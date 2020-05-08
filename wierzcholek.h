#pragma once

#include "lista.h"
template <typename T>
class Wierzcholek 
{
    private:
    Wezel<Wierzcholek<T>>* listaPtr = nullptr;
    T elem;

    public:
    Wierzcholek() { elem = 0; };
    Wierzcholek(T nowyElem) { this->elem = nowyElem; }
    void SetElem(T innyElem) { this->elem = innyElem; }
    T GetElem() { return elem; }
    void SetPtr(Wezel<Wierzcholek<T>>* ptr) { this->listaPtr = ptr; }
    Wezel<Wierzcholek<T>>* GetPtr() { return this->listaPtr; }
};