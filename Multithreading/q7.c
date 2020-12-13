//7. Estimation of PI Value using Monte carlo simulation technique (refer the internet for the
//method..) using threads.
//By assuming the radius is one, area of the circle is (pi)r², while square’s area is 4r². If we divide them we get pi/4.
//By counting the total points as aquare_points and the subset of those points that are within the circle also as circle_points,
// by doing the division (circle_points/square_points)*4 we can actually approximate with this experiment the value of pi.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
#include<math.h>
int interval;
float x,y,z;
int circle_points = 0, sq_points = 0; 
void *runner(void *param);
int main(int argc,char *argv[])
{
    if(argc!=2)
    {
        printf("Error!!\nTry ./<filename> interval \n");
        exit(1);
    }
    srand(time(NULL));

    interval = atoi(argv[1]);
    pthread_t tid[interval];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    // create threads of interval size
    for(int i=0;i<interval;i++)
    {
        pthread_create(&tid[i],&attr,runner,NULL);
    }
    //joining all threads
    for(int i=0;i<interval;i++)
    {
        pthread_join(tid[i],NULL);
    }
    
    double pi_value = (double)(4*circle_points)/sq_points;

    printf("The estimated value of pi is %f\n",pi_value);
    printf("\n");
    return 0;
}

void *runner(void *param)
{
    //random numbers are generated and area is calculated
      x = (double)rand()/RAND_MAX;
      y = (double)rand()/RAND_MAX;
      z = x*x+y*y;
      if (z<=1) //if the area is less than 1,then the points are inside the circle
      circle_points++;
        // Total number of points generated 
        sq_points++; 

        pthread_exit(0);
}
