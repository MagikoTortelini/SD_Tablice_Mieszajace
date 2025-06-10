#ifndef TABLICA_DYNAMICZNA_Z_HPP
#define TABLICA_DYNAMICZNA_Z_HPP

#include <iostream>
using namespace std;

struct element_table {
    int key;
    int el;
};

class Tablica_dynamiczna {
private:
    element_table* tab;
    int size;
public:
    int actual;

    Tablica_dynamiczna(int s = 10) {  // domyslny rozmiar kubelka = 10
        actual = 0;
        size = s;
        tab = new element_table[size];
    }

    ~Tablica_dynamiczna() {
        delete[] tab;
    }

    int resize() {
        int new_size = size * 2;
        element_table* new_tab = new element_table[new_size];

        for (int i = 0; i < actual; i++) {
            new_tab[i] = tab[i];
        }

        delete[] tab;
        tab = new_tab;
        size = new_size;
        return size;
    }

    void add_end(element_table el) {
        if (actual == size) {
            resize();
        }
        tab[actual] = el;
        actual++;
    }

    bool remove_key(int key) {
        for (int i = 0; i < actual; i++) {
            if (tab[i].key == key) {
                for (int j = i; j < actual - 1; j++) {
                    tab[j] = tab[j + 1];
                }
                actual--;
                return true;
            }
        }
        return false;
    }

    int find_el(int key) {
        for (int i = 0; i < actual; i++) {
            if (tab[i].key == key) {
                return tab[i].el;
            }
        }
        return -1;  // nie znaleziono
    }

    void show() const {
        for (int i = 0; i < actual; i++) {
            cout << "(" << tab[i].key << ", " << tab[i].el << ") ";
        }
        cout << endl;
    }
};

#endif
