#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
using namespace std;

struct element {
    element* left;
    element* right;
    int key;
    int el;
    int factor; // współczynnik równowagi
    element(int key_ = 0, int el_ = 0) : key(key_), el(el_), left(nullptr), right(nullptr), factor(1) {}
};

class Avl {
public:
    element* root;
    Avl() : root(nullptr) {}
    ~Avl() { del(root); }

    void insert(int key, int value) {
        root = insert(root, key, value);
    }
    void remove(int key) {
        root = remove(root, key);
    }
    void display() {
        inorder(root);
        cout << endl;
    }
private:
    void del(element* node) {
        if (!node) return;
        del(node->left);
        del(node->right);
        delete node;
    }
    int height(element* node) {
        if (node != nullptr) { return node->factor; }
        else { return 0; }
    }
    int balance(element* node) {
        if (node != nullptr) { return height(node->left) - height(node->right); }
        else { return 0; }
    }
    void update_factor(element* node) {
        if(node) { node -> factor = 1 + max(height(node -> left), height(node -> right)); }
    }
    void inorder(element* node) {
        if (!node) return;
        inorder(node->left);
        cout << "(" << node->key << ", " << node->el << ") ";
        inorder(node->right);
    }
    element* min_value(element* node) {
        element* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }
    element* rotate_r(element* el){
        element* x = el->left;
        element* y = x->right;
        x->right = el;
        el->left = y;

        update_factor(el);
        update_factor(x);
        return x;
    }
    element* rotate_l(element* el){
        element* x = el->right;
        element* y = x->left;
        x->left = el;
        el->right = y;

        update_factor(el);
        update_factor(x);
        return x;
    }
    element* insert(element* node, int key, int value) {
        if (node == nullptr) { return new element(key); }

        if(key < node -> key) {
            node -> left = insert(node -> left, key, value);
        } else if(key > node -> key) {
            node -> right = insert(node -> right, key, value);
        } else { return node; }

        update_factor(node);
        int b_factor = balance(node);

        if (b_factor > 1 && key < node->left->key) { return rotate_r(node); }
        if (b_factor < -1 && key > node->right->key) { return rotate_l(node); }

        if (b_factor > 1 && key > node->left->key) {
            node->left = rotate_l(node->left);
            return rotate_r(node);
        }
        if (b_factor < -1 && key < node->right->key) {
            node->right = rotate_r(node->right);
            return rotate_l(node);
        }
        return node;
    }
    element* remove(element* node, int key) {
        if (!node) return nullptr;

        if (key < node->key) {
            node->left = remove(node->left, key);
        } else if (key > node->key) {
            node->right = remove(node->right, key);
        } else {
            // znaleziono element do usuniecia
            if (!node->left || !node->right) {
                element* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                element* temp = min_value(node->right);
                node->key = temp->key;
                node->el = temp->el;
                node->right = remove(node->right, temp->key);
            }
        }
        update_factor(node);
        int b_factor = balance(node);

        // rotacje
        if (b_factor > 1 && balance(node->left) >= 0) { return rotate_r(node); }
        if (b_factor > 1 && balance(node->left) < 0) {
            node->left = rotate_l(node->left);
            return rotate_r(node);
        }
        if (b_factor < -1 && balance(node->right) <= 0) { return rotate_l(node); }
        if (b_factor < -1 && balance(node->right) > 0) {
            node->right = rotate_r(node->right);
            return rotate_l(node);
        }
        return node;
    }
};

class Hash {
private:
    int size;
    Avl** tab;
public:
    Hash(int s) {
        size = s;
        tab = new Avl*[size];
        for (int i = 0; i < size; i++) {
            tab[i] = new Avl();
        }
    }
    ~Hash() {
        for (int i = 0; i < size; i++) {
            delete tab[i];
        }
        delete[] tab;
    }
    int hash(int key) {
        return key % size;
    }
    void insert(int key, int e) {
        int index = hash(key);
        tab[index]->Avl::insert(key, e);        
    }
    void remove(int key) {
        int index = hash(key);
        tab[index]->Avl::remove(key);   
    }
    void display() {
        for (int i = 0; i < size; i++) {
            cout << "kubelek " << i << ": ";
            tab[i]->display();
        }
    }
};
#endif