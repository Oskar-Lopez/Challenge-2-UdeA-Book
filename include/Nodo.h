#ifndef NODO_H
#define NODO_H

template <typename T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    Nodo(T valor) {
        this->dato = valor;
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }

    Nodo(const Nodo<T>& otro) {
        this->dato = otro.dato;
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }

    ~Nodo() {
        this->siguiente = nullptr;
        this->anterior = nullptr;
    }
};

#endif
