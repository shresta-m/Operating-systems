//8. Computation of a Matrix Inverse using Determinant, Cofactor threads, etc.
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
int N;
int adj[100][100];
float inv[100][100];
int a[100][100];
struct data{
	int i;
	int j;
};
void *runner(void *param);
int co_fac(int mat[100][100],int temp[100][100], int p, int q, int x);
//recursive function to find the determinant of matrix
int det(int mat[100][100], int z)
{
	int D=0;
	if(z==1)//base case : if array contains single element
		return mat[0][0];

	int temp[z][z];//to store cofactors
	int sign=1;//to store sign multiplier
    //iterate for each element in first row
	for(int f=0; f<z; f++){
		co_fac(mat, temp, 0, f, z);//get the cofactors for a[0][f]
		D += sign * mat[0][f] * det(temp, z-1);

		sign=-sign;
	}
	return D;
}
int co_fac(int mat[100][100],int temp[100][100], int p, int q, int x) 
{ 
    int i = 0, j = 0; 
    // Looping for each element of the matrix 
    for (int row = 0; row < x; row++) 
    { 
        for (int col = 0; col < x; col++) 
        { 
            //  Copying into temporary matrix only those element 
            //  which are not in given row and column 
            if (row != p && col != q) 
            { 
                temp[i][j++] = mat[row][col]; 
                // Row is filled, so increase row index and 
                // reset col index 
                if (j == x - 1) 
                { 
                    j = 0; 
                    i++; 
                } 
            } 
        } 
    } 
}
void *runner(void *param)
{
    struct data *x = ((struct data *)param);
    int i = x->i;
    int j = x->j;
    int sign =1,temp[N][N];
    co_fac(a, temp, i, j, N); //get cofactor of a[i][j]
            // sign of adj[j][i] positive if sum of row 
            // and column indexes is even. 
            sign = ((i+j)%2==0)? 1: -1; 
            // Interchanging rows and columns to get the 
            // transpose of the cofactor matrix 
            adj[j][i] = (sign)*(det(temp, N-1)); 

            pthread_exit(0);
} 
int main()
{
	printf("Enter the order of matrix \N");
	scanf("%d",&N);
	printf("Enter the matrix elements\N");
	for(int i=0;i<N;i++){
	for(int j=0;j<N;j++)
	{
		scanf("%d",&a[i][j]);
	}
	}
    //N*N threads are created 
    pthread_t tid[N*N];
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    if (N == 1) 
    { 
        adj[0][0] = 1; 
    } 
    else
    {
        int k=0;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                struct data *mat = (struct data *)malloc(sizeof(struct data));
                mat->i = i;
                mat->j = j;
                pthread_create(&tid[k],&attr,runner,mat);
                k++;
            }
        }
        //joining all k threads
        for(int i=0;i<k;i++)
        pthread_join(tid[i],NULL);
    }
    
    printf("Adjoint Matrix:\N");
    for(int i=0; i<N; i++) 
    { 
        for(int j=0; j<N; j++) {
            printf("%d\t",adj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
	int determinant = det(a, N); 
    if (det == 0) 
    { 
         printf("Singular matrix, can't find its inverse\n"); 
        return 0; 
    }  
    // Find Inverse using formula "inverse(A) = adj(A)/det(A)" 
    for (int i=0; i<N; i++) 
        for (int j=0; j<N; j++) 
            inv[i][j] = adj[i][j]/(float)(determinant);

    printf("Inverse Matrix:\n");
    for(int i=0; i<N; i++) 
    { 
        for(int j=0; j<N; j++) {
            printf("%f\t",inv[i][j]);
        }
        printf("\n");
    }         
	return 0;
}

