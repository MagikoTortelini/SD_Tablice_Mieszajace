#ifndef CUCKOO_HPP
#define CUCKOO_HPP
#include "Tablica_dynamiczna_cuckoo.hpp"
#include <iostream>
#include <cmath>



//Struktura wpisu do tablicy
struct Cuckoo_entry {
    int key;
    int value;
    Cuckoo_entry(int k, int v):key(k),value(v){}
};

class Cuckoo{
private:
    int size;
    //Tablica glowna
    Tablica_dynamiczna_cuckoo<Cuckoo_entry*> tablica1;
    //Tablica alternatywna
    Tablica_dynamiczna_cuckoo<Cuckoo_entry*> tablica2;


    //Pierwsza funkcja hashujaca
    int hashfunction(int key) {
        return key%size;
    }
    
    //Druga funkcja hashujaca
    int hashfunction2(int key) {
        const double A = 0.61803398875; // złoty podział
        double modulo = fmod(key * A, 1.0);
        int indeks=static_cast<int>(size*modulo);
        return indeks;
    }

    //Funkcja zwiekszajaca rozmiara tablic i hashujaca ponownie zawartosc
    void rehash() {
        int oldsize = size;
        size = oldsize * 2;

        //Tymczasowe tablice
        Tablica_dynamiczna_cuckoo<Cuckoo_entry*> tablica1_temp(oldsize * 2);
        Tablica_dynamiczna_cuckoo<Cuckoo_entry*> tablica2_temp(oldsize * 2);

        //Przeniesienie zawartosci do tymczasowych tablic
        for (int i = 0; i < oldsize; i++) {
            if (tablica1.get(i) != nullptr) {
                tablica1_temp.add_end(tablica1.get(i));
                tablica1.get(i) = nullptr;
            }
            if (tablica2.get(i) != nullptr) {
                tablica2_temp.add_end(tablica2.get(i));
                tablica2.get(i) = nullptr;
            }
        }

        //Zmiana rozmiaru tablic
        tablica1.resize();
        tablica2.resize();

        //Ponowne zahashowanie zawartosci
        for (int i = 0; i < oldsize; i++) {
            if (tablica1_temp.get(i) != nullptr) {
               insert(tablica1_temp.get(i)->key, tablica1_temp.get(i)->value);
                tablica1_temp.del(i);
            }
            if (tablica2_temp.get(i) != nullptr) {
                insert(tablica2_temp.get(i)->key, tablica2_temp.get(i)->value);
                tablica2_temp.del(i);
            }
        }

    };

public:
    //Konstruktor
    Cuckoo(int size) : size(size), tablica1(size), tablica2(size) {
    }

    //Destruktor
    ~Cuckoo()
    {
        for (int i = 0; i < size; i++) {
            if (tablica1.get(i) != nullptr) {
                delete tablica1.get(i);
            }
            if (tablica2.get(i) != nullptr) {
                delete tablica2.get(i);
            }
        }
    }
    
    //Funkcja wsadzajaca elementy
    void insert(int key, int value) {

        //indeksy
        int index1 = hashfunction(key);
        int index2 = hashfunction2(key);

        //Maksymala liczba prob wsadzenia wpisu przed rehashem
        int max_kick=size*2;
    
        for (int i = 0; i < max_kick; i++) {

            //Sprawdzenie czy indeks w glownej tablicy jest wolny
            if (tablica1.get(index1)==nullptr) {
                tablica1.get(index1) = new Cuckoo_entry(key, value);
                return;
            }

            //Jezeli nie to wsadzamy element i szukamy nowej pozycji dla elementu ktory byl w wsadzony 
            std::swap(key, tablica1.get(index1)->key);
            std::swap(value, tablica1.get(index1)->value);

            //Sprawdzenie czy indeks jest wolny w alternatywnej tablicy
            index2 = hashfunction2(key);
            if (tablica2.get(index2)==nullptr) {
                tablica2.get(index2) = new Cuckoo_entry(key, value);
                return;
            }
            
            ///Jezeli nie to wsadzamy element i szukamy nowej pozycji dla elementu ktory byl w wsadzony 
            std::swap(key, tablica2.get(index2)->key);
            std::swap(value, tablica2.get(index2)->value);

            index1 = hashfunction(key);
        }

        // jezeli nie uda nam sie wsadzic elementow to rehashujemy tablice i ponawiamy
        rehash();
        insert(key, value);


    };

    int search(int key) {
        //indeksy
        int index = hashfunction(key);
        int index2 = hashfunction2(key);


        //Jezeli znajdziemy w glownej to zwracamy wartosc
        if (tablica1.get(index) != nullptr && tablica1.get(index)->key == key) {
            return tablica1.get(index)->value;
        }
        
        //Jezeli znajdziemy w alternatywnej to zwracamy wartosc
        if (tablica2.get(index2) != nullptr && tablica2.get(index2)->key == key) {
            return tablica2.get(index2)->value;
        }

        //Inaczej zwracamy nic
        return 0;
    };

    void remove(int key) {

        //indeksy
        int index = hashfunction(key);
        int index2 = hashfunction2(key);
        
        //Jezli jest w glownej tablicy usuwamy go i nie szukamy dalej
        if (tablica1.get(index) != nullptr && tablica1.get(index)->key == key) {
           tablica1.del(index);
           return;
        }

        //Jezli jest w alternatywnej tablicy usuwamy go
        if (tablica2.get(index2) != nullptr && tablica2.get(index2)->key == key) {
            tablica2.del(index2);
        }
        
    }

    void display() {
        std::cout << "Table 1:"<< std::endl;
        for (int i = 0; i < size; i++) {
            if (tablica1.get(i) != nullptr) {
                std::cout << "Index " << i << ": (" << tablica1.get(i)->key << "," << tablica1.get(i)->value <<")"<< std::endl;;
            }
        }
        std::cout << std::endl;
        std::cout << "Table 2:"<< std::endl;;
        for (int i = 0; i < size; i++) {
            if (tablica2.get(i) != nullptr) {
                std::cout << "Index " << i << ": (" << tablica2.get(i)->key << "," << tablica2.get(i)->value << ")"<<std::endl;;
            }
        }
    }
};

#endif