#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <fstream>
using namespace std;

int main()
{
    srand(time(NULL));
    int s[500]; //spin table
    int r, MCS = 1e5, MCS_count=0; 
    double R, S = 0, _S_ = 0; 
    fstream save_file;
    save_file.open("wyniki.txt", ios::out);
    if (save_file.good())
    {
        for (double Tr = 0; Tr < 15; Tr +=0.1) //reduced T coeficient, loop reduces
        {
            MCS_count = 0;
            for (int i = 0; i < 500; i++) //random spin setup
            {
                r = rand() % 2;
                if (r == 1)
                {
                    s[i] = 1;
                }
                else
                {
                    s[i] = -1;
                }
            }
            _S_ = 0;
            for (int i = 0; i < MCS; i++) //monte carlo steps - number of system steps
            {
                S = 0; //sum reset
                for (int j = 0; j < 500; j++)
                {
                    if (s[j] == -1) //first condtion
                    {
                        s[j] = 1;
                    }
                    else //second condtion
                    {
                        R = rand() % 1001 / 1000.0; //draw from 0 to 1 with 3 decimal places
                        if (R <= exp(-2 / Tr)) //state change if the drawn number corresponds to the probability
                        {
                            s[j] = -1;
                        }
                    }
                    S += s[j]; //states sum
                }
                if (i > 1e4 && i % 100 == 0)
                {
                    //cout << S / 1e3 << endl<<endl;
                    _S_ += S / 500.0; // _S_ to srenia w danym kroku
                    MCS_count++;
                }

            }
            cout << Tr << " " << _S_ / double(MCS_count) << endl;  //writing the average after the system has stabilized
            save_file << Tr << " " << _S_ / double(MCS_count) << endl;  //writing the average after stabilization of the system to a file 

        }
    }
    else cout << "blad otwarcia pliku" << endl;
}
