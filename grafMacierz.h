#pragma once

#include <fstream>
#include <string>

#include "krawedz.h"
#include "graf.h"
#include "lista.h"

class MacierzGraf : public Graf 
{
    private:
    Krawedz*** macierzSasiedztwa;

    public:
    ~MacierzGraf() 
    {
        for (int i = 0; i < liczbaWierzcholkow; i++) 
        {
            for (int j = i; j < liczbaWierzcholkow; j++) 
            {
                if (macierzSasiedztwa[i][j] != nullptr) 
                {
                    delete macierzSasiedztwa[i][j];
                }
            }
            delete[] macierzSasiedztwa[i];
        }
        delete[] macierzSasiedztwa;
    }

    Lista<Krawedz>* Sasiedzi(int indexWierzcholka) 
    {
        Lista<Krawedz>* pomocnicza = new Lista<Krawedz>();
        for (int i = 0; i < liczbaWierzcholkow; i++) 
        {
            if (macierzSasiedztwa[indexWierzcholka][i] != nullptr) 
            {
                pomocnicza->PushBack(*macierzSasiedztwa[indexWierzcholka][i]);
            }
        }
        return pomocnicza;
    }
    
    int GetWageKrawedzi(int wierzcholek1, int wierzcholek2) 
    {
        return macierzSasiedztwa[wierzcholek1][wierzcholek2]->GetWaga();
    }
    
    void WczytajZPliku(std::string nazwaPliku) 
    {
        std::fstream plik;
        plik.open(nazwaPliku);
        if (!plik) 
        {
            std::cerr << "Plik nie otwarty\n";
            return;
        }
        plik >> liczbaKrawedzi;
        plik >> liczbaWierzcholkow;
        plik >> WierzcholekPoczatkowy;
        macierzSasiedztwa = new Krawedz * *[liczbaWierzcholkow];
        for (int i = 0; i < liczbaWierzcholkow; i++) 
        {
            macierzSasiedztwa[i] = new Krawedz * [liczbaWierzcholkow];
            for (int j = 0; j < liczbaWierzcholkow; j++) 
            {
                macierzSasiedztwa[i][j] = nullptr;
            }
        }
        int pierwszyIndex;
        int koncowyIndex;
        int waga;
        while (plik >> pierwszyIndex) 
        {
            plik >> koncowyIndex;
            plik >> waga;
            Krawedz* krawedz = new Krawedz(pierwszyIndex, koncowyIndex, waga);
            macierzSasiedztwa[pierwszyIndex][koncowyIndex] = krawedz;
            macierzSasiedztwa[koncowyIndex][pierwszyIndex] = krawedz;
        }
        plik.close();
    }

    private:
    void aktualizujMacierz(int rozmiar) 
    {
        Krawedz*** pomocnicza = new Krawedz * *[liczbaWierzcholkow + rozmiar];
        for (int i = 0; i < liczbaWierzcholkow + rozmiar; i++) 
        {
            pomocnicza[i] = new Krawedz * [liczbaWierzcholkow + rozmiar];
            for (int j = 0; j < liczbaWierzcholkow + rozmiar; j++) 
            {
                pomocnicza[i][j] = nullptr;
            }
        }

        for (int i = 0; i < liczbaWierzcholkow; i++) 
        {
            for (int j = 0; j < liczbaWierzcholkow; j++) 
            {
                pomocnicza[i][j] = macierzSasiedztwa[i][j];
            }
            delete[] macierzSasiedztwa[i];
        }
        delete[] macierzSasiedztwa;
        macierzSasiedztwa = pomocnicza;
    }
};