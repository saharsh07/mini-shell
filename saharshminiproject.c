
#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>
#include <signal.h>  
#include <unistd.h>  
#include <sys/wait.h>  

#define Buffer_Length 1024

void handle_sigtstp(int sig){
    printf("Stop not allowed.\n Saharsh's shell>> ");
    fflush(stdout);
}

void sigintHandler(int sig){
    printf("Stop not allowed.\n Saharsh's shell>> ");
    fflush(stdout);
}

void executeCommand(char line[]) {
	int index = 1,pid2;
	char *args[30]; 	                 
	char *token = strtok(line, " "); //breaks string str into a series of tokens using the delimiter.	
	args[0] = strdup(token);			 
    pid2 = fork();
    if(pid2==0)          //Child process
    {
	    while ((token = strtok(NULL, " ")) != NULL) 
	    {
		args[index] = strdup(token);
		++index;
	    }
	args[index] = NULL;
	execvp(args[0], args);  //execute command in UNIX
	perror( "Error" );
	exit(1);
    }
	else           //Parent Process
	{
	    wait(NULL);
	}
}

void ExecuteCmdWoFork(char line[])
{
    int index = 1;
	char *args[30]; 					 
	char *token = strtok(line, " ");	 
	args[0] = strdup(token);			 
	    while ((token = strtok(NULL, " ")) != NULL) 
	    {
		args[index] = strdup(token);
		++index;
	    }
	args[index] = NULL;
	execvp(args[0], args);
	perror( "Error" );
	exit(1);
}

void executePipeCommand(char line[]) 
{
	int pid,pid1;
	int pipefds[2];
	char *cmd1, *cmd2;
	pid1 = fork();
    if(pid1==0)
    {
	    cmd1 = strtok(line, "|"); //tokenize command by the | substring
	    cmd2 = strtok(NULL, "|");
	    pipe(pipefds);         
        if ((pid = fork()) < 0) 
		{
		perror( "connect" );
		exit(1);
	    }
	
		if (pid == 0)      //child process        
		{	
		close(1);			
		dup(pipefds[1]);	
		close(pipefds[0]);	
		close(pipefds[1]);
		ExecuteCmdWoFork(cmd1);	 //execute the first command
		}
	
		else      //parent process 
		{ 
		close(0);			
		dup(pipefds[0]);	
		close(pipefds[0]);	
		close(pipefds[1]);
		ExecuteCmdWoFork(cmd2);	//execute the second command
		}
	}
	else
	{
   wait(NULL); 
	}
}

int main()
{
    char line[Buffer_Length];   //get command line
    while(1)
    {
        signal(SIGTSTP, &handle_sigtstp);  //Ctrl z block
        signal(SIGINT, sigintHandler);      
		printf("\nSaharsh's shell>> ");                    
        if(!fgets(line, Buffer_Length, stdin))
            break;    
        size_t length = strlen(line);
        if (line[length - 1] == '\n')
            line[length - 1] = '\0';     //if user hits CTRL+D break                         
        if(strcmp(line, "exit")==0)                         
        {            
            break;
        }
        if(strstr(line, "|") == NULL)	
			executeCommand(line);
		else								
			executePipeCommand(line);       
        
    }
} 
