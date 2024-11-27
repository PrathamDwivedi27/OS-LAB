#include<stdio.h>
#include<unistd.h>

//Get process id and parent id
int main(){
    printf("Parent Process Id: %d\n",getppid());
    printf("Child Process Id: %d\n",getpid());

}