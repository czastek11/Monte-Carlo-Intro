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

void pokaz(int** space, int L) //funkcja testowa do pokazywania pozycji
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
    int L = 20, n = 200; //deklaracja wielkosci przestrzeni LxL oraz ilosci atomow N
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
    for (int i = 0; i < L; i++)  //utworzenie i wyzerowanie przestrzeni LxL
    {
        space[i] = new int[L];
        for (int j = 0; j < L; j++)
        {
            space[i][j] = 0;
        }
    }
    int* INext = new int[L]; //utworzenie tablicy sasiadow dla przesuniecia prawo/gora
    for (int i = 0; i < L; i++)
    {
        INext[i] = i + 1;
    }
    INext[L - 1] = 0;
    int* IPrev = new int[L];    //utworzenie tablicy sasiadow dla przesuniecia lewo/dol
    for (int i = 0; i < L; i++)
    {
        IPrev[i] = i - 1;
    }
    IPrev[0] = L-1;
for(int N=n;N<n+1;N++) //petla krokow monte-carlo (zmiana liczby atomow->zmiana stezenia C=n(L^-2)
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
    x = new int[N];    //tablica pozycji
    y = new int[N];    //tablica pozycji

    //pokaz(space, L);


    for(int K=1;K<61;K++) //petla krokow monte-carlo (zmiana liczby krokow)
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
            for (int i = 0; i < N; i++) //petla odpowiadajaca za wylosowanie miejsc atomow w przestrzeni
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
            for (int j = 0; j < N; j++) //wyzerowanie delt
            {
                dRxR[j] = 0;
                dx[j] = 0;
                dy[j] = 0;

            }
            for (int i = 0; i < K; i++) //petla odpowiadajca za przemieszczenie modelu o K krokow
            {
                for (int j = 0; j < N; j++) //petla po wszystkich atomach
                {
                    pom = rand() % 4;
                    if (pom == 0 && space[INext[x[j]]][y[j]] == 0) //warunek przemieszczenia sie w gore
                    {
                        space[INext[x[j]]][y[j]] = 1;
                        space[x[j]][y[j]] = 0;
                        x[j] = INext[x[j]];
                        dx[j]++;
                    }
                    if (pom == 1 && space[IPrev[x[j]]][y[j]] == 0) //warunek przemieszczenia sie w dol
                    {
                        space[IPrev[x[j]]][y[j]] = 1;
                        space[x[j]][y[j]] = 0;
                        x[j] = IPrev[x[j]];
                        dx[j]--;
                    }
                    if (pom == 2 && space[x[j]][INext[y[j]]] == 0) //warunek przemieszczenia sie w prawo
                    {
                        space[x[j]][INext[y[j]]] = 1;
                        space[x[j]][y[j]] = 0;
                        y[j] = INext[y[j]];
                        dy[j]++;
                    }
                    if (pom == 3 && space[x[j]][IPrev[y[j]]] == 0)//warunek przemieszczenia sie w lewo
                    {
                        space[x[j]][IPrev[y[j]]] = 1;
                        space[x[j]][y[j]] = 0;
                        y[j] = IPrev[y[j]];
                        dy[j]--;
                    }
                }
                plik << x[0] << " " << y[0] << endl; //wypisanie pozycji do pliku (uzyte w symulacji trajektorii pojedynczej czastki)
            }
            for (int j = 0; j < N; j++) //zliczenie a nastepnie usrednienie (deltyR)^2
            {
                dRxR[j] = dx[j] * dx[j] + dy[j] * dy[j];
                DR2 += dRxR[j];
            }
            DR2 /= double(N); //uśrednienie po liczbie atmowó
            
            DR2_sr += DR2;
        }
        DR2_sr /= 30.0; //usrednienie po niezależnych realizacjach
       
    D=DR2_sr/4/double(K); //wyliczenie szukanej liczby  D = sredniej gestosci
    if (true)
    {
        cout << endl << endl << K << " " << D << endl;
        plik1<<K<<" "<<D<<endl;
    }

}
    C=N/double(L)/double(L); //gęstość C
    //cout<<endl<<endl<<C<<" "<<D<<endl;
    //plik2<<C<<" "<<D<<endl;
}


    //cout << '\n' << '\n' << '\n' << '\n' << '\n' << '\n';
   // pokaz(space, L);

    for (int i = 0; i < L; i++) //zwolnienie pamieci uzytej przez zadeklarowane tablice
    {
        delete[] space[i];
    }
    delete[] space;
    delete[] dx;
    delete[] dy;
    delete[] dRxR;
    return 0;
}
