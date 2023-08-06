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
    int x, K=200,  x2, x1, n; //dek zmiennych calkowitych
    double pom , odch; //dek zmiennych rzeczywistych
    srand(time(NULL));
    fstream plik;
    plik.open("wyniki.txt", ios::out);
    if (plik.good() == true)
    {
        cin >> n; //podanie zakresu startowego
        for (int N = n; N < 10000; N++) //petla dla roznych wart. N
        {
            x2 = 0;
            x1 = 0;
            for (int j = 0; j < K; j++) //petla dla kazdego pijaka
            {
                x = 0;
                for (int i = 0; i < N; i++) //suma krokow pijaka
                {
                    pom = rand() % 101 / double(100);
                    if (pom < 0.5) x++;
                    if (pom >= 0.5) x--;
                    //cout << x << endl;
                }
                x2 += x * x; //suma kwadratow
                x1 += x; //suma
            }
            odch = sqrt(x2 / double(K) - x1 * x1 / double(K) / double(K)); //odchylenie standardowe
           // cout << N << " " << odch << endl;
            plik << N << " " << odch << endl;
        }
    }
    else
    {
        cout << "blad otwarcia pliku" << endl;
    }
   
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
