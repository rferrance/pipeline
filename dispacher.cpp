#include <fcntl.h>              /* Obtain O_* constant definitions */

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
using namespace std;

int main()
{
    pid_t pid1, pid2;
    int pipefd[2]; 
    char buf;

    pipe(pipefd);
    
    pid1 = fork();
    if(pid1 == -1) {
	    fprintf(stderr, "Failure forking");
        _exit(0);
    }
    else if(pid1 == 0) { // this is the child process
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        pid1 = getpid();
        if(-1 ==execve("./generator", NULL, NULL)) {
	        perror("Error calling execve");
	        _exit(0);
	    }
	    
    }
    
    pid2 = fork();
    
    if(pid2 == -1) {
	    fprintf(stderr, "Failure forking");
        _exit(0);
    }
    else if(pid2 == 0) {
        close(pipefd[1]);
        dup2(pipefd[0], STDIN_FILENO);
        pid2 = getpid();
        if ( -1 == execve("./consumer", NULL, NULL)) {
	        perror("Error calling execve");
	        _exit(0);
	    }
    }
    
    
    sleep(1);
    
    kill(pid1, SIGTERM);
    
    close(pipefd[0]); // close the read end of parent's write pipe
	close(pipefd[1]); //close the write end of parent's read pipe
    
    int status;
    waitpid(pid1, &status, 0);
    
    std::cerr << "Parent waited for child[" << pid1 << "] to exit with status " << status << std::endl;
    
    int status1;
    waitpid(pid2, &status1, 0);
    
    std::cerr << "Parent waited for child[" << pid2 << "] to exit with status " << status1 << std::endl;
    
    
    
    return 0;
}

