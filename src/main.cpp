#include <iostream>
#include "ListaLigada.h"

int main() {
    ListaLigada<int> lista;

    lista.insertarAlFinal(10);
    lista.insertarAlFinal(20);
    lista.insertarAlFinal(30);

    std::cout << "Elemento [0]: " << lista[0] << std::endl;
    std::cout << "Elemento [1]: " << lista[1] << std::endl;
    std::cout << "Elemento [2]: " << lista[2] << std::endl;

    std::cout << "Tamanio: " << lista.obtenerTamanio() << std::endl;

    lista.eliminarElemento(20);
    std::cout << "Tras eliminar 20, tamanio: " << lista.obtenerTamanio() << std::endl;

    Nodo<int>* actual = lista.getCabeza();
    for (int i = 0; i < 6; ++i) {
        std::cout << actual->dato << " -> ";
        actual = actual->siguiente;
    }
    std::cout << "(vuelve al inicio)" << std::endl;

    return 0;
}
