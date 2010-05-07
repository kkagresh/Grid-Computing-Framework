/* Send/receive commands to
 * the client */

#include <semaphore.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

struct command
{
	string command_str, client;
};


void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }

    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

/* At a time, only one command can be sent 
 * Others would need to wait until the first
 * is sent */

sem_t sc_sem;
void send_command_to_client(command arg)
{
	int sockfd;
        struct addrinfo hints, *servinfo, *p;
	int rv, numbytes, optval = 1;
	char messagebuffer[500];
	
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM;
	
	cout << arg.client << " sent the command " << arg.command_str << endl;	

        if ((rv = getaddrinfo(arg.client.c_str(),PORT3, &hints, &servinfo)) != 0) 
	{
               fprintf(stderr, "Error in send_command_to_client: %s\n", gai_strerror(rv));
               exit(1);
        }

        for(p = servinfo; p != NULL; p = p->ai_next) 
	{
            if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) 
        	{
                    perror("Error in send_command_to_client(): Could not create socket\n");
                    continue;
            }
			break;
       }
	
        if (p == NULL) 
	{
                 fprintf(stderr, "Error in send_command_to_client(): Failed to bind socket\n");
                 exit(1);
        }	
	
	strcpy(messagebuffer, arg.command_str.c_str());	
	
	if ((numbytes = sendto(sockfd, messagebuffer, 
			strlen(messagebuffer), 0, p->ai_addr, p->ai_addrlen)) == -1) 
	{
			perror("Error in send_command_to_client(): Message could not be sent\n");
			exit(1);
	}
	freeaddrinfo(servinfo);
	close(sockfd);
}

struct c_resp
{
	string client, response;
	unsigned int time_stamp;

	bool operator < (const c_resp & b) const
	{
		return time_stamp < b.time_stamp;
	}
};

/* At a time only one client response
 * message can be sent */

sem_t cr_sem;
set < c_resp > client_response;

void * wait_for_client_response_to_command( void * args )
{
    int sockfd;
    struct addrinfo hints, *servinfo, *p;
    char tbuf[MAXBUFLEN];
    unsigned int time_stamp = 0;

    int rv, numbytes;
    struct sockaddr_storage their_addr;
    char buf[MAXBUFLEN];
    size_t addr_len;
    char s[INET6_ADDRSTRLEN], contacting_client[100];
    fd_set readfds, masterfds;
    struct timeval timeout;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = AI_PASSIVE; // use my IP
	
    if ((rv = getaddrinfo(NULL, PORT4, &hints, &servinfo)) != 0) 
    {
        fprintf(stderr, "Error in wait_for_client_response_to_command(): %s\n", gai_strerror(rv));
        exit(1);
    }

    // loop through all the results and bind to the first we can
    for(p = servinfo; p != NULL; p = p->ai_next) 
	{
        if ((sockfd = socket(p->ai_family, p->ai_socktype, 
			p->ai_protocol)) == -1) 
		{
            perror("Error in wait_for_client_response_to_command(): Could not create socket\n");
            continue;
        }
    int optval;
    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
	   fprintf(stderr, "Failed to set socket options\n");
	   exit(1);
    }

        if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) 
		{
            close(sockfd);
            perror("Error in wait_for_client_response_to_command(): Failed to bind socket\n");
            continue;
        }
        break;
    }

    if (p == NULL) 
    {
        fprintf(stderr, "Error in wait_for_client_response_to_command(): Failed to bind socket\n\n");
        exit(1);
    }

    freeaddrinfo(servinfo);
    addr_len = sizeof their_addr;
   
    while(1)
   {
		addr_len = sizeof their_addr;
		if ((numbytes = recvfrom(sockfd, buf, MAXBUFLEN-1 , 0,
			(struct sockaddr *)&their_addr, &addr_len)) == -1) 
	  	 {
			perror("recvfrom");
			exit(1);
       		}
	   	buf[numbytes] = '\0';

		strcpy(contacting_client, inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr),s, sizeof s));
		
		string response = (string)buf;
		cout << contacting_client << " responded with " << response << endl;
  		c_resp cr;
		cr.client = contacting_client; cr.response = response;
		cr.time_stamp = time_stamp++;
		sem_wait(&cr_sem);
		client_response.insert(cr);
		sem_post(&cr_sem);
  }
	freeaddrinfo(servinfo);
	close(sockfd);
}
