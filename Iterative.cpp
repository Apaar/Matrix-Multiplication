#include<iostream>
#include<cstdlib>
#include<chrono>
using namespace::std;
int n;
float **matrix1,**matrix2,**matrix3;
void init();
void display();
void free_mem();

void inner_product()
{
  for(int i=0;i<n;i++)
  {
    for(int j=0;j<n;j++)
    {
      for(int k=0;k<n;k++)
      {
        matrix3[i][j]+=matrix1[i][k]*matrix2[k][j];
      }
    }
  }
}
int main()
{
  cin >> n;
  //doing brute force
  init();
    typedef chrono::high_resolution_clock Clock;
    Clock::time_point t0 = Clock::now();

    inner_product();
    Clock::time_point t1 = Clock::now();
    chrono::microseconds ms = chrono::duration_cast<chrono::microseconds>(t1 - t0);
    cout << ms.count()/1000000.0 << " sec\n";
  free_mem();
  return 0;
}


void init()
{

  srand(time(0));
  matrix1 = new float*[n];
  matrix2 = new float*[n];
  matrix3 = new float*[n];
  for(int i=0;i<n;i++)
  {
    matrix1[i] = new float[n];
    matrix2[i] = new float[n];
    matrix3[i] = new float[n];
    for(int j=0;j<n;j++)
    {
      cin>>matrix1[i][j];
      matrix3[i][j] = 0.0;
    }
    for(int j=0;j<n;j++)
    {
      cin>>matrix2[i][j];
    }
  }
}
void free_mem()
{
  for(int i=0;i<n;i++)
  {
    delete[] matrix1[i];
    delete[] matrix2[i];
    delete[] matrix3[i];
  }
  delete[] matrix1;
  delete[] matrix2;
  delete[] matrix3;
}

