#ifndef tablica_dynamiczna_hpp
#define tablica_dynamiczna_hpp
#include <iostream>

using namespace std;

template<typename T>
class Tablica_dynamiczna {
private:
    T *tab;
    int size;
    int actual;

public:

    Tablica_dynamiczna(int s) {
        actual = 0;
        size = s;
        tab = new T[size];
        for (int i = 0; i < size; i++) {
            tab[i] = nullptr;
        }
    };

    ~Tablica_dynamiczna() {
        delete[] tab;
    };

    T &get(int index) {
        return tab[index];
    }

    int get_size() {
        return size;
    }




    int resize() {
        
        int n_size = 2 * size;
        T *n_tab = new T[n_size];

      
        for (int i = 0; i < size; i++) {
            n_tab[i] = tab[i];
        }
        for (int i = size; i < n_size; i++) {
            n_tab[i] = nullptr;
        }

        delete[] tab;
        tab = n_tab;
        size = n_size;
        return size;
    }

    void add_end(T element) {
        tab[actual] = element;
        actual++;
    }

    void del(int index) {
        
        if (index >= 0 && index < size && tab[index] != nullptr) {
            delete tab[index];
            tab[index] = nullptr;
        }
    }

};
#endif