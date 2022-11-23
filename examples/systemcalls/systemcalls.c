#include "systemcalls.h"
#include "string.h"
#include "sys/types.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * @param cmd the command to execute with system()
 * @return true if the command in @param cmd was executed
 *   successfully using the system() call, false if an error occurred,
 *   either in invocation of the system() call, or if a non-zero return
 *   value was returned by the command issued in @param cmd.
*/
bool do_system(const char *cmd)
{

/*
 * TODO  add your code here
 *  Call the system() function with the command set in the cmd
 *   and return a boolean true if the system() call completed with success
 *   or false() if it returned a failure
*/
    int ret = system(cmd);
    
    if (ret == -1){
    	perror("Error Executing Command");
        return false;
    }


    return true;
}

/**
* @param count -The numbers of variables passed to the function. The variables are command to execute.
*   followed by arguments to pass to the command
*   Since exec() does not perform path expansion, the command to execute needs
*   to be an absolute path.
* @param ... - A list of 1 or more arguments after the @param count argument.
*   The first is always the full path to the command to execute with execv()
*   The remaining arguments are a list of arguments to pass to the command in execv()
* @return true if the command @param ... with arguments @param arguments were executed successfully
*   using the execv() call, false if an error occurred, either in invocation of the
*   fork, waitpid, or execv() command, or if a non-zero return value was returned
*   by the command issued in @param arguments with the specified arguments.
*/

bool do_exec(int count, ...)
{
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
       
    }
    
    command[count] = NULL;
    //printf("Command[%count] is %.*s\n",i, 50, command[count]);

    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

/*
 * TODO:
 *   Execute a system command by calling fork, execv(),
 *   and wait instead of system (see LSP page 161).
 *   Use the command[0] as the full path to the command to execute
 *   (first argument to execv), and use the remaining arguments
 *   as second argument to the execv() command.
 *
*/


    pid_t pid;
    
    pid = fork();
    if(pid == -1) { 
       perror("Error: Fork Failed with return value -1");
       return false;
    }

    else if (pid ==0){ 
        //printf("Attempting execv \n");
        printf("Command[is %.*s\n", 50, command[count-1]);
	int ret = execv(command[0], &command[0]);
	if (ret == -1){
	
	    perror("Error: ecec faild with return value -1");
	    return(false);
	exit(-1);
		
		
	}
	va_end(args);
	exit(-1);
    }
    
    int status;
    if (waitpid (pid, &status, 0) == -1) return false;
   
    else if ((WEXITSTATUS(status) == 0))
    	return true;
    //retval = WEXITSTATUS(status);
    //printf("The return value is %i \n", retval);
    
    //if (retval == 0) return true;
    	
    else
     return false;
    
    //return false;
	
}
/**
* @param outputfile - The full path to the file to write with command output.
*   This file will be closed at completion of the function call.
* All other parameters, see do_exec above
*/

bool do_exec_redirect(const char *outputfile, int count, ...)
{
    //printf("Made it to redirect \n");
    va_list args;
    va_start(args, count);
    char * command[count+1];
    int i;
    for(i=0; i<count; i++)
    {
        command[i] = va_arg(args, char *);
    }
    command[count] = NULL;
    // this line is to avoid a compile warning before your implementation is complete
    // and may be removed
    command[count] = command[count];

    va_end(args);
    



    int fd = open(outputfile, O_RDWR|O_TRUNC|O_CREAT, 0644);
    //int fd = open(outputfile, 777);
    if (fd < 0) printf("fd open error \n");
  
    int status;
    pid_t pid;
    
    pid = fork();
    if(pid == -1) { 
       printf("Do_exec fork failed \n");
       return false;
    }

    else if (pid ==0){ 
        dup2(fd,1);
        close(fd);
        //printf("Attempting execv \n");
	int ret = execv(command[0], command);
	if ( ret  == -1){
		printf("Do exec exev v failed \n");
		return(false);
	}

	//exit(-1);
    }
    
    waitpid (pid, &status, 0);
    int retval = WEXITSTATUS(status);
    //printf("The return value is %i \n", retval);
    
    if (retval == 0) return true;
    	
    else
    	return false;
}
