
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
using namespace std;

int main()
{
    int L;
    cin >> L;
    int * next=new int[L];      //
    int * prev=new int[L];      // neighbour table
    for (int i = 0; i < L; i++) //
    {
        if (i == L - 1) next[i] = 0;
        else next[i] = i + 1;
        if (i == 0) prev[i] = L - 1;
        else prev[i] = i - 1;
    }
    

    int*** s = new int** [L]; //building of 3D table of spins
    for (int i = 0; i < L; i++)
    {
        s[i] = new int* [L];
        for (int j = 0; j < L; j++)
        {
            s[i][j] = new int[L];
        }
    }
    for (int i = 0; i < L; i++)
    {
        for (int j = 0; j < L; j++)
        {
            for (int k = 0; k < L; k++)
            {
                s[i][j][k] = -1;  //setting default value for all spins
            }
        }
    }

    srand(time(NULL));
    double DU = 0;          //
    double R=0;             //    
    double mi_sr=0;         //
    double mi = 0;          // real variables
    int MCS_count = 0;      //
    double U,U_sr,U2_sr,c;  //
    fstream plik_1;
    plik_1.open("test_1.txt", ios::out); 
    fstream plik_2;
    plik_2.open("test_2.txt", ios::out);
    for (double Tzr = 2; Tzr < 5.6; Tzr += 0.025) //loop for chaning reduced temperature
    {
        MCS_count = 0;
        mi_sr = 0;
        U_sr = 0;
        U2_sr = 0;
        for (int MCS = 0; MCS < 130000; MCS++)  //monte carlo steps loop
        {
           
            for (int i = 0; i < L; i++)         //
            {
                for (int j = 0; j < L; j++)     // loop after all spins
                {
                    for (int k = 0; k < L; k++) //
                    {
                        DU = 2.0 * s[i][j][k] * (s[next[i]][j][k] + s[prev[i]][j][k] + s[i][next[j]][k] + s[i][prev[j]][k] + s[i][j][next[k]] + s[i][j][prev[k]]); //calculations of energy delta
                        
                        if (DU < 0) s[i][j][k] = -1*s[i][j][k];                 //
                        else                                                    //
                        {                                                       //  metropolis algorithm
                            R =(rand() % 1000+1.0 )/ 1000.0;                    //
                            if(R<= exp(-DU / Tzr)) s[i][j][k] = -1*s[i][j][k];  //
                        }
                        
                    }
                }
            }
            if (MCS > 30000 && MCS % 100 == 0)
            {
                mi = 0;
                U = 0;
                for (int i = 0; i < L; i++)         //
                {
                    for (int j = 0; j < L; j++)     // loop after all spins
                    {
                        for (int k = 0; k < L; k++) //
                        {
                            mi += s[i][j][k]; //summing all states after spins
                            U += s[i][j][k] * (s[next[i]][j][k] + s[i][next[j]][k] + s[i][j][next[k]]); //sum of energies to a total energy
                        }
                    }
                }
                mi /= double(L * L * L); //averging above spins
                mi_sr += abs(mi);  //
                MCS_count++; //number of analised steps
                U_sr += U; //average
                U2_sr += U * U; //average of squares

            } 
        }
        mi_sr = mi_sr / double(MCS_count); //average magnetisation
        U_sr = U_sr / double(MCS_count); //average
        U2_sr = U2_sr / double(MCS_count); //average of squares
        c = (U2_sr - U_sr * U_sr) / double(L * L * L) / Tzr / Tzr; //formula for c with standard deviation
        std::cout << Tzr << " " << mi_sr <<" "<<c<< endl << endl;
        plik_1 << Tzr << " " << mi_sr << endl << endl;
        plik_2 << Tzr << " " << c << endl << endl;
       // std::cout << "( " << U2_sr << " " << U_sr << " )" << endl << endl << endl;
    }
}
