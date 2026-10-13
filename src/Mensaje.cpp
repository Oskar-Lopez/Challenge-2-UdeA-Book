#include "Mensaje.h"
#include <iostream>
using namespace std;

// =========================================================
// MÉTODOS AUXILIARES PRIVADOS
// =========================================================

int Mensaje::longitudCadena(const char* cadena) {
    if (cadena == nullptr) return 0;
    int len = 0;
    while (cadena[len] != '\0') {
        len++;
    }
    return len;
}

void Mensaje::copiarCadena(char* destino, const char* origen) {
    if (destino == nullptr || origen == nullptr) return;
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

bool Mensaje::compararCadenas(const char* a, const char* b) {
    if (a == nullptr || b == nullptr) return a == b;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

// =========================================================
// CONSTRUCTORES Y DESTRUCTOR
// =========================================================

Mensaje::Mensaje() {
    texto = new char[1]{'\0'};
    fechaEnvio = new char[1]{'\0'};
    leido = false;
    emisor = nullptr;
    receptor = nullptr;
}

Mensaje::Mensaje(const char* texto, const char* fecha,
                 Usuario* emisor, Usuario* receptor) {
    int lenTexto = longitudCadena(texto);
    if (lenTexto > 512) lenTexto = 512;

    this->texto = new char[lenTexto + 1];
    for (int i = 0; i < lenTexto; i++) {
        this->texto[i] = texto[i];
    }
    this->texto[lenTexto] = '\0';

    int lenFecha = longitudCadena(fecha);
    this->fechaEnvio = new char[lenFecha + 1];
    copiarCadena(this->fechaEnvio, fecha != nullptr ? fecha : "");

    this->leido = false;
    this->emisor = emisor;
    this->receptor = receptor;
}

Mensaje::Mensaje(const Mensaje& otro) {
    int lenTexto = longitudCadena(otro.texto);
    this->texto = new char[lenTexto + 1];
    copiarCadena(this->texto, otro.texto);

    int lenFecha = longitudCadena(otro.fechaEnvio);
    this->fechaEnvio = new char[lenFecha + 1];
    copiarCadena(this->fechaEnvio, otro.fechaEnvio);

    this->leido = otro.leido;
    this->emisor = otro.emisor;
    this->receptor = otro.receptor;
}

Mensaje::~Mensaje() {
    delete[] texto;
    delete[] fechaEnvio;
    texto = nullptr;
    fechaEnvio = nullptr;
}

// =========================================================
// GETTERS Y SETTERS
// =========================================================

const char* Mensaje::getTexto() const {
    return texto;
}

void Mensaje::setTexto(const char* texto) {
    delete[] this->texto;

    int lenTexto = longitudCadena(texto);
    if (lenTexto > 512) lenTexto = 512;

    this->texto = new char[lenTexto + 1];
    for (int i = 0; i < lenTexto; i++) {
        this->texto[i] = texto[i];
    }
    this->texto[lenTexto] = '\0';
}

const char* Mensaje::getFechaEnvio() const {
    return fechaEnvio;
}

void Mensaje::setFechaEnvio(const char* fecha) {
    delete[] this->fechaEnvio;
    int lenFecha = longitudCadena(fecha);
    this->fechaEnvio = new char[lenFecha + 1];
    copiarCadena(this->fechaEnvio, fecha != nullptr ? fecha : "");
}

bool Mensaje::getLeido() const {
    return leido;
}

void Mensaje::setLeido(bool leido) {
    this->leido = leido;
}

Usuario* Mensaje::getEmisor() const {
    return emisor;
}

void Mensaje::setEmisor(Usuario* emisor) {
    this->emisor = emisor;
}

Usuario* Mensaje::getReceptor() const {
    return receptor;
}

void Mensaje::setReceptor(Usuario* receptor) {
    this->receptor = receptor;
}

// =========================================================
// MÉTODOS DE NEGOCIO
// =========================================================

void Mensaje::marcarComoLeido() {
    this->leido = true;
}

void Mensaje::marcarComoNoLeido() {
    this->leido = false;
}

int Mensaje::obtenerLongitudTexto() const {
    return longitudCadena(texto);
}

// =========================================================
// SOBRECARGA DE OPERADORES
// =========================================================

bool Mensaje::operator==(const Mensaje& otro) const {
    return compararCadenas(this->texto, otro.texto) &&
           compararCadenas(this->fechaEnvio, otro.fechaEnvio) &&
           (this->emisor == otro.emisor) &&
           (this->receptor == otro.receptor);
}

Mensaje& Mensaje::operator=(const Mensaje& otro) {
    if (this == &otro) return *this;

    delete[] texto;
    delete[] fechaEnvio;

    int lenTexto = longitudCadena(otro.texto);
    texto = new char[lenTexto + 1];
    copiarCadena(texto, otro.texto);

    int lenFecha = longitudCadena(otro.fechaEnvio);
    fechaEnvio = new char[lenFecha + 1];
    copiarCadena(fechaEnvio, otro.fechaEnvio);

    leido = otro.leido;
    emisor = otro.emisor;
    receptor = otro.receptor;

    return *this;
}

// =========================================================
// FUNCIÓN AMIGA
// =========================================================

void imprimirMensaje(const Mensaje& m) {
    cout << "De: " << (m.emisor ? "Usuario" : "N/A") << endl;
    cout << "Para: " << (m.receptor ? "Usuario" : "N/A") << endl;
    cout << "Fecha: " << (m.fechaEnvio ? m.fechaEnvio : "N/A") << endl;
    cout << "Leido: " << (m.leido ? "Si" : "No") << endl;
    cout << "Texto: " << (m.texto ? m.texto : "") << endl;
    cout << "---" << endl;
}
