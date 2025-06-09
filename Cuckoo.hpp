#ifndef CUCKOO_HPP
#define CUCKOO_HPP
#include "tablica_dynamiczna.hpp"
#include <iostream>
#include <random>

struct Cuckoo_entry {
    int key;
    int value;
    Cuckoo_entry(int k, int v):key(k),value(v){}
};

class Cuckoo{
private:
    int size;
    Tablica_dynamiczna<Cuckoo_entry*> tablica1;
    Tablica_dynamiczna<Cuckoo_entry*> tablica2;
    int hashfunction(int key) {
        return (key)% size;
    };

    int hashfunction2(int key) {
        return (key/17)% size;
    };

    void rehash() {
        int oldsize = size;
        size = oldsize * 2;


        Tablica_dynamiczna<Cuckoo_entry*> tablica1_temp(oldsize * 2);
        Tablica_dynamiczna<Cuckoo_entry*> tablica2_temp(oldsize * 2);


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


        tablica1.resize();
        tablica2.resize();

        for (int i = 0; i < oldsize; i++) {
            if (tablica1_temp.get(i) != nullptr) {
               insert(tablica1_temp.get(i)->key, tablica1_temp.get(i)->value);
                tablica1_temp.get(i) = nullptr;
            }
            if (tablica2_temp.get(i) != nullptr) {
                insert(tablica2_temp.get(i)->key, tablica2_temp.get(i)->value);
                tablica2_temp.get(i) = nullptr;
            }
        }

    };

public:
    Cuckoo(int size) : size(size), tablica1(size), tablica2(size) {
    }
    ~Cuckoo()=default;
    

    void insert(int key, int value) {

        int index1 = hashfunction(key);
        int index2 = hashfunction2(key);
        int max_kick=size*2;
        for (int i = 0; i < max_kick; i++) {
            if (tablica1.get(index1)==nullptr) {
                tablica1.get(index1) = new Cuckoo_entry(key, value);
                return;
            }

            std::swap(key, tablica1.get(index1)->key);
            std::swap(value, tablica1.get(index1)->value);

            index2 = hashfunction2(key);
            if (tablica2.get(index2)==nullptr) {
                tablica2.get(index2) = new Cuckoo_entry(key, value);
                return;
            }

            std::swap(key, tablica2.get(index2)->key);
            std::swap(value, tablica2.get(index2)->value);

            index1 = hashfunction(key);
        }

        rehash();
        insert(key, value);


    };

    int search(int key) {
        int index = hashfunction(key);
        int index2 = hashfunction2(key);

        if (tablica1.get(index) != nullptr && tablica1.get(index)->key == key) {
            return tablica1.get(index)->value;
        }
        
        if (tablica2.get(index2) != nullptr && tablica2.get(index2)->key == key) {
            return tablica2.get(index2)->value;
        }
        return 0;
    };

    void remove(int key) {
        int index = hashfunction(key);
        int index2 = hashfunction2(key);
        

        if (tablica1.get(index) != nullptr && tablica1.get(index)->key == key) {
           tablica1.del(index);
        }
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