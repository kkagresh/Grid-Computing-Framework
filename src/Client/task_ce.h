#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include <fstream>
#include <unistd.h>
#include <cstring>
#include <sys/wait.h>
#include <sys/resource.h>
#include <cmath>
#include <sys/times.h>
#include <sys/time.h>
using namespace std;

struct Task
{
	string task_id, task_execution_command;
	vector<string> task_input_file, task_output_file, task_compile_command;
	int priority; float time_limit;
};


int wrap_up()
{
	return 2;
}

int end_task()
{
	return 1;
}

int die(const char *msg, int wrap_up_flag = 0)
{
	fprintf(stderr, "Error: %s\n", msg);
	if(!wrap_up_flag)end_task();
	return wrap_up();
}

int compile_task(Task *tf)
{
	int file_pipes[2];
	pid_t pid;
	string task_id = tf->task_id;
	if(pipe(file_pipes) == 0)
	{
		pid = fork();
		if(pid == -1)
			return die("Could not fork a new process.",1);
	
		if(pid == 0)
		{
			close(2);
			dup(file_pipes[1]);
			for(int j = 0; j < tf->task_compile_command.size(); j++)
			{
				system((char *)(tf->task_compile_command[j]).c_str());
			}
			fprintf(stderr, "~");
			close(file_pipes[0]);
			close(file_pipes[1]);
			exit(0);
		}
		else
		{
			FILE *compilation_error_log;
			compilation_error_log = fopen((char*)((task_id + "_cel.log").c_str()), "w");
			int st, error_bytes;
			waitpid(pid, &st, 0);
			char error_buff[10001];
			error_bytes = read(file_pipes[0],error_buff,10000);
			error_bytes--;
			if(!error_bytes) 
			{ 
				fclose(compilation_error_log);
				return error_bytes;
			}
			fwrite(error_buff, sizeof(char), error_bytes, compilation_error_log);
			fclose(compilation_error_log);
			char msg[50];
			sprintf(msg, "Error in compiling task %s.",(char *)task_id.c_str());
			return die(msg);
		}
	}
	else
	{
		char msg[100];
		sprintf(msg, "Error: Could not create pipe while compiling task %s.\n", (char *)task_id.c_str());
		return die(msg,1);
	}
	return 0;
}

const char* sig_text[] = {
    "Success",
    "Hangup",
    "Interrupted",
    "Quit",
    "ILL",
    "TRAP",
    "Aborted",
    "7",
    "Floating Point Exception",
    "Killed",
    "10",
    "Segmentation Fault"
};


int execute_task(Task *tf)
{
	pid_t pid;
	pid = fork();
	if(pid == -1)
		die("Could not fork a new process.",1);
	int status, ret, max_real_secs = (int)ceil(tf->time_limit)*2;
        long ticks_per_sec = sysconf(_SC_CLK_TCK);
        struct tms t;
	float time_taken_2 = ((float)(t.tms_cutime + t.tms_cstime))/ticks_per_sec;
	if(time_taken_2 < 0) time_taken_2 = 0;
	timeval t1, t2;
	gettimeofday(&t1, NULL);
	
	if(pid == 0)
	{
		string command = tf->task_execution_command;
		cout << command << endl;
		rlimit resource_limit;
		resource_limit.rlim_cur = (int)(ceil(tf->time_limit + 0.1));
		resource_limit.rlim_max = (int)(ceil(tf->time_limit + 0.1));
		
		if(setrlimit(RLIMIT_CPU, &resource_limit) == -1)
			return die("Could not set resource limits.", 1);
		printf("Executing\n");
		system( (char *)command.c_str());
		exit(0);		
	}
	else
	{
		
                 time_t start = time(NULL);
        
        	 while ((ret = waitpid(pid, &status, WNOHANG)) == 0) {
          		  if ((time(NULL) - start) > max_real_secs)
                		return die("Killed because it seemed to have hung.");
            		  usleep(50000);
        	 }
                
                gettimeofday(&t2, NULL);
                float time_taken = (t2.tv_sec + (t2.tv_usec * 1.0)/(1000000)) - (t1.tv_sec + (t1.tv_usec * 1.0)/(1000000));
                
                
                
        	if (ret < 0)
            		return die("Failed to wait for child process.",1);

        	
		printf("Time taken: %.2f\n", time_taken);
        	ofstream ofs;
		ofs.open((char *)((tf->task_id + "_stats.log").c_str()));
		ofs << time_taken;
		ofs.close();
		
		FILE *execution_error_log;
		execution_error_log = fopen((char *)( (tf->task_id + "_eel.log").c_str()), "w");

		 char execution_error_message[200];
       		 if (time_taken > tf->time_limit) 
		 {
			 sprintf(execution_error_message, "Exceeded time limit of %.2f seconds.\n", tf->time_limit);
            		 fprintf(stderr, "%s", execution_error_message);
			 fprintf(execution_error_log, "%s", execution_error_message);
			 fclose(execution_error_log);
			 return 1;
 	        }
        
		if (WIFEXITED(status))
            		printf("Successfully Executed\n");
        	else {
            	if (WIFSIGNALED(status)) {
                	int sig = WTERMSIG(status);
                
                if (sig < 0 || sig > 11)
		{
                    sprintf(execution_error_message, "Terminated (%d).\n", sig);
                    fprintf(stderr, "%s", execution_error_message);
		}
		else 
                    fprintf(stderr, "Terminated (%s).\n", sig_text[sig]);
            }
            else
	    {   
		sprintf(execution_error_message, "Unknown error (%d)!\n", status);
            	fprintf(stderr, "%s", execution_error_message);
	    }
	    fprintf(execution_error_log, "%s", execution_error_message);
	    fclose(execution_error_log);
	    return 1;
        }

    fclose(execution_error_log);
    }

    return 0;
}

void read_tdd(Task &tf, string task_id)
{
	string tdd_file = task_id + ".tdd";
	ifstream ifs;
	ifs.open((char *)((tdd_file).c_str()));
	getline(ifs,tf.task_id);
	int tc_count, j;
	ifs >> tc_count;
	for(j = 0; j < tc_count; j++)
	{
		string temp;
		while(getline(ifs,temp) && temp == "");
		tf.task_compile_command.push_back((string)temp);
	}
	cout << tf.task_compile_command.size() << endl;
	cout << tf.task_compile_command[0] << endl;
	getline(ifs,tf.task_execution_command);
	
	int ti_count;
	ifs >> ti_count;
	for(j = 0; j < ti_count; j++)
	{
		string temp;
		ifs >> temp;
		tf.task_input_file.push_back(temp);
	}
	
	int to_count;
	ifs >> to_count;
	for(j = 0; j < to_count; j++)
	{
		string temp;
		ifs >> temp;
		cout << temp << endl;
		tf.task_output_file.push_back(temp);
	}
	ifs >> tf.priority;
	ifs >> tf.time_limit;
}
int task_ce(string tid)
{
	string command = "gunzip -f " + tid + ".tar.gz"; 
	system(command.c_str());
	command = "tar xf " + tid + ".tar";
	system(command.c_str());
	
	ofstream ofs;
	ofs.open((char *)((tid + "_cel.log").c_str()));
	ofs.close();
	ofs.open((char *)((tid + "_eel.log").c_str()));
	ofs.close();
	ofs.open((char *)((tid + "_stats.log").c_str()));
	ofs.close();
	
	Task tf;
	read_tdd(tf, tid);
	int cret, eret;
	cret = compile_task(&tf);
	if(cret)
	{
		if(cret == 1)
		{
			//TODO
			//Handle this
			
		}
		else if(cret == 2)
		{
			//TODO
			//Handle this
			
		}
	}
	
	eret = 0;
	if(cret == 0)
	{
		eret = execute_task(&tf);
		if(eret == 2)
		{
			//TODO
			//Handle this
		}
	}
	string cur_task_id = tid;
	command = "tar cf " + cur_task_id + "_op.tar " + cur_task_id + "_cel.log";
	system(command.c_str());
	command = "tar rf " + cur_task_id + "_op.tar " + cur_task_id + "_eel.log";
	system(command.c_str());
	command = "tar rf " + cur_task_id + "_op.tar " + cur_task_id + "_stats.log";
	system(command.c_str());
	if(!(eret | cret))
	{
		for(int j = 0; j < tf.task_output_file.size(); j++)
			command = ("tar rf " + cur_task_id + "_op.tar " + tf.task_output_file[j]);
		system(command.c_str());
	}
	command = ("gzip -f " + cur_task_id + "_op.tar");
	system(command.c_str());

	return max(eret,cret);
}
