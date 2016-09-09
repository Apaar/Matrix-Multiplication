#include<iostream>
#include<cstdlib>
#include<chrono>
#include<pthread.h>
using namespace::std;
int n;
float **matrix1,**matrix2,**matrix3;
typedef struct
{
     int ra, rb, ca, cb;
} corners;
typedef struct
{
    corners a,b,c;
}args;
void recursive1(corners a, corners b, corners c);
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

void* free_mem()
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

void find_corners(corners a, int i, int j, corners *b)
{
  int rm = a.ra + (a.rb - a.ra)/2 ;
  int cm = a.ca + (a.cb - a.ca)/2 ;
  *b = a;
  if (i==0)  b->rb = rm;
  else       b->ra = rm;
  if (j==0)  b->cb = cm;
  else       b->ca = cm;
}

void* recursive(void* arg10)
{

    args* arg=(args*)arg10;
    corners a=arg->a;
    corners b=arg->b;
    corners c=arg->c;
    
  corners aii[2][2], bii[2][2], cii[2][2];
  int i, j, m, n, p;

  m = a.rb - a.ra;
  n = a.cb - a.ca;
  p = b.cb - b.ca;
  p = b.cb - b.ca;

  for(i=0;i<2;i++)
  {
    for(j=0;j<2;j++)
    {
        find_corners(a, i, j, &aii[i][j]);
        find_corners(b, i, j, &bii[i][j]);
        find_corners(c, i, j, &cii[i][j]);
    }
  }
if(n>=1024){
  pthread_t threads[8];
  args arg1;
  arg1.a=aii[0][0];
  arg1.b=bii[0][0];
  arg1.c=cii[0][0];

  args arg2;
  arg2.a=aii[0][1];
  arg2.b=bii[1][0];
  arg2.c=cii[0][0];

  args arg3;
  arg3.a=aii[0][0];
  arg3.b=bii[0][1];
  arg3.c=cii[0][1];

  args arg4;
  arg4.a=aii[0][1];
  arg4.b=bii[1][1];
  arg4.c=cii[0][1];

  args arg5;
  arg5.a=aii[1][0];
  arg5.b=bii[0][0];
  arg5.c=cii[1][0];

  args arg6;
  arg6.a=aii[1][1];
  arg6.b=bii[1][0];
  arg6.c=cii[1][0];

  args arg7;
  arg7.a=aii[1][0];
  arg7.b=bii[0][1];
  arg7.c=cii[1][1];

  args arg8;
  arg8.a=aii[1][1];
  arg8.b=bii[1][1];
  arg8.c=cii[1][1];

  pthread_create(&threads[0], NULL, recursive, (void*)&arg1);
  pthread_create(&threads[1], NULL, recursive, (void*)&arg2);
  pthread_create(&threads[2], NULL, recursive, (void*)&arg3);
  pthread_create(&threads[3], NULL, recursive, (void*)&arg4);
  pthread_create(&threads[4], NULL, recursive, (void*)&arg5);
  pthread_create(&threads[5], NULL, recursive, (void*)&arg6);
  pthread_create(&threads[6], NULL, recursive, (void*)&arg7);
  pthread_create(&threads[7], NULL, recursive, (void*)&arg8);

  pthread_join(threads[0], NULL);
  pthread_join(threads[1], NULL);
  pthread_join(threads[2], NULL);
  pthread_join(threads[3], NULL);
  pthread_join(threads[4], NULL);
  pthread_join(threads[5], NULL);
  pthread_join(threads[6], NULL);
  pthread_join(threads[7], NULL);
}

else{
	recursive1(aii[0][0], bii[0][0], cii[0][0] );
  recursive1(aii[0][1], bii[1][0], cii[0][0] );
  recursive1(aii[0][0], bii[0][1], cii[0][1] );
  recursive1(aii[0][1], bii[1][1], cii[0][1] );
  recursive1(aii[1][0], bii[0][0], cii[1][0] );
  recursive1(aii[1][1], bii[1][0], cii[1][0] );
  recursive1(aii[1][0], bii[0][1], cii[1][1] );
  recursive1(aii[1][1], bii[1][1], cii[1][1] );
  }

}

void recursive1(corners a, corners b, corners c)
{
  corners aii[2][2], bii[2][2], cii[2][2];
  int i, j, m, n, p;

  m = a.rb - a.ra;
  n = a.cb - a.ca;
  p = b.cb - b.ca;
  p = b.cb - b.ca;
  if (n==1)
  {
    matrix3[c.ra][c.ca] += matrix1[a.ra][a.ca] * matrix2[b.ra][b.ca];
    return;
  }
  if(n==16)
  {
      for(int i=0;i<16;i++)
        {
            for(int j=0;j<16;j++)
            {
                for(int k=0;k<16;k++)
                {
                    matrix3[c.ca+i][c.ra+j]+=matrix1[a.ca+i][a.ra+k]*matrix2[b.ca+k][b.ra+j];
                }
            }
        }
        return;
      //cout<<a.ca<<" "<<a.cb<<" "<<a.ra<<" "<<a.rb<<"\n";
       // cout<<b.ca<<" "<<b.cb<<" "<<b.ra<<" "<<b.rb<<"\n";
       // cout<<c.ca<<" "<<c.cb<<" "<<c.ra<<" "<<c.rb<<"\n\n";
  }
  for(i=0;i<2;i++)
  {
    for(j=0;j<2;j++)
    {
        find_corners(a, i, j, &aii[i][j]);
        find_corners(b, i, j, &bii[i][j]);
        find_corners(c, i, j, &cii[i][j]);
    }
  }
  recursive1(aii[0][0], bii[0][0], cii[0][0] );
  recursive1(aii[0][1], bii[1][0], cii[0][0] );
  recursive1(aii[0][0], bii[0][1], cii[0][1] );
  recursive1(aii[0][1], bii[1][1], cii[0][1] );
  recursive1(aii[1][0], bii[0][0], cii[1][0] );
  recursive1(aii[1][1], bii[1][0], cii[1][0] );
  recursive1(aii[1][0], bii[0][1], cii[1][1] );
  recursive1(aii[1][1], bii[1][1], cii[1][1] );
}

args* arg1=(args*)malloc(sizeof(args));

int main()
{
	cin >> n;

	init();
	
    pthread_t threads;
	corners ai = {0,n,0,n};
    corners bi = {0,n,0,n};
    corners ci = {0,n,0,n};

    arg1->a=ai;
    arg1->b=bi;
    arg1->c=ci;

    typedef chrono::high_resolution_clock Clock;
    typedef chrono::milliseconds milliseconds;
    Clock::time_point t0 = Clock::now();
    if(n<1024)
    {
    	recursive1(ai,bi,ci);
    }
    else
	recursive((void*)arg1);	
    Clock::time_point t1 = Clock::now();
    chrono::microseconds ms = chrono::duration_cast<chrono::microseconds>(t1 - t0);

    cout << ms.count()/1000000.0 << " sec\n";
	free_mem();
	return 0;
}