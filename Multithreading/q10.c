//(10)Longest Common Subsequence (Extra-Credits)
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
char string1[100],string2[100],lcs[100];
int m,n;
int L[100][100]; 
void *runner(void *param);
void *lcs_runner(void *param);
int max(int a, int b)
{
	if(a>b)
	return a;
	else
	{
	  return b;
	}
	
}
int main() 
{  
    printf("Enter the 2 strings for generating the longest common subsequence\n");
    scanf("%s %s",string1,string2);
    m = strlen(string1); 
    n = strlen(string2);
    pthread_t tid,tid1;
    pthread_attr_t attr,attr1;
    //2 threads are created , one to calculate the length of lcs string and another thread to find the lcs string
            pthread_attr_init(&attr);
            pthread_create(&tid,&attr,runner,NULL);
            pthread_join(tid ,NULL);   

            pthread_attr_init(&attr1);
            pthread_create(&tid1,&attr1,lcs_runner,NULL);
            pthread_join(tid1,NULL);

            printf("Longest common subsequence of %s and %s is %s\n",string1,string2,lcs);
    return 0; 
} 
// this runner code is used to calculate length of LCS for string1[0..m-1], string2[0..n-1] 
void *runner(void *param)
{
  /* Following steps build L[m+1][n+1] in bottom up fashion
       L[i][j] contains length of LCS of string1 and string2 */
	for (int i=0; i<=m; i++) 
   { 
     for (int j=0; j<=n; j++) 
     { 
       if (i == 0 || j == 0) 
         L[i][j] = 0; 
       else if (string1[i-1] == string2[j-1]) 
         L[i][j] = L[i-1][j-1] + 1; 
       else
         L[i][j] = max(L[i-1][j], L[i][j-1]); 
     } 
   } 
   pthread_exit(0);
}
//this following code is to find the lcs string
void *lcs_runner( void *param) 
{ 
  int index = L[m][n]; 
   lcs[index] = '\0'; //this stores the lcs string and set the terminating character
   int i = m, j = n; 
   // Start from the right-most-bottom-most corner and 
   // one by one store characters in lcs[] 
   while (i > 0 && j > 0) 
   {  
      if (string1[i-1] == string2[j-1]) //if the current character is same in string1 and string2 ,
      {                                 //then that character will be included in lcs 

          lcs[index-1] = string1[i-1];//put the character into result lcs string and reduce the values of i,j and index
          i--; j--; index--;      
      } 
      // If not same, then find the larger of two and 
      // go in the direction of larger value 
      else if (L[i-1][j] > L[i][j-1]) 
         i--; 
      else
         j--; 
   }
   pthread_exit(0);  
} 
