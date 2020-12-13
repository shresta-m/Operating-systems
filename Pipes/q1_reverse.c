//OUESTION:
//(1) Parent sets up a string which is read by child, reversed there and read back the parent
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
//here we'll use 2 pipes
//1st one to send the string from parent
//2nd one to send the reversed string from child
int main()
{
    int fd1[2],fd2[2];
    char string[100];
    pid_t pid;
    if((pipe(fd1))== -1)
    {
        fprintf(stderr,"pipe failed");
        return 1;
    }
    if((pipe(fd2))== -1)
    {
        fprintf(stderr,"pipe failed");
        return 1;
    }
    printf("Enter the string to be reversed :\n");
    scanf("%s",string);
    pid = fork();
    if(pid == -1)
    {
        fprintf(stderr,"fork failed");
        return 1;
    }
    //parent block
    else if(pid > 0)
    {
        char rev_str[100];
        close(fd1[0]);//close the read end of pipe 1
        write(fd1[1],string,strlen(string)+1);//write the string to the write end of pipe 1
        close(fd1[1]);//close the write end of pipe 1
        //wait for the child process to complete
        wait(NULL);

        close(fd2[1]);//close the write end 
        read(fd2[0],rev_str,100);//read the reversed string from the read end of pipe 2
        printf("The reversed string : %s \n",rev_str);//print the reversed string
        close(fd2[0]);//close the read end of pipe 2
    }
    else
    {
        char s[100], r[100];
        close(fd1[1]);//close the write end of pipe 1
        read(fd1[0],s,100);//read the string from read end of pipe 1
        close(fd1[0]);//close the read  end  of pipe 1

        //string reversal
        int begin, end, count = 0;
        // Calculating string length
        while (s[count] != '\0')
        count++;
        end = count - 1;
        //string reversal
        for (begin = 0; begin < count; begin++) 
        {
            r[begin] = s[end];
            end--;
         }
        r[begin] = '\0';

        close(fd2[0]);//close read end of pipe 2
        write(fd2[1],r,strlen(r)+1);//write the reversed string to write end of pipe 2
        close(fd2[1]);//close the write end of pipe 2

        exit(0);

    }
    return 0;   
}
