#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <fstream>

using namespace std;

double rand1()
{

    return rand() % 1001 / 1000.0;
}

void pokaz(int** space, int L) //function for showing currecnt pozition
{
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
        {
            cout << space[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    fstream plik,plik1,plik2;
    plik1.open("D od K.txt",ios::out);
    plik2.open("D od C.txt",ios::out);
    plik.open("trajektoria.txt",ios::out);
    int L = 20, n = 200; //declaration of space size LxL and number of particles n
    srand(time(NULL));
    int** space = new int* [L];
    int pom=0;
    int* dx=NULL;
    int* dy=NULL;
    int * x=NULL;
    int * y=NULL;
    double * dRxR=NULL;
    double DR2=0,DR2_sr=0;
    double D=0;
    double C=0;
    for (int i = 0; i < L; i++)  //creation and setting to 0 space LxL
    {
        space[i] = new int[L];
        for (int j = 0; j < L; j++)
        {
            space[i][j] = 0;
        }
    }
    int* INext = new int[L]; //creation of array for neighbours for moving right/up
    for (int i = 0; i < L; i++)
    {
        INext[i] = i + 1;
    }
    INext[L - 1] = 0;
    int* IPrev = new int[L];    //utworzenie tablicy sasiadow dla przesuniecia left/down
    for (int i = 0; i < L; i++)
    {
        IPrev[i] = i - 1;
    }
    IPrev[0] = L-1;
for(int N=n;N<n+1;N++) //monte-carlo loop (change of number of atoms->change of concentration C=n(L^-2)
{

    if(dx!=NULL)
    {
        delete[] dx;
        dx=NULL;
    }
    if(dy!=NULL)
    {
       delete[] dy;
       dy=NULL;
    }
    if(dRxR!=NULL)
    {
        delete[] dRxR;
        dRxR=NULL;
    }
    if(x!=NULL)
    {
       delete[] x;
       x=NULL;
    }
    if(y!=NULL)
    {
       delete[] y;
       y=NULL;
    }
    dx = new int[N];
    dy = new int[N];
    dRxR=new double[N];
    x = new int[N];    //table of position
    y = new int[N];    //table of position

    //pokaz(space, L);


    for(int K=1;K<61;K++) //monte carlo steps loop (change in number of iterations)
    {
        DR2_sr = 0;
        for (int nr = 0; nr < 30; nr++)
        {
            for (int i = 0; i < L; i++)  //wyzerowanie przestrzeni LxL
            {
                for (int j = 0; j < L; j++)
                {
                    space[i][j] = 0;
                }
            }
            for (int i = 0; i < N; i++) //loop for assining starting particles setting randomly
            {

                while (true)
                {
                    x[i] = rand() % L;
                    y[i] = rand() % L;
                    if (space[x[i]][y[i]] == 0)
                    {
                        space[x[i]][y[i]] = 1;
                        break;
                    }
                }
            }

            DR2 = 0;
            for (int j = 0; j < N; j++) //setting deltas to zero
            {
                dRxR[j] = 0;
                dx[j] = 0;
                dy[j] = 0;

            }
            for (int i = 0; i < K; i++) //loop for moving model by K steps
            {
                for (int j = 0; j < N; j++) //loop after all particles
                {
                    pom = rand() % 4;
                    if (pom == 0 && space[INext[x[j]]][y[j]] == 0) //condition for moving up
                    {
                        space[INext[x[j]]][y[j]] = 1;
                        space[x[j]][y[j]] = 0;
                        x[j] = INext[x[j]];
                        dx[j]++;
                    }
                    if (pom == 1 && space[IPrev[x[j]]][y[j]] == 0) //condition for moving down
                    {
                        space[IPrev[x[j]]][y[j]] = 1;
                        space[x[j]][y[j]] = 0;
                        x[j] = IPrev[x[j]];
                        dx[j]--;
                    }
                    if (pom == 2 && space[x[j]][INext[y[j]]] == 0) //condition for moving right
                    {
                        space[x[j]][INext[y[j]]] = 1;
                        space[x[j]][y[j]] = 0;
                        y[j] = INext[y[j]];
                        dy[j]++;
                    }
                    if (pom == 3 && space[x[j]][IPrev[y[j]]] == 0)//condition for moving left
                    {
                        space[x[j]][IPrev[y[j]]] = 1;
                        space[x[j]][y[j]] = 0;
                        y[j] = IPrev[y[j]];
                        dy[j]--;
                    }
                }
                plik << x[0] << " " << y[0] << endl; //writing out the position to a file (used in the simulation of the trajectory of a single particle)
            }
            for (int j = 0; j < N; j++) //counting and then averaging (deltaR)^2
            {
                dRxR[j] = dx[j] * dx[j] + dy[j] * dy[j];
                DR2 += dRxR[j];
            }
            DR2 /= double(N); //uśrednienie po liczbie atomów
            
            DR2_sr += DR2;
        }
        DR2_sr /= 30.0; //averaging after independent realizations
       
    D=DR2_sr/4/double(K); //calculation of the number sought D = average density
    if (true)
    {
        cout << endl << endl << K << " " << D << endl;
        plik1<<K<<" "<<D<<endl;
    }

}
    C=N/double(L)/double(L); //concentration C
    //cout<<endl<<endl<<C<<" "<<D<<endl;
    //plik2<<C<<" "<<D<<endl;
}


    //cout << '\n' << '\n' << '\n' << '\n' << '\n' << '\n';
   // pokaz(space, L);

    for (int i = 0; i < L; i++) 
    {
        delete[] space[i];
    }
    delete[] space;
    delete[] dx;
    delete[] dy;
    delete[] dRxR;
    return 0;
}
