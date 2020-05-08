#pragma once

class Krawedz {
private:
    int poczatek = -1;
    int koniec = -1;
    int waga = -1;

public:
    Krawedz() { waga = 0; }
    Krawedz(int nowyPoczatek, int nowyKoniec, int nowaWaga) 
    {
        this->poczatek = nowyPoczatek;
        this->koniec = nowyKoniec;
        this->waga = nowaWaga;
    }
    int GetPoczatek() { return this->poczatek; }
    int GetKoniec() { return this->koniec; }
    int GetWaga() { return this->waga; }
};