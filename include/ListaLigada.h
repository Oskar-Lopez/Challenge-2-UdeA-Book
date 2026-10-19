#ifndef LISTALIGADA_H
#define LISTALIGADA_H

#include "Nodo.h"

template <typename T>
class ListaLigada {
private:
    Nodo<T>* cabeza;
    Nodo<T>* cola;
    int tamanio;

public:
    // Constructores y destructor
    ListaLigada();
    ListaLigada(const ListaLigada<T>& otra);
    ~ListaLigada();

    // Operaciones principales con paso por referencia constante
    void insertarAlFinal(const T& elemento);
    bool eliminarElemento(const T& elemento);
    Nodo<T>* obtenerNodo(int posicion) const;
    int obtenerTamanio() const;
    bool estaVacia() const;
    void vaciar();

    // Sobrecarga de operadores
    T& operator[](int indice);
    const T& operator[](int indice) const;
    ListaLigada<T>& operator=(const ListaLigada<T>& otra);
    bool operator==(const ListaLigada<T>& otra) const;

    // Getters
    Nodo<T>* getCabeza() const { return cabeza; }
    Nodo<T>* getCola() const { return cola; }
};

// =========================================================
// IMPLEMENTACIÓN
// =========================================================

template <typename T>
ListaLigada<T>::ListaLigada() : cabeza(nullptr), cola(nullptr), tamanio(0) {}

template <typename T>
ListaLigada<T>::ListaLigada(const ListaLigada<T>& otra) : cabeza(nullptr), cola(nullptr), tamanio(0) {
    Nodo<T>* actual = otra.cabeza;
    for (int i = 0; i < otra.tamanio; ++i) {
        insertarAlFinal(actual->dato);
        actual = actual->siguiente;
    }
}

template <typename T>
ListaLigada<T>::~ListaLigada() {
    vaciar();
}

template <typename T>
void ListaLigada<T>::insertarAlFinal(const T& elemento) {
    Nodo<T>* nuevo = new Nodo<T>(elemento);

    if (cabeza == nullptr) {
        cabeza = nuevo;
        cola = nuevo;
        nuevo->siguiente = nuevo;
        nuevo->anterior = nuevo;
    } else {
        nuevo->anterior = cola;
        nuevo->siguiente = cabeza;
        cola->siguiente = nuevo;
        cabeza->anterior = nuevo;
        cola = nuevo;
    }
    tamanio++;
}

template <typename T>
bool ListaLigada<T>::eliminarElemento(const T& elemento) {
    if (cabeza == nullptr) return false;

    Nodo<T>* actual = cabeza;
    for (int i = 0; i < tamanio; ++i) {
        if (actual->dato == elemento) {
            if (tamanio == 1) {
                cabeza = nullptr;
                cola = nullptr;
            } else {
                actual->anterior->siguiente = actual->siguiente;
                actual->siguiente->anterior = actual->anterior;
                if (actual == cabeza) cabeza = actual->siguiente;
                if (actual == cola) cola = actual->anterior;
            }
            delete actual;
            tamanio--;
            return true;
        }
        actual = actual->siguiente;
    }
    return false;
}

template <typename T>
Nodo<T>* ListaLigada<T>::obtenerNodo(int posicion) const {
    if (posicion < 0 || posicion >= tamanio) return nullptr;

    Nodo<T>* actual = cabeza;
    for (int i = 0; i < posicion; ++i) {
        actual = actual->siguiente;
    }
    return actual;
}

template <typename T>
int ListaLigada<T>::obtenerTamanio() const {
    return tamanio;
}

template <typename T>
bool ListaLigada<T>::estaVacia() const {
    return tamanio == 0;
}

template <typename T>
void ListaLigada<T>::vaciar() {
    if (cabeza == nullptr) return;

    Nodo<T>* actual = cabeza;
    for (int i = 0; i < tamanio; ++i) {
        Nodo<T>* siguiente = actual->siguiente;
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
}

// =========================================================
// SOBRECARGA DE OPERADORES SEGUROS
// =========================================================

template <typename T>
T& ListaLigada<T>::operator[](int indice) {
    if (cabeza == nullptr) {
        static T defecto{};
        return defecto;
    }
    Nodo<T>* nodo = obtenerNodo(indice);
    if (nodo == nullptr) {
        return cabeza->dato;
    }
    return nodo->dato;
}

template <typename T>
const T& ListaLigada<T>::operator[](int indice) const {
    if (cabeza == nullptr) {
        static T defecto{};
        return defecto;
    }
    Nodo<T>* nodo = obtenerNodo(indice);
    if (nodo == nullptr) {
        return cabeza->dato;
    }
    return nodo->dato;
}

template <typename T>
ListaLigada<T>& ListaLigada<T>::operator=(const ListaLigada<T>& otra) {
    if (this == &otra) return *this;

    vaciar();

    Nodo<T>* actual = otra.cabeza;
    for (int i = 0; i < otra.tamanio; ++i) {
        insertarAlFinal(actual->dato);
        actual = actual->siguiente;
    }
    return *this;
}

template <typename T>
bool ListaLigada<T>::operator==(const ListaLigada<T>& otra) const {
    if (tamanio != otra.tamanio) return false;

    Nodo<T>* a = cabeza;
    Nodo<T>* b = otra.cabeza;
    for (int i = 0; i < tamanio; ++i) {
        if (a->dato != b->dato) return false;
        a = a->siguiente;
        b = b->siguiente;
    }
    return true;
}

#endif
