#ifndef ZAMKNIETE_HPP
#define ZAMKNIETE_HPP

#include <iostream>
#include "tablica_dynamiczna_z.hpp"

using namespace std;

class Hash_close {
public:
    Hash_close(int size_) : size(size_) {
        chain = new Tablica_dynamiczna*[size];
        for (int i = 0; i < size; i++) {
            chain[i] = new Tablica_dynamiczna(10);
        }
    }
    ~Hash_close() { 
        for (int i = 0; i < size; i++) {
            delete chain[i];
        }
        delete[] chain;
     }

    void insert(int key_, int el_) {
        
        element_table new_element;
        new_element.key = key_;
        new_element.el = el_;
        int index = key_ % size;
        chain[index]->add_end(new_element);
        
    }
    int get_size()
    {
        return size;
    }
    void remove(int key) {
       int index = key % size;
        if (chain[index]->remove_key(key)) { 
            cout<<"";
        } else {
            cout << "nie znaleziono elementu z kluczem " << key << " w kubelku " << index << endl;
        }
    }
    void show() {
        for (int i = 0; i < size; i++) {
            cout << "bucket " << i << ": ";
            chain[i]->show();
        }
    }
private:
    Tablica_dynamiczna** chain;
    int size;
};
#endif