#include<cstdio>
#include<vector>
#include<cstring>
#include<malloc.h>
#include<iostream>
#include<sstream>

#include "config.h"

using namespace std;

typedef struct XMLFile
{
	char file_address[MAXPATHLENGTH];
	char file[MAXFILESIZE];
	int file_length;
}XMLFile;

typedef struct ProblemDescripton
{
	string name;
	//char name[100];
	string user;
	//char user[50];
	string problem_id;
	//char problem_id[40];
	string purpose;
	//char purpose[400];
}ProblemDescription;


typedef struct UnitTask
{
	string task_id; 
    	short priority;
	int total_dependencies;
	vector<string> dependencies;
	unsigned int timeout;
	string task_source_path;
	string task_inputset_path;
} UnitTask;

typedef struct ResultCompiler
{
	string rcp_path;
}ResultCompiler;

typedef struct ExecutionMonitor
{
	string emp_path;
}ExecutionMonitor;

typedef struct ParsedXMLElements
{
	ProblemDescription Description;
	vector<UnitTask> Tasks;
	ResultCompiler RCP;
	ExecutionMonitor EMP;
}ParsedXMLElements;

void get_file(XMLFile *xf)
{
	FILE *fp;
	char ch;
	fp = fopen(xf->file_address,"r");
	xf->file_length = 0;
	while(1)
	{
		ch = fgetc(fp);
		if(ch == '\n' || ch == '\t') ch = ' ';
		if(ch == EOF) break;
		xf->file[xf->file_length++] = ch;
	}
	xf->file[xf->file_length] = '\0';
	xf->file_length++;
}

int report_parse_error(short error_number)
{
	char error[200];
	switch(error_number)
	{
		case 1: strcpy(error, "Improperly formed or missing opening problem tag."); 
				break;
		case 2: strcpy(error, "Improperly formed or missing closing problem tag.");
				break;
		case 3: strcpy(error, "Unexpected characters found after closing problem tag.");
				break;
		case 4: strcpy(error, "Improperly formed or missing opening description tag. ");
				break;
		case 5: strcpy(error, "Improperly formed or missing closing description tag.");
				break;
		case 6: strcpy(error, "Improperly formed or missing opening name tag.");
				break;
		case 7: strcpy(error, "Improperly formed or missing closing name tag.");
				break;
		case 8: strcpy(error, "Improperly formed or missing opening problem id tag.");
				break;
		case 9: strcpy(error, "Improperly formed or missing closing problem id tag.");
				break;
		case 10: strcpy(error, "Improperly formed or missing opening user id tag.");
				break;
		case 11: strcpy(error, "Improperly formed or missing closing user id tag.");
				break;
		case 12: strcpy(error, "Improperly formed or missing opening purpose id tag.");
				break;
		case 13: strcpy(error, "Improperly formed or missing closing purpose id tag.");
				break;
		case 14: strcpy(error, "Improperly formed or missing opening tasks tag.");
				break;
		case 15: strcpy(error, "Improperly formed or missing closing tasks tag.");
				break;
		case 16: strcpy(error, "Improperly formed or missing opening task tag.");
				break;
		case 17: strcpy(error, "Improperly formed or missing closing task tag.");
				break;
		case 18: strcpy(error, "Improperly formed or missing opening task id tag.");
				break;
		case 19: strcpy(error, "Improperly formed or missing closing task id tag.");
				break;
		case 20: strcpy(error, "Improperly formed or missing opening task priority tag.");
				break;
		case 21: strcpy(error, "Improperly formed or missing closing task priority tag.");
				break;
		case 22: strcpy(error, "Improperly formed or missing opening dependencies tag.");
				break;
		case 23: strcpy(error, "Improperly formed or missing closing dependencies tag.");
				break;
		case 24: strcpy(error, "Improperly formed or missing opening do tag.");
				break;
		case 25: strcpy(error, "Improperly formed or missing closing do tag.");
				break;
		case 26: strcpy(error, "Improperly formed or missing opening task timeout tag.");
				break;
		case 27: strcpy(error, "Improperly formed or missing closing task timeout tag.");
				break;
		case 28: strcpy(error, "Improperly formed or missing opening task source path tag.");
				break;
		case 29: strcpy(error, "Improperly formed or missing closing task source path tag.");
				break;
		case 30: strcpy(error, "Improperly formed or missing opening task compile command tag.");
				break;
		case 31: strcpy(error, "Improperly formed or missing closing task compile command tag.");
				break;
		case 32: strcpy(error, "Improperly formed or missing opening task execution command tag.");
				break;
		case 33: strcpy(error, "Improperly formed or missing closing task executon command tag.");
				break;
		case 34: strcpy(error, "Improperly formed or missing opening rcp tag.");
				break;
		case 35: strcpy(error, "Improperly formed or missing closing rcp tag.");
				break;
		case 36: strcpy(error, "Improperly formed or missing opening rcp source path tag.");
				break;
		case 37: strcpy(error, "Improperly formed or missing closing rcp source path tag.");
				break;
		case 38: strcpy(error, "Improperly formed or missing opening emp tag.");
				break;
		case 39: strcpy(error, "Improperly formed or missing closing emp tag.");
				break;
		case 40: strcpy(error, "Improperly formed or missing opening emp source path tag.");
				break;
		case 41: strcpy(error, "Improperly formed or missing closing emp source path tag.");
				break;
		case 42: strcpy(error, "Improperly formed or missing opening task input set path tag.");
				break;
		case 43: strcpy(error, "Improperly formed or missing closing task input set path tag.");
				break;
	}

	printf("%s\n", error);
	return 0;
}

int parse(XMLFile *xf, ParsedXMLElements *pxe)
{
	int i, j;
	/*Tags*/
	char problem_tag[30]; int problem_tag_length;
	char description_tag[30]; int description_tag_length;
	char name_tag[30]; int name_tag_length;
	char problemid_tag[30]; int problemid_tag_length;
	char userid_tag[30]; int userid_tag_length;
	char purpose_tag[30]; int purpose_tag_length;
	char tasks_tag[30]; int tasks_tag_length;
	char task_tag[30]; int task_tag_length;
	char taskid_tag[30]; int taskid_tag_length;
	char taskpriority_tag[30]; int taskpriority_tag_length;
	char dependencies_tag[30]; int dependencies_tag_length;
	char do_tag[30]; int do_tag_length;
	char tasktimeout_tag[30]; int tasktimeout_tag_length;
	char tasksourcepath_tag[30]; int tasksourcepath_tag_length;
	char taskinputsetpath_tag[30]; int taskinputsetpath_tag_length;
	char taskcompilecommand_tag[30]; int taskcompilecommand_tag_length;
	char taskexecutioncommand_tag[30]; int taskexecutioncommand_tag_length;
	char rcp_tag[30]; int rcp_tag_length;
	char rcpsourcepath_tag[30]; int rcpsourcepath_tag_length;
	char emp_tag[30]; int emp_tag_length;
	char empsourcepath_tag[30]; int empsourcepath_tag_length;


	/*Set Tags*/
	strcpy(problem_tag, "problem"); problem_tag_length = strlen(problem_tag);
	strcpy(description_tag, "description"); description_tag_length = strlen(description_tag);
	strcpy(name_tag, "name"); name_tag_length = strlen(name_tag);
	strcpy(problemid_tag, "problemid"); problemid_tag_length = strlen(problemid_tag);
	strcpy(userid_tag, "userid"); userid_tag_length = strlen(userid_tag);
	strcpy(purpose_tag, "purpose"); purpose_tag_length = strlen(purpose_tag);
	strcpy(tasks_tag, "tasks"); tasks_tag_length = strlen(tasks_tag);
	strcpy(task_tag, "task"); task_tag_length = strlen(task_tag);
	strcpy(taskid_tag, "taskid"); taskid_tag_length = strlen(taskid_tag);
	strcpy(taskpriority_tag, "taskpriority"); taskpriority_tag_length = strlen(taskpriority_tag);
	strcpy(dependencies_tag, "dependencies"); dependencies_tag_length = strlen(dependencies_tag);
	strcpy(do_tag, "do"); do_tag_length = strlen(do_tag);
	strcpy(tasktimeout_tag, "tasktimeout"); tasktimeout_tag_length = strlen(tasktimeout_tag);
	strcpy(tasksourcepath_tag, "tasksourcepath"); tasksourcepath_tag_length = strlen(tasksourcepath_tag);
	strcpy(taskinputsetpath_tag, "taskinputsetpath"); taskinputsetpath_tag_length = strlen(taskinputsetpath_tag);
	strcpy(taskcompilecommand_tag, "taskcompilecommand"); taskcompilecommand_tag_length = strlen(taskcompilecommand_tag);
	strcpy(taskexecutioncommand_tag, "taskexecutioncommand"); taskexecutioncommand_tag_length = strlen(taskexecutioncommand_tag);
	strcpy(rcp_tag, "rcp"); rcp_tag_length = strlen(rcp_tag);
	strcpy(rcpsourcepath_tag, "rcpsourcepath"); rcpsourcepath_tag_length = strlen(rcpsourcepath_tag);
	strcpy(emp_tag, "emp"); emp_tag_length = strlen(emp_tag);
	strcpy(empsourcepath_tag, "empsourcepath"); empsourcepath_tag_length = strlen(empsourcepath_tag);



	/* <problem> */
	for(i = 0; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break; 
	
	//i += 1;
	if(i >= xf->file_length) return report_parse_error(1);
	
	if(xf->file[i] == '<' && xf->file[i+problem_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+problem_tag_length); j++)
				if(problem_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(1);
	}
	else return report_parse_error(1);
	i += problem_tag_length + 2;
	/* <problem> */
	

	/* <description> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	
	if(i >= xf->file_length) return report_parse_error(4);
	//i += 1;

	if(xf->file[i] == '<' && xf->file[i+description_tag_length+1] == '>')
	{
			
			for(j = i+1; j < (i+1+description_tag_length); j++)
				if(description_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(4);
	}
	else return report_parse_error(4);
	i += description_tag_length + 2;
	
	/* <description> */
	
        /* <name> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(6);
	
	if(xf->file[i] == '<' && xf->file[i+name_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+name_tag_length); j++)
				if(name_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(6);
	}
	else return report_parse_error(6);
	i += name_tag_length + 2;
	/* <name> */

	
	/* </name> */
	
	pxe->Description.name = "";
	//(pxe.Description).name = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			if(pxe->Description.name.size() > 100)
			{	//return validate_error(1); 
			}
			
			pxe->Description.name.push_back(xf->file[i]);
		}



	if(i >= xf->file_length) return report_parse_error(7);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+name_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+name_tag_length); j++)
				if(name_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(2);
	}
	else return report_parse_error(7);
	i += name_tag_length + 3;
	
	/* </name> */

	/* <problemid> */
		for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
	
	
	if(i >= xf->file_length) return report_parse_error(8);
	//i += 1;
	//printf("%c %c", xf->file[i], xf->file[i+name_tag_length+1]);
	
	if(xf->file[i] == '<' && xf->file[i+problemid_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+problemid_tag_length); j++)
				if(problemid_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(8);
	}
	else return report_parse_error(8);
	i += problemid_tag_length + 2;
	/* <problemid> */

	/* </problemid> */
	//for(; i < xf->file_length; i++)
		//if(xf->file[i] != ' ') break;
	
		pxe->Description.problem_id = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			if(pxe->Description.problem_id.size() > 40)
			{
		
					//return validate_error(2);
			}else 
			pxe->Description.problem_id.push_back(xf->file[i]);
		}

		
	if(i >= xf->file_length) return report_parse_error(9);
	
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+problemid_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+problemid_tag_length); j++)
				if(problemid_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(9);
	}
	else return report_parse_error(9);
	i += problemid_tag_length + 3;
	
	/* </problemid> */
	
	/* <user> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
	
	

	if(i >= xf->file_length) return report_parse_error(10);
	//i += 1;
	//printf("%c %c", xf->file[i], xf->file[i+name_tag_length+1]);
	
	if(xf->file[i] == '<' && xf->file[i+userid_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+userid_tag_length); j++)
				if(userid_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(10);
	}
	else return report_parse_error(10);
	i += userid_tag_length + 2;
	/* <user> */

	/* </user> */
	//for(; i < xf->file_length; i++)
	//	if(xf->file[i] != ' ') break;
	pxe->Description.user = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			if(pxe->Description.user.size() > 50)
			{
		
					//return validate_error(2);
			}else 
			pxe->Description.user.push_back(xf->file[i]);
		}

	
		
	if(i >= xf->file_length) return report_parse_error(11);
	//printf("%c",xf->file[i+1]);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+userid_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+userid_tag_length); j++)
				if(userid_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(11);
	}
	else return report_parse_error(11);
	i += userid_tag_length + 3;
	/* </user> */





	/* <purpose> */
	
	pxe->Description.purpose = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		

		
	if(i >= xf->file_length) return report_parse_error(12);
	//i += 1;
	//printf("%c %c", xf->file[i], xf->file[i+name_tag_length+1]);
	
	if(xf->file[i] == '<' && xf->file[i+purpose_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+purpose_tag_length); j++)
				if(purpose_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(12);
	}
	else return report_parse_error(12);
	i += purpose_tag_length + 2;
	/* <purpose> */

	/* </purpose> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			if(pxe->Description.purpose.size() > 50)
			{
		
					//return validate_error(2);
			}else 
			pxe->Description.purpose.push_back(xf->file[i]);
		}
		
	if(i >= xf->file_length) return report_parse_error(13);
	//printf("%c",xf->file[i+1]);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+purpose_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+purpose_tag_length); j++)
				if(purpose_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(13);
	}
	else return report_parse_error(13);
	i += purpose_tag_length + 3;
	
	/* </purpose> */

		
	/* </description> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(5);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+description_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+description_tag_length); j++)
				if(description_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(2);
	}
	else return report_parse_error(5);
	i += description_tag_length + 3;
	/* </description> */
	
	//cout << pxe->Description.name << endl;
	//cout << pxe->Description.user << endl;
	//cout << pxe->Description.problem_id << endl;
	//cout << pxe->Description.purpose << endl;
	/* <tasks> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(14);
	//i += 1;
	//printf("%c %c", xf->file[i], xf->file[i+name_tag_length+1]);
	
	if(xf->file[i] == '<' && xf->file[i+tasks_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+tasks_tag_length); j++)
				if(tasks_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(14);
	}
	else return report_parse_error(14);
	i += tasks_tag_length + 2;
	/* <tasks> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;

	
	
	int tot_task_tags = 0;
	int cur_index = i;
	int task_tag_set = 1;
	
	
	while(task_tag_set)
	{
		if(xf->file[cur_index] == '<' && xf->file[cur_index+task_tag_length+1] == '>')
		{
				for(j = cur_index+1; j < (cur_index+1+task_tag_length); j++)
					if(task_tag[j-(cur_index+1)] != xf->file[j])
						{ 
						task_tag_set = 0; break; }
					
				if(task_tag_set == 0) break;
				tot_task_tags += 1;

				/* <task> */
				for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(16);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+task_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+task_tag_length); j++)
					if(task_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(16);
				}
				else return report_parse_error(16);
				i += task_tag_length + 2;
				/* <task> */	
				UnitTask ut;	
				
				/* <taskid> */
				for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(18);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+taskid_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+taskid_tag_length); j++)
					if(taskid_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(18);
				}
				else return report_parse_error(18);
				i += taskid_tag_length + 2;
				/* <task> */	
					
				/* </taskid> */
					ut.task_id = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			if(ut.task_id.size() > 40)
			{	//return validate_error(1); 
			}
			
			ut.task_id.push_back(xf->file[i]);
		}

		
				if(i >= xf->file_length) return report_parse_error(19);
				//printf("%c",xf->file[i+1]);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+taskid_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+taskid_tag_length); j++)
						if(taskid_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(19);
				}
				else return report_parse_error(19);
				i += taskid_tag_length + 3;
	
				/* </taskid> */
				
			
				/* <taskpriority> */
				for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(20);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+taskpriority_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+taskpriority_tag_length); j++)
					if(taskpriority_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(20);
				}
				else return report_parse_error(20);
				i += taskpriority_tag_length + 2;
				/* <taskpriority> */	
					
				/* </taskpriority> */
				ut.priority = 0;
				string temp_str = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			
			if(temp_str.size() > 8)
			{	//return validate_error(1); 
			}
			
			temp_str.push_back(xf->file[i]);
		}
		
				if(i >= xf->file_length) return report_parse_error(21);
				//printf("%c",xf->file[i+1]);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+taskpriority_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+taskpriority_tag_length); j++)
						if(taskpriority_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(21);
				}
				else return report_parse_error(21);
				i += taskpriority_tag_length + 3;
	
				/* </taskpriority> */
				
				/* <dependencies> */
				for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(22);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+dependencies_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+dependencies_tag_length); j++)
					if(dependencies_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(22);
				}
				else return report_parse_error(22);
				i += dependencies_tag_length + 2;
				/* <dependencies> */	
				
				int do_index = i;
				int do_tag_set = 1;
				int tot_do_tags = 0;

				for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;

				do_index = i;
				while(do_tag_set)
				{
					if(xf->file[do_index] == '<' && xf->file[do_index+do_tag_length+1] == '>')
					{
						for(j = do_index+1; j < (do_index+1+do_tag_length); j++)
						if(do_tag[j-(do_index+1)] != xf->file[j])
						{ 
							do_tag_set = 0; break; 
						}
					
						if(do_tag_set == 0) break;
					
					tot_do_tags += 1;

			          /* <do> */
			  	for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(24);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+do_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+do_tag_length); j++)
					if(do_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(24);
				}
				else return report_parse_error(24);
				i += do_tag_length + 2;
				/* <do> */	
					
				/* </do> */
				string temp_dep = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			if(temp_dep.size() > 40)
			{	//return validate_error(1); 
			}
			
			temp_dep.push_back(xf->file[i]);
		}
	if(temp_dep !=  "") ut.dependencies.push_back(temp_dep);
		
				if(i >= xf->file_length) return report_parse_error(25);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+do_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+do_tag_length); j++)
						if(do_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(25);
				}
				else return report_parse_error(25);
				i += do_tag_length + 3;
	
				/* </do> */
						for(; i < xf->file_length; i++)
							if(xf->file[i] != ' ') break;


						do_index = i;
					}
					else break;
				}
					
				
				/* </dependencies> */
				for(; i < xf->file_length; i++)
					if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(23);	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+dependencies_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+dependencies_tag_length); j++)
						if(dependencies_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(23);
				}
				else return report_parse_error(23);
				i += dependencies_tag_length + 3;
	
				/* </dependencies> */
					
				 /* <tasktimeout> */
			  	for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(26);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+tasktimeout_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+tasktimeout_tag_length); j++)
					if(tasktimeout_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(26);
				}
				else return report_parse_error(26);
				i += tasktimeout_tag_length + 2;
				/* <tasktimeout> */	
					
				/* </tasktimeout> */
				for(; i < xf->file_length; i++)
					if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(27);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+tasktimeout_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+tasktimeout_tag_length); j++)
						if(tasktimeout_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(27);
				}
				else return report_parse_error(27);
				i += tasktimeout_tag_length + 3;
	
				/* </tasktimeout> */	
					
				
				/* <tasksourcepath> */
			  	for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(28);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+tasksourcepath_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+tasksourcepath_tag_length); j++)
					if(tasksourcepath_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(28);
				}
				else return report_parse_error(28);
				i += tasksourcepath_tag_length + 2;
				/* <tasksourcepath> */	
					
				/* </tasksourcepath> */
				for(; i < xf->file_length; i++)
					if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(29);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+tasksourcepath_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+tasksourcepath_tag_length); j++)
						if(tasksourcepath_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(29);
				}
				else return report_parse_error(29);
				i += tasksourcepath_tag_length + 3;
	
				/* </tasksourcepath> */	

				/* <taskinputsetpath> */
			  	for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(42);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+taskinputsetpath_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+taskinputsetpath_tag_length); j++)
					if(taskinputsetpath_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(42);
				}
				else return report_parse_error(42);
				i += taskinputsetpath_tag_length + 2;
				/* <taskinputsetpath> */	
					
				/* </taskinputsetpath> */
				for(; i < xf->file_length; i++)
					if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(43);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+taskinputsetpath_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+taskinputsetpath_tag_length); j++)
						if(taskinputsetpath_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(43);
				}
				else return report_parse_error(43);
				i += taskinputsetpath_tag_length + 3;
	
				/* </taskinputsetpath> */	

				/* <taskcompilecommand> */
			  	for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(30);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+taskcompilecommand_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+taskcompilecommand_tag_length); j++)
					if(taskcompilecommand_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(30);
				}
				else return report_parse_error(30);
				i += taskcompilecommand_tag_length + 2;
				/* <taskcompilecommand> */	
					
				/* </taskcompilecommand> */
				for(; i < xf->file_length; i++)
					if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(31);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+taskcompilecommand_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+taskcompilecommand_tag_length); j++)
						if(taskcompilecommand_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(31);
				}
				else return report_parse_error(31);
				i += taskcompilecommand_tag_length + 3;
	
				/* </taskcompilecommand> */	
				
				/* <taskexecutioncommand> */
			  	for(; i < xf->file_length; i++)
						if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(32);
					//i += 1;
	
				if(xf->file[i] == '<' && xf->file[i+taskexecutioncommand_tag_length+1] == '>')
				{
					for(j = i+1; j < (i+1+taskexecutioncommand_tag_length); j++)
					if(taskexecutioncommand_tag[j-(i+1)] != xf->file[j])
						return report_parse_error(32);
				}
				else return report_parse_error(32);
				i += taskexecutioncommand_tag_length + 2;
				/* <taskexecutioncommand> */	
					
				/* </taskexecutioncommand> */
				for(; i < xf->file_length; i++)
					if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(33);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+taskexecutioncommand_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+taskexecutioncommand_tag_length); j++)
						if(taskexecutioncommand_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(33);
				}
				else return report_parse_error(33);
				i += taskexecutioncommand_tag_length + 3;
	
				/* </taskexecutioncommand> */	
				
				/* </task> */
				for(; i < xf->file_length; i++)
					if(xf->file[i] != ' ') break;
		
				if(i >= xf->file_length) return report_parse_error(17);
				//printf("%c",xf->file[i+1]);
	
				if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+task_tag_length+1] == '>')
				{
					for(j = i+2; j < (i+2+task_tag_length); j++)
						if(task_tag[j-(i+2)] != xf->file[j])
							return report_parse_error(17);
				}
				else return report_parse_error(17);
				i += task_tag_length + 3;
	
				/* </task> */
				
				for(; i < xf->file_length; i++)
					if(xf->file[i] != ' ') break;


				cur_index = i;
		}
		else break;
	}
	

	//if(open_task_tags != 0) return report_parse_error(17);
	/* </tasks> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(15);
	//printf("%c",xf->file[i+1]);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+tasks_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+tasks_tag_length); j++)
				if(tasks_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(15);
	}
	else return report_parse_error(15);
	i += tasks_tag_length + 3;
	
	/* </tasks> */

        /* <rcp> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(34);
	
	if(xf->file[i] == '<' && xf->file[i+rcp_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+rcp_tag_length); j++)
				if(rcp_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(34);
	}
	else return report_parse_error(34);
	i += rcp_tag_length + 2;
	/* <rcp> */


        /* <rcpsourcepath> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(36);
	
	if(xf->file[i] == '<' && xf->file[i+rcpsourcepath_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+rcpsourcepath_tag_length); j++)
				if(rcpsourcepath_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(36);
	}
	else return report_parse_error(36);
	i += rcpsourcepath_tag_length + 2;
	/* <rcpsourcepath> */
	
	/* </rcpsourcepath> */
	pxe->RCP.rcp_path = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			if(pxe->RCP.rcp_path.size() > MAXPATHLENGTH)
			{	//return validate_error(1); 
			}
			
			pxe->RCP.rcp_path.push_back(xf->file[i]);
		}

		
	if(i >= xf->file_length) return report_parse_error(37);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+rcpsourcepath_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+rcpsourcepath_tag_length); j++)
				if(rcpsourcepath_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(37);
	}
	else return report_parse_error(37);
	i += rcpsourcepath_tag_length + 3;
	
	/* </rcpsourcepath> */


	
	/* </rcp> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(35);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+rcp_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+rcp_tag_length); j++)
				if(rcp_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(35);
	}
	else return report_parse_error(35);
	i += rcp_tag_length + 3;
	
	/* </rcp> */

	
	    /* <emp> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(38);
	
	if(xf->file[i] == '<' && xf->file[i+emp_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+emp_tag_length); j++)
				if(emp_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(38);
	}
	else return report_parse_error(38);
	i += emp_tag_length + 2;
	/* <emp> */


        /* <empsourcepath> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;

			
	if(i >= xf->file_length) return report_parse_error(40);
	
	if(xf->file[i] == '<' && xf->file[i+empsourcepath_tag_length+1] == '>')
	{
			for(j = i+1; j < (i+1+empsourcepath_tag_length); j++)
				if(empsourcepath_tag[j-(i+1)] != xf->file[j])
					return report_parse_error(40);
	}
	else return report_parse_error(40);
	i += empsourcepath_tag_length + 2;
	/* <empsourcepath> */
	
	/* </empsourcepath> */
			
	
	pxe->EMP.emp_path = "";
	for(; i < xf->file_length; i++)
		if(xf->file[i] == '<') break;
		else
		{
			if(pxe->EMP.emp_path.size() > MAXPATHLENGTH)
			{	//return validate_error(1); 
			}
			
			pxe->EMP.emp_path.push_back(xf->file[i]);
		}
	


	if(i >= xf->file_length) return report_parse_error(41);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+empsourcepath_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+empsourcepath_tag_length); j++)
				if(empsourcepath_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(41);
	}
	else return report_parse_error(41);
	i += empsourcepath_tag_length + 3;
	
	/* </empsourcepath> */


	
	/* </emp> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(39);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+emp_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+rcp_tag_length); j++)
				if(emp_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(39);
	}
	else return report_parse_error(39);
	i += emp_tag_length + 3;
	
	/* </emp> */

	
	/* </problem> */
	for(; i < xf->file_length; i++)
		if(xf->file[i] != ' ') break;
		
	if(i >= xf->file_length) return report_parse_error(2);
	
	if(xf->file[i] == '<' && xf->file[i+1] == '/' && xf->file[i+1+problem_tag_length+1] == '>')
	{
		for(j = i+2; j < (i+2+problem_tag_length); j++)
				if(problem_tag[j-(i+2)] != xf->file[j])
					return report_parse_error(2);
	}
	else return report_parse_error(2);
	i += problem_tag_length + 3;
	/* </problem> */
	
	
	for(; xf->file[i] != EOF && xf->file[i] != 0 &&  xf->file_length; i++)
		if(xf->file[i] != ' ') { return report_parse_error(3); }
	
	printf("Properly formed XML Schema");
	return 1;
}

void show_file(XMLFile *xf)
{
	int i;
	for(i = 0; i < (xf->file_length); i++)
		putc(xf->file[i],stdout);
}

int main()
{
	XMLFile *xf = new XMLFile;
	//Handle this
	if(xf == NULL) return 1;
	
	//ParsedXMLElements pxe;
	ParsedXMLElements *pxe = new ParsedXMLElements;

	strcpy(xf->file_address, "inp.in");
	get_file(xf);
	//show_file(xf);
	
	parse(xf,pxe);
	
	delete xf;
	delete pxe;
	return 0;
}
