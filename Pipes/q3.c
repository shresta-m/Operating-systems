//QUESTION:
//(3) Substring generation at child end of a string setup at parent process end.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<string.h>
void substring(char s[], char sub[], int p, int l) {
   int c = 0;
   
   while (c < l) {
      sub[c] = s[p+c-1];
      c++;
   }
   sub[c] = '\0';
}
int main()
{
    int fd1[2],fd2[2];
    int b,e;
    pid_t pid;
    char string[100];
    if((pipe(fd1))== -1)
    {
        fprintf(stderr,"pipe failed");
        return 1;
    }
    if((pipe(fd2))==-1)
    {
        fprintf(stderr,"pipe failed ");
        return 1;
    }
    printf("Enter the string :\n");
    scanf("%s",string);
    printf("Enter the position and length  to display the substring \n");
    scanf("%d %d",&b,&e);
    int a[2];
    a[0]=b;
    a[1]=e;
    pid = fork();
    if(pid == -1)
    {
        fprintf(stderr,"fork failed");
        return 1;
    }
    else if(pid >0)
    {
        close(fd1[0]);//close reading end of pipe 1
        write(fd1[1],string,strlen(string)+1);//write the string to write end  of pipe 1
        close(fd1[1]);//close the writing end

        close(fd2[0]);//close the reading end of pipe 2
        write(fd2[1],&b,sizeof(b));//write the position and length of substring to write end of pipe 2
        write(fd2[1],&e,sizeof(e));
        close(fd2[1]);//close the writing end of pipe 2

        close(fd1[1]);      
    }
    else
    {
        char string[100],sub[100];
        int b,e;
        close(fd1[1]);//close the write end of pipe 1
        read(fd1[0],string,100); //read the string  form read end of pipe 1
        close(fd1[0]);//close the read end of pipe 1

        close(fd2[1]);//close the write end of pipe 2
        read(fd2[0],&b,sizeof(b));//read the position and length value from the read end of pipe 2
        read(fd2[0],&e,sizeof(e));
        close(fd2[0]);//close the read end of pipe 2
        int low = b;
        int high = e;
        printf("Substring :\n");
        substring(string,sub,low,high);
        printf("Required substring is \"%s\"\n", sub);
        
        exit(0);
    }
    wait(NULL);
    return 0;  
}