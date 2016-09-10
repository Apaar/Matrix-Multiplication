#include<iostream>
#include<cstdlib>
#include<chrono>
#include<pthread.h>
using namespace::std;
int num;
float **matrix1,**matrix2,**matrix3;

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
      cin>>matrix1[i][j];
      matrix3[i][j] = 0.0;
    }
    for(int j=0;j<num;j++)
    {
      cin>>matrix2[i][j];
    }
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
void matrix_mul(float **a, float **b, float **c, int n){
  if (n == 1){
    c[0][0] = a[0][0] * b[0][0];
  }



  if (n == 16){
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
    matrix_mul(temp1, temp2, m1, (n / 2)); //m1 = (a11 + a22) (b11 + b22)

    matrix_sum(a21, a22, temp1, (n / 2)); // a21 + a22
    matrix_mul(temp1, b11, m2, (n / 2)); //m2 = (a21 + a22) b11

    matrix_sub(b12, b22, temp1, (n / 2)); // b12 - b22
    matrix_mul(a11, temp1, m3, (n / 2)); //m3 = a11 (b12 - b22)

    matrix_sub(b21, b11, temp1, (n / 2)); // b21 - b11
    matrix_mul(a22, temp1, m4, (n / 2)); //m4 = a22 (b21 - b11)

    matrix_sum(a11, a12, temp1, (n / 2)); // a11 + a12
    matrix_mul(temp1, b22, m5, (n / 2)); //m5 = (a11 + a12) b22

    matrix_sub(a21, a11, temp1, (n / 2)); // a21 - a11
    matrix_sum(b11, b12, temp2, (n / 2)); // b11 + b12
    matrix_mul(temp1, temp2, m6, (n / 2)); //m6 = (a21 - a11) (b11 + b12)

    matrix_sub(a12, a22, temp1, (n / 2)); // a12 - a22
    matrix_sum(b21, b22, temp2, (n / 2)); // b21 + b22
    matrix_mul(temp1, temp2, m7, (n / 2)); //m7 = (a12 - a22) (b21 + b22)

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

  init();

    typedef chrono::high_resolution_clock Clock;
    typedef chrono::milliseconds milliseconds;
    Clock::time_point t0 = Clock::now();

    matrix_mul(matrix1,matrix2,matrix3,num);

    Clock::time_point t1 = Clock::now();
    chrono::microseconds ms = chrono::duration_cast<chrono::microseconds>(t1 - t0);
    //display();
    cout << ms.count()/1000000.0 << " sec\n";

  free_mem();
  return 0;
}
