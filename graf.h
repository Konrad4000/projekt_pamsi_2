#pragma once

#include "lista.h"
#include "krawedz.h"
class Graf 
{
    protected:
    int liczbaWierzcholkow = 0;
    int liczbaKrawedzi = 0;
    int WierzcholekPoczatkowy = 0;

    public:
    int GetLiczbaWierzcholkow() { return liczbaWierzcholkow; }
    int GetLiczbaKrawedzi() { return liczbaKrawedzi; }
    int GetWierzcholekPoczatkowy() { return WierzcholekPoczatkowy; }
    virtual Lista<Krawedz>* Sasiedzi(int indexWierzcholka) 
    {
        Lista<Krawedz>* pomocnicza = new Lista<Krawedz>();
        return pomocnicza;
    }
    virtual int GetWageKrawedzi(int Wierzcholek1, int Wierzcholek2) { return 0; }
};