#include<iostream>
#include<cstdlib>
#include<chrono>
#include<pthread.h>
using namespace::std;
int num;
float **matrix1,**matrix2,**matrix3;

typedef struct
{
    float **a1,**b1,**c1;
    int num1;
}args;

void* matrix_mul1(void* arguments);

void init()
{

	srand(time(0));
	matrix1 = new float*[num];
	matrix2 = new float*[num];
	matrix3 = new float*[num];
	for(int i=0;i<num;i++)
	{
		matrix1[i] = new float[num];
		matrix2[i] = new float[num];
		matrix3[i] = new float[num];
		for(int j=0;j<num;j++)
		{
			matrix1[i][j] = (float)(rand() % 100 + 1);
			matrix3[i][j] = 0.0;
		}
		for(int j=0;j<num;j++)
		{
			matrix2[i][j] = (float)(rand() % 100 + 1);
		}
	}
}
void display()
{
	cout<<"MATRIX 1\n";
	for(int i=0;i<num;i++)
	{
		for(int j=0;j<num;j++)
		{
			cout<<matrix1[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\nMATRIX 2\n";
	for(int i=0;i<num;i++)
	{
		for(int j=0;j<num;j++)
		{
			cout<<matrix2[i][j]<<" ";
		}
		cout<<"\n";
	}
	cout<<"\nMATRIX 3\n";
	for(int i=0;i<num;i++)
	{
		for(int j=0;j<num;j++)
		{
			cout<<matrix3[i][j]<<" ";
		}
		cout<<"\n";
	}
}
void* free_mem()
{
	for(int i=0;i<num;i++)
	{
		delete[] matrix1[i];
		delete[] matrix2[i];
		delete[] matrix3[i];
	}
	delete[] matrix1;
	delete[] matrix2;
	delete[] matrix3;
}
void matrix_sum(float **a, float **b, float **c, int n){
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++){
		c[i][j] = a[i][j] + b[i][j];
	}
}
void matrix_sub(float **a, float **b, float **c, int n){
	for (int i = 0; i < n; i++)
	for (int j = 0; j < n; j++){
		c[i][j] = a[i][j] - b[i][j];
	}
}
void* matrix_mul(void* arguments){
    args* arg=(args*)arguments;
    float **a=arg->a1;
    float **b=arg->b1;
    float **c=arg->c1;
    int n=arg->num1;
	if (n == 1){
		c[0][0] = a[0][0] * b[0][0];
		return NULL;
	}
	if (n <= 64){
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<n;k++)
                {
                    c[i][j]+=a[i][k]*b[k][j];
                }
            }
        }
        return NULL;
	}
	else{
		float **a11 = new float*[(n / 2)];
		float **a12 = new float*[(n / 2)];
		float **a21 = new float*[(n / 2)];
		float **a22 = new float*[(n / 2)];
		float **b11 = new float*[(n / 2)];
		float **b12 = new float*[(n / 2)];
		float **b21 = new float*[(n / 2)];
		float **b22 = new float*[(n / 2)];
		float **c11 = new float*[(n / 2)];
		float **c12 = new float*[(n / 2)];
		float **c21 = new float*[(n / 2)];
		float **c22 = new float*[(n / 2)];
		float **temp1 = new float*[(n / 2)];
		float **temp2 = new float*[(n / 2)];
		float **temp3 = new float*[(n / 2)];
		float **temp4 = new float*[(n / 2)];
		float **temp5 = new float*[(n / 2)];
		float **temp6 = new float*[(n / 2)];
		float **temp7 = new float*[(n / 2)];
		float **temp8 = new float*[(n / 2)];
		float **temp9 = new float*[(n / 2)];
		float **temp10 = new float*[(n / 2)];
		float **m1 = new float*[(n / 2)];
		float **m2 = new float*[(n / 2)];
		float **m3 = new float*[(n / 2)];
		float **m4 = new float*[(n / 2)];
		float **m5 = new float*[(n / 2)];
		float **m6 = new float*[(n / 2)];
		float **m7 = new float*[(n / 2)];
		for (int i = 0; i < (n / 2); i++){
			a11[i] = new float[(n / 2)];
			a12[i] = new float[(n / 2)];
			a21[i] = new float[(n / 2)];
			a22[i] = new float[(n / 2)];
			b11[i] = new float[(n / 2)];
			b12[i] = new float[(n / 2)];
			b21[i] = new float[(n / 2)];
			b22[i] = new float[(n / 2)];
			c11[i] = new float[(n / 2)];
			c12[i] = new float[(n / 2)];
			c21[i] = new float[(n / 2)];
			c22[i] = new float[(n / 2)];
			temp1[i] = new float[(n / 2)];
			temp2[i] = new float[(n / 2)];
			temp3[i] = new float[(n / 2)];
			temp4[i] = new float[(n / 2)];
			temp5[i] = new float[(n / 2)];
			temp6[i] = new float[(n / 2)];
			temp7[i] = new float[(n / 2)];
			temp8[i] = new float[(n / 2)];
			temp9[i] = new float[(n / 2)];
			temp10[i] = new float[(n / 2)];	
			m1[i] = new float[n / 2];
			m2[i] = new float[n / 2];
			m3[i] = new float[n / 2];
			m4[i] = new float[n / 2];
			m5[i] = new float[n / 2];
			m6[i] = new float[n / 2];
			m7[i] = new float[n / 2];
		}
		for (int i = 0; i < (n / 2); i++)
		for (int j = 0; j < (n / 2); j++){
			a11[i][j] = a[i][j];
			a12[i][j] = a[i][j + (n / 2)];
			a21[i][j] = a[i + (n / 2)][j];
			a22[i][j] = a[i + (n / 2)][j + (n / 2)];

			b11[i][j] = b[i][j];
			b12[i][j] = b[i][j + (n / 2)];
			b21[i][j] = b[i + (n / 2)][j];
			b22[i][j] = b[i + (n / 2)][j + (n / 2)];
		}
		matrix_sum(a11, a22, temp1, (n / 2)); // a11 + a22
		matrix_sum(b11, b22, temp2, (n / 2)); // b11 + b2
		pthread_t threads[7];
		args arg1;
		arg1.a1=temp1;
		arg1.b1=temp2;
		arg1.c1=m1;
		arg1.num1=(n / 2);
        	pthread_create(&threads[0], NULL, matrix_mul1, (void*)&arg1);
		//m1 = (a11 + a22) (b11 + b22)
		matrix_sum(a21, a22, temp3, (n / 2)); // a21 + a22
		args arg2;
		arg2.a1=temp3;
		arg2.b1=b11;
		arg2.c1=m2;
		arg2.num1=(n / 2);
		pthread_create(&threads[1], NULL, matrix_mul, (void*)&arg2); //m2 = (a21 + a22) b11
		matrix_sub(b12, b22, temp4, (n / 2)); // b12 - b22
		args arg3;
		arg3.a1=a11;
		arg3.b1=temp4;
		arg3.c1=m3;
		arg3.num1=(n / 2);
		pthread_create(&threads[2], NULL, matrix_mul1, (void*)&arg3); //m3 = a11 (b12 - b22)
		matrix_sub(b21, b11, temp5, (n / 2)); // b21 - b11
		args arg4;
		arg4.a1=a22;
		arg4.b1=temp5;
		arg4.c1=m4;
		arg4.num1=(n / 2);
		pthread_create(&threads[3], NULL, matrix_mul1, (void*)&arg4); //m4 = a22 (b21 - b11)
		matrix_sum(a11, a12, temp6, (n / 2)); // a11 + a12
		args arg5;
		arg5.a1=temp6;
		arg5.b1=b22;
		arg5.c1=m5;
		arg5.num1=(n / 2);
		pthread_create(&threads[4], NULL, matrix_mul1, (void*)&arg5); //m5 = (a11 + a12) b22
		matrix_sub(a21, a11, temp7, (n / 2)); // a21 - a11
		matrix_sum(b11, b12, temp8, (n / 2)); // b11 + b12
		args arg6;
		arg6.a1=temp7;
		arg6.b1=temp8;
		arg6.c1=m6;
		arg6.num1=(n / 2);
		pthread_create(&threads[5], NULL, matrix_mul1, (void*)&arg6); //m6 = (a21 - a11) (b11 + b12)
		matrix_sub(a12, a22, temp9, (n / 2)); // a12 - a22
		matrix_sum(b21, b22, temp10, (n / 2)); // b21 + b22
		args arg7;
		arg7.a1=temp9;
		arg7.b1=temp10;
		arg7.c1=m7;
		arg7.num1=(n / 2);
		pthread_create(&threads[6], NULL, matrix_mul1, (void*)&arg7); //m7 = (a12 - a22) (b21 + b22)
		pthread_join(threads[0], NULL);
          	pthread_join(threads[1], NULL);
          	pthread_join(threads[2], NULL);
          	pthread_join(threads[3], NULL);
          	pthread_join(threads[4], NULL);
          	pthread_join(threads[5], NULL);
          	pthread_join(threads[6], NULL);
		matrix_sum(m1, m4, temp1, n / 2); // m1 + m4
		matrix_sum(temp1, m7,temp2, n / 2); // m1 + m4 + m7
		matrix_sub(temp2, m5, c11, n / 2);// c11 = m1 + m4 - m5 + m7
		matrix_sum(m3, m5, c12, n / 2); // c12 = m3 + m5
		matrix_sum(m2, m4, c21, n / 2); // c21 = m2 + m4
		matrix_sum(m1, m3, temp1, n / 2); // m1 + m3
		matrix_sum(temp1, m6, temp2, n / 2); //m1 + m3 + m6
		matrix_sub(temp2, m2, c22, n / 2); // c22 = m1 - m2 + m3 + m6
		for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++){
			c[i][j] = c11[i][j];
			c[i][j + (n / 2)] = c12[i][j];
			c[i + (n / 2)][j] = c21[i][j];
			c[i + (n / 2)][j + (n / 2)] = c22[i][j];
		}
		for (int i = 0; i < (n / 2); i++){
			delete[] a11[i];
			delete[] a12[i];
			delete[] a21[i];
			delete[] a22[i];
			delete[] b11[i];
			delete[] b12[i];
			delete[] b21[i];
			delete[] b22[i];
			delete[] c11[i];
			delete[] c12[i];
			delete[] c21[i];
			delete[] c22[i];
			delete[] temp1[i];
			delete[] temp2[i];
		}
	}
}
void* matrix_mul1(void* arguments){
	args* arg=(args*)arguments;
    	float **a=arg->a1;
    	float **b=arg->b1;
    	float **c=arg->c1;
    	int n=arg->num1;
    	
    	if (n == 1){
		c[0][0] = a[0][0] * b[0][0];
	}

	if (n == 32){
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<n;k++)
                {
                    c[i][j]+=a[i][k]*b[k][j];
                }
            }
        }
	}
	else{
		float **a11 = new float*[(n / 2)];
		float **a12 = new float*[(n / 2)];
		float **a21 = new float*[(n / 2)];
		float **a22 = new float*[(n / 2)];
		float **b11 = new float*[(n / 2)];
		float **b12 = new float*[(n / 2)];
		float **b21 = new float*[(n / 2)];
		float **b22 = new float*[(n / 2)];
		float **c11 = new float*[(n / 2)];
		float **c12 = new float*[(n / 2)];
		float **c21 = new float*[(n / 2)];
		float **c22 = new float*[(n / 2)];
		float **temp1 = new float*[(n / 2)];
		float **temp2 = new float*[(n / 2)];
		float **temp3 = new float*[(n / 2)];
		float **temp4 = new float*[(n / 2)];
		float **temp5 = new float*[(n / 2)];
		float **temp6 = new float*[(n / 2)];
		float **temp7 = new float*[(n / 2)];
		float **temp8 = new float*[(n / 2)];
		float **temp9 = new float*[(n / 2)];
		float **temp10 = new float*[(n / 2)];
		float **m1 = new float*[(n / 2)];
		float **m2 = new float*[(n / 2)];
		float **m3 = new float*[(n / 2)];
		float **m4 = new float*[(n / 2)];
		float **m5 = new float*[(n / 2)];
		float **m6 = new float*[(n / 2)];
		float **m7 = new float*[(n / 2)];
		for (int i = 0; i < (n / 2); i++){
			a11[i] = new float[(n / 2)];
			a12[i] = new float[(n / 2)];
			a21[i] = new float[(n / 2)];
			a22[i] = new float[(n / 2)];
			b11[i] = new float[(n / 2)];
			b12[i] = new float[(n / 2)];
			b21[i] = new float[(n / 2)];
			b22[i] = new float[(n / 2)];
			c11[i] = new float[(n / 2)];
			c12[i] = new float[(n / 2)];
			c21[i] = new float[(n / 2)];
			c22[i] = new float[(n / 2)];
			temp1[i] = new float[(n / 2)];
			temp2[i] = new float[(n / 2)];
			temp3[i] = new float[(n / 2)];
			temp4[i] = new float[(n / 2)];
			temp5[i] = new float[(n / 2)];
			temp6[i] = new float[(n / 2)];
			temp7[i] = new float[(n / 2)];
			temp8[i] = new float[(n / 2)];
			temp9[i] = new float[(n / 2)];
			temp10[i] = new float[(n / 2)];			
			m1[i] = new float[n / 2];
			m2[i] = new float[n / 2];
			m3[i] = new float[n / 2];
			m4[i] = new float[n / 2];
			m5[i] = new float[n / 2];
			m6[i] = new float[n / 2];
			m7[i] = new float[n / 2];
		}
		for (int i = 0; i < (n / 2); i++)
		for (int j = 0; j < (n / 2); j++){
			a11[i][j] = a[i][j];
			a12[i][j] = a[i][j + (n / 2)];
			a21[i][j] = a[i + (n / 2)][j];
			a22[i][j] = a[i + (n / 2)][j + (n / 2)];
			b11[i][j] = b[i][j];
			b12[i][j] = b[i][j + (n / 2)];
			b21[i][j] = b[i + (n / 2)][j];
			b22[i][j] = b[i + (n / 2)][j + (n / 2)];
		}
		matrix_sum(a11, a22, temp1, (n / 2)); // a11 + a22
		matrix_sum(b11, b22, temp2, (n / 2)); // b11 + b22
		pthread_t threads[7];
		args arg1;
		arg1.a1=temp1;
		arg1.b1=temp2;
		arg1.c1=m1;
		arg1.num1=(n / 2);
        	matrix_mul1((void*)&arg1);
		//m1 = (a11 + a22) (b11 + b22)
		matrix_sum(a21, a22, temp3, (n / 2)); // a21 + a22
		args arg2;
		arg2.a1=temp3;
		arg2.b1=b11;
		arg2.c1=m2;
		arg2.num1=(n / 2);
		matrix_mul1((void*)&arg2);
		matrix_sub(b12, b22, temp4, (n / 2)); // b12 - b22
		args arg3;
		arg3.a1=a11;
		arg3.b1=temp4;
		arg3.c1=m3;
		arg3.num1=(n / 2);
		matrix_mul1((void*)&arg3);
		matrix_sub(b21, b11, temp5, (n / 2)); // b21 - b11
		args arg4;
		arg4.a1=a22;
		arg4.b1=temp5;
		arg4.c1=m4;
		arg4.num1=(n / 2);
		matrix_mul1((void*)&arg4);
		matrix_sum(a11, a12, temp6, (n / 2)); // a11 + a12
	args arg5;
		arg5.a1=temp6;
		arg5.b1=b22;
		arg5.c1=m5;
		arg5.num1=(n / 2);
		matrix_mul1((void*)&arg5);
		matrix_sub(a21, a11, temp7, (n / 2)); // a21 - a11
		matrix_sum(b11, b12, temp8, (n / 2)); // b11 + b12
		args arg6;
		arg6.a1=temp7;
		arg6.b1=temp8;
		arg6.c1=m6;
		arg6.num1=(n / 2);
		matrix_mul1((void*)&arg6);
		matrix_sub(a12, a22, temp9, (n / 2)); // a12 - a22
		matrix_sum(b21, b22, temp10, (n / 2)); // b21 + b22
		args arg7;
		arg7.a1=temp9;
		arg7.b1=temp10;
		arg7.c1=m7;
		arg7.num1=(n / 2);
		matrix_mul1((void*)&arg7);
		matrix_sum(m1, m4, temp1, n / 2); // m1 + m4
		matrix_sum(temp1, m7,temp2, n / 2); // m1 + m4 + m7
		matrix_sub(temp2, m5, c11, n / 2);// c11 = m1 + m4 - m5 + m7
	matrix_sum(m3, m5, c12, n / 2); // c12 = m3 + m5
		matrix_sum(m2, m4, c21, n / 2); // c21 = m2 + m4
		matrix_sum(m1, m3, temp1, n / 2); // m1 + m3
		matrix_sum(temp1, m6, temp2, n / 2); //m1 + m3 + m6
		matrix_sub(temp2, m2, c22, n / 2); // c22 = m1 - m2 + m3 + m6	
		for (int i = 0; i < n / 2; i++)
		for (int j = 0; j < n / 2; j++){
			c[i][j] = c11[i][j];
			c[i][j + (n / 2)] = c12[i][j];
			c[i + (n / 2)][j] = c21[i][j];
			c[i + (n / 2)][j + (n / 2)] = c22[i][j];
		}
		for (int i = 0; i < (n / 2); i++){
			delete[] a11[i];
			delete[] a12[i];
			delete[] a21[i];
			delete[] a22[i];
			delete[] b11[i];
			delete[] b12[i];
			delete[] b21[i];
			delete[] b22[i];
			delete[] c11[i];
			delete[] c12[i];
			delete[] c21[i];
			delete[] c22[i];
			delete[] temp1[i];
			delete[] temp2[i];
		}
	}
}

int main()
{
	cin >> num;
    pthread_t threads;
	init();
    args* arg1=(args*)malloc(sizeof(args));
    arg1->a1=matrix1;
    arg1->b1=matrix2;
    arg1->c1=matrix3;
    arg1->num1=num;
    typedef chrono::high_resolution_clock Clock;
    typedef chrono::milliseconds milliseconds;
    Clock::time_point t0 = Clock::now();
    matrix_mul((void*)arg1);

    Clock::time_point t1 = Clock::now();
    chrono::microseconds ms = chrono::duration_cast<chrono::microseconds>(t1 - t0);
    //display();
    cout << ms.count() << " sec\n";

	free_mem();
	return 0;
}