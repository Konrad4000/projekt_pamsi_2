#pragma once

template <typename T>
class Wezel 
{
    private:
    T element;
    Wezel<T>* nastepnyPtr;
    Wezel<T>* poprzedniPtr;

    public:
    Wezel() {}
    Wezel(T nowyElement) 
    {
        this->element = nowyElement;
        this->nastepnyPtr = nullptr;
        this->poprzedniPtr = nullptr;
    }

    T GetElement() { return this->element; }
    T* GetElementPtr() { return &(this->element); }
    void SetElement(T nowyElement) { this->element = nowyElement; }
    Wezel<T>* GetNastepny() { return this->nastepnyPtr; }
    void SetNastepny(Wezel<T>* nowyElement) { this->nastepnyPtr = nowyElement; }
    Wezel<T>* GetPoprzedni() { return this->poprzedniPtr; }
    void SetPoprzedni(Wezel<T>* nowyElement) { this->poprzedniPtr = nowyElement; }
};

template <typename T>
class Lista 
{
    private:
    Wezel<T>* glowa;
    Wezel<T>* ogon;
    unsigned int rozmiar = 0;

    public:
    Lista() 
    {
        this->glowa = nullptr;
        this->ogon = nullptr;
    }

    Lista(T nowyElement) 
    {
        Wezel<T>* pomocniczy = new Wezel<T>(nowyElement);
        this->glowa = pomocniczy;
        this->ogon = this->glowa;
        rozmiar = 1;
    }

    ~Lista() 
    {
        if (!this->IsEmpty()) {
            while (this->glowa != this->ogon) 
            {
                Wezel<T>* pomocniczy = this->glowa->GetNastepny();
                delete this->glowa;
                this->glowa = pomocniczy;
            }
            delete this->glowa;
        }
    }

    bool IsEmpty()
    {
        if (glowa == nullptr)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void Clear() 
    {
        if (!this->IsEmpty()) 
        {
            while (this->glowa->GetNastepny() != nullptr) 
            {
                Wezel<T>* pomocniczy = this->glowa->GetNastepny();
                delete this->glowa;
                this->glowa = pomocniczy;
            }
            delete this->glowa;
        }
        rozmiar = 0;
    }

    T operator[](unsigned int index) 
    {
        if (!this->IsEmpty()) 
        {
            if (index < this->Rozmiar()) 
            {
                Wezel<T>* pomocniczy = this->glowa;
                while (index != 0) 
                {
                    pomocniczy = pomocniczy->GetNastepny();
                    index--;
                }
                return pomocniczy->GetElement();
            }
            else {
                throw "Index poza zakresem";
            }
        }
        else {
            throw "Lista jest pusta";
        }
    }

    unsigned int Rozmiar()
    {
        return rozmiar;
    }

    Wezel<T>* GetWezel(unsigned int index) 
    {
        if (!this->IsEmpty()) 
        {
            if (index < this->Rozmiar()) 
            {
                Wezel<T>* pomocniczy = this->glowa;
                while (index != 0) 
                {
                    pomocniczy = pomocniczy->GetNastepny();
                    index--;
                }
                return pomocniczy;
            }
            else 
            {
                throw "Index poza zakresem";
                return nullptr;
            }
        }
        else 
        {
            throw "Lista jest pusta";
            return nullptr;
        }
    }

    void PushFront(T elem) 
    {
        if (!this->IsEmpty()) 
        {
            Wezel<T>* pomocniczy = new Wezel<T>(elem);
            pomocniczy->SetNastepny(this->glowa);
            this->glowa->SetPoprzedni(pomocniczy);
            this->glowa = pomocniczy;
        }
        else 
        {
            this->glowa = new Wezel<T>(elem);
            this->ogon = this->glowa;
        }
        rozmiar++;
    }

    T PopFront() 
    {
        if (!this->IsEmpty()) 
        {
            Wezel<T> pomocniczy = *this->glowa;
            if (this->Rozmiar() > 1) 
            {
                delete this->glowa;
                this->glowa = pomocniczy.GetNastepny();
                this->glowa->SetPoprzedni(nullptr);
            }
            else 
            {
                delete this->glowa;
                this->glowa = nullptr;
                this->ogon = nullptr;
            }
            rozmiar--;
            return pomocniczy.GetElement();
        }
        else 
        {
            throw "Lista jest pusta";
        }
    }

    void Insert(T elem, unsigned int index) 
    {
        if (!this->IsEmpty()) 
        {
            if (index == 0) 
            {
                this->PushFront(elem);
            }
            else if (index == this->Rozmiar() - 1) 
            {
                this->PushBack(elem);
            }
            else if (index < this->Rozmiar() - 1) 
            {
                Wezel<T>* poprzedni = this->glowa;
                while (index > 1) 
                {
                    poprzedni = poprzedni->GetNastepny();
                    index--;
                }
                Wezel<T>* nastepny = poprzedni->GetNastepny();
                Wezel<T>* pomocniczy = new Wezel<T>(elem);
                poprzedni->SetNastepny(pomocniczy);
                pomocniczy->SetPoprzedni(poprzedni);
                pomocniczy->SetNastepny(nastepny);
                nastepny->SetPoprzedni(pomocniczy);
            }
            rozmiar++;
        }
        else if (index == 0) 
        {
            this->PushFront(elem);
            rozmiar++;
        }
        else 
        {
            throw "Lista jest pusta i index > 0\n";
        }
    }

    T PullOut(unsigned int index) 
    {
        if (!this->IsEmpty()) 
        {
            if (index == 0) 
            {
                return this->PopFront();
            }
            else if (index == this->Rozmiar() - 1) 
            {
                return this->PopBack();
            }
            else if (index < this->Rozmiar() - 1) 
            {
                Wezel<T>* pomocniczy = this->glowa;
                while (index > 0) 
                {
                    pomocniczy = pomocniczy->GetNastepny();
                    index--;
                }
                Wezel<T>* nastepny = pomocniczy->GetNastepny();
                Wezel<T>* poprzedni = pomocniczy->GetPoprzedni();
                poprzedni->SetNastepny(nastepny);
                nastepny->SetPoprzedni(poprzedni);
                T tymczasowy = pomocniczy->GetElement();
                delete pomocniczy;
                rozmiar--;
                return tymczasowy;
            }
        }
        else 
        {
            throw "Lista jest pusta i index > 0\n";
        }
    }

    void PushBack(T elem) 
    {
        if (!this->IsEmpty()) 
        {
            Wezel<T>* pomocniczy = new Wezel<T>(elem);
            pomocniczy->SetPoprzedni(this->ogon);
            this->ogon->SetNastepny(pomocniczy);
            this->ogon = pomocniczy;
        }
        else 
        {
            this->glowa = new Wezel<T>(elem);
            this->ogon = this->glowa;
        }
        rozmiar++;
    }

    T PopBack() 
    {
        if (!this->IsEmpty()) 
        {
            Wezel<T> pomocniczy = *(this->ogon);
            if (this->Rozmiar() > 1) 
            {
                delete this->ogon;
                this->ogon = pomocniczy.GetPoprzedni();
                this->ogon->SetNastepny(nullptr);
            }
            else 
            {
                delete this->ogon;
                this->ogon = nullptr;
                this->glowa = nullptr;
            }
            rozmiar--;
            return pomocniczy.GetElement();
        }
        else 
        {
            throw "Lista jest pusta\n";
        }
    }

    void Modify(int index, T elem) 
    {
        if (!this->IsEmpty()) 
        {
            if (index < this->Rozmiar()) 
            {
                Wezel<T>* pomocnicza = this->glowa;
                while (index > 0) 
                {
                    pomocnicza = pomocnicza->GetNastepna();
                    index--;
                }
                pomocnicza->SetElement(elem);
            }
            else 
            {
                throw "Index poza zakresem\n";
            }
        }
        else 
        {
            throw "Lista jest pusta\n";
        }
    }
};