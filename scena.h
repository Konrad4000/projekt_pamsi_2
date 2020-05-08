#pragma once

#include <time.h>

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "graf.h"
#include "lista.h"

void utworzGraf(int rozmiar, float gestosc, std::string nazwapliku)
{
    srand(time(NULL));
    int liczbaKrawedzi;
    int** pomocnicza;
    if (gestosc == 1)
    {
        liczbaKrawedzi = rozmiar * ((rozmiar - 1) / 2);
        pomocnicza = new int* [rozmiar];
        for (int i = 0; i < rozmiar; i++)
        {
            pomocnicza[i] = new int[rozmiar];
            for (int j = 0; j < rozmiar; j++)
            {
                if (j == i)
                {
                    pomocnicza[i][j] = 0;
                }
                else
                {
                    pomocnicza[i][j] = 1;
                }
            }
        }
    }
    else
    {
        liczbaKrawedzi = rozmiar * ((rozmiar - 1) / 2) * gestosc;
        pomocnicza = new int* [rozmiar];
        for (int i = 0; i < rozmiar; i++)
        {
            pomocnicza[i] = new int[rozmiar];
            for (int j = 0; j < rozmiar; j++)
            {
                pomocnicza[i][j] = 0;
            }
        }
        for (int i = 0; i < rozmiar; i++)
        {
            pomocnicza[i][0] = 1;
            pomocnicza[0][i] = 1;
        }
        for (int i = rozmiar; i < liczbaKrawedzi; i++)
        {
            int x1 = rand() % rozmiar;
            int x2 = rand() % rozmiar;
            while (x1 == x2)
            {
                x2 = rand() % rozmiar;
            }
            while (pomocnicza[x1][x2] == 1)
            {
                x1 = rand() % rozmiar;
                x2 = rand() % rozmiar;
                while (x1 == x2)
                {
                    x2 = rand() % rozmiar;
                }
            }
            pomocnicza[x1][x2] = 1;
            pomocnicza[x2][x1] = 1;
        }
    }
    std::ofstream plik;
    plik.open(nazwapliku);
    if (!plik)
    {
        std::cerr << "Problem";
        return;
    }
    plik << liczbaKrawedzi << " " << rozmiar << " " << rand() % rozmiar << std::endl;
    for (int i = 0; i < rozmiar; i++)
    {
        for (int j = i; j < rozmiar; j++)
        {
            if (pomocnicza[i][j] == 1)
            {
                plik << i << " " << j << " " << rand() % 50 << std::endl;
            }
        }
    }
    plik.close();
    for (int i = 0; i < rozmiar; i++)
    {
        delete[] pomocnicza[i];
    }
    delete[] pomocnicza;
}

double Djikstra(Graf* graf) 
{
    int liczbaWierzcholkow = graf->GetLiczbaWierzcholkow();
    int liczbakrawedzi = graf->GetLiczbaKrawedzi();
    int WierzcholekPoczatkowy = graf->GetWierzcholekPoczatkowy();
    unsigned int* dystans = new unsigned int[liczbaWierzcholkow];
    int* poprzedniWierzcholek = new int[liczbaWierzcholkow];
    Lista<int> zakolejkowany, rozwiazany;
    bool* jestZakolejkowany = new bool[liczbaWierzcholkow];
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < liczbaWierzcholkow; i++) 
    {
        zakolejkowany.PushBack(i);
        dystans[i] = -1;
        poprzedniWierzcholek[i] = -1;
        jestZakolejkowany[i] = true;
    }
    dystans[WierzcholekPoczatkowy] = 0;

    while (!zakolejkowany.IsEmpty()) 
    {
        unsigned int koszt =-1;
        int biezacyWierzcholek = 0;
        int indexNaLiscie = 0;
        for (unsigned int i = 0; i < zakolejkowany.Rozmiar(); i++) 
        {
            if (dystans[zakolejkowany[i]] < koszt) 
            {
                koszt = dystans[zakolejkowany[i]];
                biezacyWierzcholek = zakolejkowany[i];
                indexNaLiscie = i;
            }
        }
        rozwiazany.PushBack(zakolejkowany.PullOut(indexNaLiscie));
        jestZakolejkowany[rozwiazany[rozwiazany.Rozmiar() - 1]] = false;
        Lista<Krawedz>* sasiedzi = graf->Sasiedzi(biezacyWierzcholek);

        while (!sasiedzi->IsEmpty()) 
        {
            Krawedz sasiedniaKrawedz = sasiedzi->PopFront();
            int sasiedniWierzcholek = sasiedniaKrawedz.GetKoniec();
            unsigned int i = 0;
            if (!jestZakolejkowany[sasiedniWierzcholek]) 
            {
                continue;
            }
            else {
                unsigned int alterantive =
                    dystans[biezacyWierzcholek] + sasiedniaKrawedz.GetWaga();
                if (dystans[sasiedniWierzcholek] > alterantive) 
                {
                    dystans[sasiedniWierzcholek] = alterantive;
                    poprzedniWierzcholek[sasiedniWierzcholek] = biezacyWierzcholek;
                }
            }
        }
        delete sasiedzi;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    delete[] dystans;
    delete[] poprzedniWierzcholek;
    return (std::chrono::duration_cast<std::chrono::microseconds>(stop - start)
        .count());
}

void Test() 
{
    float gestosc[] = { 0.25, 0.5, 0.75, 1 };
    int rozmiar[] = { 10, 25, 50, 75, 100 };
    std::ofstream plik;
    plik.open("Wyniki.txt");
    for (int k = 0; k < 4; k++)
    {
        for (int j = 0; j < 5; j++)
        {
            double czasListy = 0;
            double czasMacierzy = 0;
            for (int i = 0; i < 100; i++)
            {
                utworzGraf(rozmiar[j], gestosc[k], "test.txt");
                MacierzGraf macierzG;
                ListaGraf listaG;
                macierzG.WczytajZPliku("test.txt");
                czasMacierzy += Djikstra(&macierzG);
                listaG.WczytajZPliku("test.txt");
                czasListy += Djikstra(&listaG);
            }
            double sumaM = 0;
            double sumaL = 0;
            sumaM = czasMacierzy;
            sumaL = czasListy;
            czasMacierzy = sumaM / 100;
            czasListy = sumaL / 100;

            plik << "Macierz;" << gestosc[k] << ";" << rozmiar[j] << ";" << czasMacierzy;
            plik << ";;Lista;" << gestosc[k] << ";" << rozmiar[j] << ";" << czasListy;
            plik << std::endl;
            std::cout << "rozmiar:" << rozmiar[j] << " gestosc:" << gestosc[k] * 100
                << "% czas: " << czasMacierzy << " czas : " << czasListy;
            ;
            std::cout << std::endl;
        }
    }
    plik.close();
}