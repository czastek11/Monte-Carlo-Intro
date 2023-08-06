// Dystrybucja normalna i pijaków.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <time.h>
#include <math.h>
#include <fstream>

using namespace std;

int main()
{
    int x, K=200,  x2, x1, n; //declaring intigers
    double pom , odch; //decraling doubles
    srand(time(NULL));
    fstream plik;
    plik.open("wyniki.txt", ios::out);
    if (plik.good() == true)
    {
        cin >> n; //user declares initial range
        for (int N = n; N < 10000; N++) //loop for diffrent N values
        {
            x2 = 0;
            x1 = 0;
            for (int j = 0; j < K; j++) //loop for every drunkard
            {
                x = 0;
                for (int i = 0; i < N; i++) //sum of drunkard's steps
                {
                    pom = rand() % 101 / double(100);
                    if (pom < 0.5) x++;
                    if (pom >= 0.5) x--;
                    //cout << x << endl;
                }
                x2 += x * x; //sum of squares
                x1 += x; //sum
            }
            odch = sqrt(x2 / double(K) - x1 * x1 / double(K) / double(K)); //standard deviation
           // cout << N << " " << odch << endl;
            plik << N << " " << odch << endl;
        }
    }
    else
    {
        cout << "blad otwarcia pliku" << endl;
    }
   
}


