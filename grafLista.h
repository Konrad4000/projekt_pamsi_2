#pragma once

#include <fstream>

#include "krawedz.h"
#include "graf.h"
#include "lista.h"

class ListaGraf : public Graf 
{
    private:
    Lista<Krawedz>** listaSasiedztwa;

    public:
    ~ListaGraf() 
    {
        for (int i = 0; i < liczbaWierzcholkow; i++) 
        {
            delete listaSasiedztwa[i];
        }
        delete[] listaSasiedztwa;
    }

    void WczytajZPliku(std::string nazwaPliku) 
    {
        std::fstream plik;
        plik.open(nazwaPliku);
        if (!plik) 
        {
            std::cerr << "Plik nie otwarty";
            return;
        }
        plik >> liczbaKrawedzi;
        plik >> liczbaWierzcholkow;
        plik >> WierzcholekPoczatkowy;
        listaSasiedztwa = new Lista<Krawedz> * [liczbaWierzcholkow];
        for (int i = 0; i < liczbaWierzcholkow; i++) 
        {
            listaSasiedztwa[i] = new Lista<Krawedz>();
        }
        int pierwszyIndex;
        int koncowyIndex;
        int waga;
        while (plik >> pierwszyIndex) 
        {
            plik >> koncowyIndex;
            plik >> waga;
            Krawedz k1 = Krawedz(pierwszyIndex, koncowyIndex, waga);
            Krawedz k2 = Krawedz(koncowyIndex, pierwszyIndex, waga);
            listaSasiedztwa[pierwszyIndex]->PushBack(k1);
            listaSasiedztwa[koncowyIndex]->PushBack(k2);
        }
        plik.close();
    }

    Lista<Krawedz>* Sasiedzi(int indexWierzcholka) 
    {
        Lista<Krawedz>* pomocnicza = new Lista<Krawedz>();
        for (unsigned int i = 0; i < listaSasiedztwa[indexWierzcholka]->Rozmiar(); i++) 
        {
            pomocnicza->PushBack((*listaSasiedztwa[indexWierzcholka])[i]);
        }
        return pomocnicza;
    }
    int GetWageKrawedzi(int Wierzcholek1, int Wierzcholek2) 
    {
        for (unsigned int i = 0; i < listaSasiedztwa[Wierzcholek1]->Rozmiar(); i++) 
        {
            if ((*listaSasiedztwa[Wierzcholek1])[i].GetKoniec() == Wierzcholek2) 
            {
                return (*listaSasiedztwa[Wierzcholek1])[i].GetWaga();
            }
        }
        return 0;
    }
};