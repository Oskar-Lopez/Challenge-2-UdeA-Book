#include <iostream>
#include "ListaLigada.h"
#include "Mensaje.h"
using namespace std;

int main() {
    // Lista ligada
    ListaLigada<int> lista;
    lista.insertarAlFinal(10);
    lista.insertarAlFinal(20);
    lista.insertarAlFinal(30);

    cout << "=== Lista Ligada ===" << endl;
    cout << "Elemento [0]: " << lista[0] << endl;
    cout << "Tamanio: " << lista.obtenerTamanio() << endl;

    // Mensaje
    cout << "\n=== Mensaje ===" << endl;
    Mensaje m1("Hola, como estas?", "2026-10-12 14:30", nullptr, nullptr);
    cout << "Texto: " << m1.getTexto() << endl;
    cout << "Fecha: " << m1.getFechaEnvio() << endl;
    cout << "Leido: " << (m1.getLeido() ? "Si" : "No") << endl;

    m1.marcarComoLeido();
    cout << "Tras marcar leido: " << (m1.getLeido() ? "Si" : "No") << endl;
    cout << "Longitud: " << m1.obtenerLongitudTexto() << endl;

    // Copia
    Mensaje m2 = m1;
    cout << "Copia - Texto: " << m2.getTexto() << endl;

    // Igualdad
    if (m1 == m2) {
        cout << "m1 y m2 son iguales" << endl;
    }

    // Función amiga
    imprimirMensaje(m1);

    return 0;
}
