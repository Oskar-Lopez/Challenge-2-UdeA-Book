#include "Mensaje.h"
#include "Usuario.h"
#include <iostream>

using namespace std;

int Mensaje::longitudCadena(const char* cadena) {
    if (cadena == nullptr) return 0;
    int len = 0;
    while (cadena[len] != '\0') len++;
    return len;
}

void Mensaje::copiarCadena(char* destino, const char* origen) {
    int i = 0;
    while (origen[i] != '\0') { destino[i] = origen[i]; i++; }
    destino[i] = '\0';
}

bool Mensaje::compararCadenas(const char* a, const char* b) {
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

Mensaje::Mensaje() {
    texto = new char[1]; texto[0] = '\0';
    fechaEnvio = new char[1]; fechaEnvio[0] = '\0';
    leido = false;
    emisor = nullptr;
    receptor = nullptr;
}

Mensaje::Mensaje(const char* texto, const char* fecha,
                 Usuario* emisor, Usuario* receptor) {
    int lenTexto = longitudCadena(texto);
    if (lenTexto > 512) lenTexto = 512;
    this->texto = new char[lenTexto + 1];
    for (int i = 0; i < lenTexto; i++) this->texto[i] = texto[i];
    this->texto[lenTexto] = '\0';

    int lenFecha = longitudCadena(fecha);
    this->fechaEnvio = new char[lenFecha + 1];
    copiarCadena(this->fechaEnvio, fecha);

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

const char* Mensaje::getTexto() const { return texto; }
void Mensaje::setTexto(const char* texto) {
    delete[] this->texto;
    int lenTexto = longitudCadena(texto);
    if (lenTexto > 512) lenTexto = 512;
    this->texto = new char[lenTexto + 1];
    for (int i = 0; i < lenTexto; i++) this->texto[i] = texto[i];
    this->texto[lenTexto] = '\0';
}

const char* Mensaje::getFechaEnvio() const { return fechaEnvio; }
void Mensaje::setFechaEnvio(const char* fecha) {
    delete[] this->fechaEnvio;
    int lenFecha = longitudCadena(fecha);
    this->fechaEnvio = new char[lenFecha + 1];
    copiarCadena(this->fechaEnvio, fecha);
}

bool Mensaje::getLeido() const { return leido; }
void Mensaje::setLeido(bool leido) { this->leido = leido; }

Usuario* Mensaje::getEmisor() const { return emisor; }
void Mensaje::setEmisor(Usuario* emisor) { this->emisor = emisor; }

Usuario* Mensaje::getReceptor() const { return receptor; }
void Mensaje::setReceptor(Usuario* receptor) { this->receptor = receptor; }

void Mensaje::marcarComoLeido() { this->leido = true; }
void Mensaje::marcarComoNoLeido() { this->leido = false; }
int Mensaje::obtenerLongitudTexto() const { return longitudCadena(texto); }

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

void imprimirMensaje(const Mensaje& m) {
    cout << "De: "   << (m.emisor ? m.emisor->getUsername() : "N/A") << "\n";
    cout << "Para: " << (m.receptor ? m.receptor->getUsername() : "N/A") << "\n";
    cout << "Fecha: " << m.fechaEnvio << "\n";
    cout << "Leido: " << (m.leido ? "Si" : "No") << "\n";
    cout << "Texto: " << m.texto << "\n---\n";
}
