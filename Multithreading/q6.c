//(6)Implement Merge Sort and Quick Sort in a multithreaded fashion.
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<pthread.h>
int arr[100],arr_size;
int arr_q[100];
struct data
{
    int beg,end,mid;
};
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
/* This function takes last element as pivot, places 
   the pivot element at its correct position in sorted 
    array, and places all smaller (smaller than pivot) 
   to left of pivot and all greater elements to right 
   of pivot */
int partition (int low, int high) 
{ 
    int pivot = arr_q[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  
    for (int j = low; j <= high- 1; j++) 
    { 
        // If current element is smaller than the pivot 
        if (arr_q[j] < pivot) 
        { 
            i++;    // increment index of smaller element 
            swap(&arr_q[i], &arr_q[j]); 
        } 
    } 
    swap(&arr_q[i + 1], &arr_q[high]); 
    return (i + 1); 
} 
  
/* The main function that implements QuickSort 
 arr[] --> Array to be sorted, 
  low  --> Starting index, 
  high  --> Ending index */
void *quickSort(void *param) 
{ 
    struct data *c = ((struct data *)param);
    int low = c->beg;
    int high = c->end;
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(low, high); 
        struct data al;
        al.beg =low;al.end = pi-1;
        struct data ar;
        ar.beg = pi+1;ar.end = high;
  
        // Separately sort elements before 
        // partition and after partition  using 2 threads
        pthread_t tid[2];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_create(&tid[0],&attr,quickSort,&al);
        pthread_create(&tid[1],&attr,quickSort,&ar);
        //join 2 threads
        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);
    }
    pthread_exit(0); 
} 
void merge( int l, int m, int r) 
{ 
    int i, j, k; 
    int n1 = m - l + 1; 
    int n2 = r - m; 
 
    /* create temp arrays */
    int L[n1], R[n2]; 
 
    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++) 
        L[i] = arr[l + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[m + 1 + j]; 
 
    // Merge the temp arrays back into arr[l..r]
    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2) { 
        if (L[i] <= R[j]) { 
            arr[k] = L[i]; 
            i++; 
        } 
        else { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    //Copy the remaining elements of L[], if there  are any
    while (i < n1) { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
    // Copy the remaining elements of R[], if there are any
    while (j < n2) { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
/* l is for left index and r is right index of the 
sub-array of arr to be sorted */
void *mergeSort(void *d) 
{ 
    struct data *b = ((struct data *)d);
    int l =b->beg ;
    int r =b->end ;
    if (l < r) { 
        // Same as (l+r)/2, but avoids overflow for 
        // large l and h 
        int m = l + (r - l) / 2; 
        struct data  msl;
        msl.beg = l;
        msl.end = m;
        struct data msr;
        msr.beg = m+1;
        msr.end = r;
        pthread_t tid[2];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
    // Sort first and second halves using 2 threads
        pthread_create(&tid[0],&attr,mergeSort,&msl);
        pthread_create(&tid[1],&attr,mergeSort,&msr);
        //join 2 threads
        pthread_join(tid[0],NULL);
        pthread_join(tid[1],NULL);

        merge(l, m, r); 
    } 
    pthread_exit(0);
} 
void printArray(int A[], int size) 
{ 
    int i; 
    for (i = 0; i < size; i++) 
        printf("%d ", A[i]); 
    printf("\n"); 
} 
int main(int argc,char *argv[]) 
{ 
     arr_size=atoi(argv[1]);
	if(argc!=arr_size+2) {printf("invalid input\n");exit(0);}
	
	for(int i=0;i<arr_size;++i)
	{
		arr[i]=atoi(argv[i+2]);
        arr_q[i] = atoi(argv[i+2]);
	} 
   struct data array;
   array.beg =0;
   array.end = arr_size -1;
   pthread_t tid1;
   pthread_attr_t attr1;
   pthread_attr_init(&attr1);
   pthread_create(&tid1,&attr1,mergeSort,&array);//this thread carries out merge sort
   pthread_join(tid1,NULL);

   pthread_t tid2;
   pthread_attr_t attr2;
   pthread_attr_init(&attr2);
   pthread_create(&tid2,&attr2,quickSort,&array);//this thread carries out quick sort
   pthread_join(tid2,NULL);
 
    printf("\nSorted array after merge sort:\n"); 
    printArray(arr, arr_size); 
    printf("\nSorted array after quick sort:\n"); 
    printArray(arr_q, arr_size); 
    return 0; 
} 
