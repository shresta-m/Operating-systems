//QUESTION:
//(2) Parent sets up string 1 and child sets up string 2. String 2 concatenated to string 1 at parent end
//and then read back at the child end.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
//here we'll use 2 pipes
//1st one to send the string from child to parent
//2nd one to send the concatenated string from parent to child 
int main()
{
    int fd1[2];
    int fd2[2];
    char string1[100],string2[100];
    pid_t pid;
    if((pipe(fd1))== -1)
    {
       fprintf(stderr,"pipe failed ");
       return 1; 
    }
    if((pipe(fd2))== -1)
    {
        fprintf(stderr,"pipe failed");
        return 1;
    }
    printf("Enter the 1st string \n");
    scanf("%s",string1);
    printf("Enter the 2nd string \n");
    scanf("%s",string2);

    pid = fork();
    if(pid == -1)
    {
        fprintf(stderr,"fork failed ");
        return 1;
    }
    //child block
    else if( pid == 0)
    {
        char concat_str[100];
        close(fd1[0]);//close the read end of pipe1 
        write(fd1[1],string2, strlen(string2)+1);//write the string 2 to write end and close
        close(fd1[1]);
        //wait for the parent to complete
        wait(NULL);

        close(fd2[1]);//close the write end of 2nd pipe
        read(fd2[0],string1,100);//read the concatenated string from the read end of pipe 2 and it is printed
        printf("The concatenated string : %s \n",string1);
        close(fd2[0]);

    }
    //parent block
    else
    {
        char concat_str[100];
        close(fd1[1]);//close the write end of pipe 1
        read(fd1[0],concat_str,100);//read the string2 from the read end of pipe 1
        close(fd1[0]);//close the read end of pipe 1
        strcat(string1,concat_str);//concatenate string2 to string1
        //string1=>string1 concatenated with string2
        close(fd2[0]);//close the reading end of pipe 2
        write(fd2[1],string1,strlen(string1)+1);//write the concatenated string to write end of pipe 2
        close(fd2[1]);//close the write end of pipe 2

        exit(0);
    }
    return 0;
}