#ifndef NODO_H
#define NODO_H

template <typename T>
class ListaLigada; // Forward declaration para conceder amistad

template <typename T>
class Nodo {
private:
    T dato;
    Nodo<T>* siguiente;
    Nodo<T>* anterior;

    // Encapsulamiento POO: solo ListaLigada accede a los miembros privados
    friend class ListaLigada<T>;

public:
    // Constructores y destructor
    Nodo(T valor) : dato(valor), siguiente(nullptr), anterior(nullptr) {}
    Nodo(const Nodo<T>& otro) : dato(otro.dato), siguiente(nullptr), anterior(nullptr) {}
    ~Nodo() {
        siguiente = nullptr;
        anterior = nullptr;
    }

    // Getters públicos
    T getDato() const { return dato; }
    Nodo<T>* getSiguiente() const { return siguiente; }
    Nodo<T>* getAnterior() const { return anterior; }
};

#endif
