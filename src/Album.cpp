#include "Album.h"

// =========================================================
// MÉTODOS AUXILIARES PRIVADOS
// =========================================================

int Album::longitudCadena(const char* cadena) {
    if (cadena == nullptr) return 0;
    int len = 0;
    while (cadena[len] != '\0') {
        len++;
    }
    return len;
}

void Album::copiarCadena(char* destino, const char* origen) {
    if (origen == nullptr || destino == nullptr) return;
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

bool Album::compararCadenas(const char* a, const char* b) {
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

Album::Album() {
    nombre = new char[1];
    nombre[0] = '\0';
    rutaAlmacenamiento = new char[1];
    rutaAlmacenamiento[0] = '\0';
    privacidad = 'P';
}

Album::Album(const char* nombre, const char* ruta, char privacidad) {
    int lenNom = longitudCadena(nombre);
    this->nombre = new char[lenNom + 1];
    copiarCadena(this->nombre, nombre);

    int lenRuta = longitudCadena(ruta);
    this->rutaAlmacenamiento = new char[lenRuta + 1];
    copiarCadena(this->rutaAlmacenamiento, ruta);

    this->privacidad = privacidad;
}

// Constructor de copia con COPIA PROFUNDA de las fotos
Album::Album(const Album& otro) {
    int lenNom = longitudCadena(otro.nombre);
    this->nombre = new char[lenNom + 1];
    copiarCadena(this->nombre, otro.nombre);

    int lenRuta = longitudCadena(otro.rutaAlmacenamiento);
    this->rutaAlmacenamiento = new char[lenRuta + 1];
    copiarCadena(this->rutaAlmacenamiento, otro.rutaAlmacenamiento);

    this->privacidad = otro.privacidad;

    // Duplicar cada foto instanciada para evitar punteros compartidos
    for (int i = 0; i < otro.fotos.obtenerTamanio(); ++i) {
        if (otro.fotos[i] != nullptr) {
            Foto* nuevaFoto = new Foto(*(otro.fotos[i]));
            nuevaFoto->setAlbumPadre(this);
            this->fotos.insertarAlFinal(nuevaFoto);
        }
    }
}

Album::~Album() {
    delete[] nombre;
    delete[] rutaAlmacenamiento;
    nombre = nullptr;
    rutaAlmacenamiento = nullptr;

    // Liberar la memoria de todas las fotos administradas por el álbum
    for (int i = 0; i < fotos.obtenerTamanio(); ++i) {
        delete fotos[i];
    }
    fotos.vaciar();
}

// =========================================================
// GETTERS Y SETTERS
// =========================================================

const char* Album::getNombre() const { return nombre; }
void Album::setNombre(const char* nom) {
    delete[] nombre;
    int len = longitudCadena(nom);
    nombre = new char[len + 1];
    copiarCadena(nombre, nom);
}

const char* Album::getRutaAlmacenamiento() const { return rutaAlmacenamiento; }
void Album::setRutaAlmacenamiento(const char* ruta) {
    delete[] rutaAlmacenamiento;
    int len = longitudCadena(ruta);
    rutaAlmacenamiento = new char[len + 1];
    copiarCadena(rutaAlmacenamiento, ruta);
}

char Album::getPrivacidad() const { return privacidad; }
void Album::setPrivacidad(char priv) { privacidad = priv; }

ListaLigada<Foto*>& Album::getFotos() { return fotos; }
const ListaLigada<Foto*>& Album::getFotos() const { return fotos; }

// =========================================================
// MÉTODOS DE NEGOCIO Y MEDICIÓN
// =========================================================

void Album::agregarFoto(Foto* f) {
    if (f != nullptr) {
        f->setAlbumPadre(this);
        fotos.insertarAlFinal(f);
    }
}

bool Album::esVisibleParaAmigos() const {
    return (privacidad == 'P' || privacidad == 'p' || privacidad == 'A' || privacidad == 'a');
}

unsigned long Album::obtenerMemoriaConsumida() const {
    unsigned long total = sizeof(*this);
    if (nombre) total += (longitudCadena(nombre) + 1) * sizeof(char);
    if (rutaAlmacenamiento) total += (longitudCadena(rutaAlmacenamiento) + 1) * sizeof(char);

    // Memoria consumida por los nodos de la ListaLigada
    total += sizeof(fotos) + (fotos.obtenerTamanio() * sizeof(Nodo<Foto*>));

    // Memoria consumida por cada objeto Foto en dynamic memory
    for (int i = 0; i < fotos.obtenerTamanio(); ++i) {
        if (fotos[i] != nullptr) {
            total += fotos[i]->obtenerMemoriaConsumida();
        }
    }
    return total;
}

// =========================================================
// SOBRECARGA DE OPERADORES
// =========================================================

Album& Album::operator=(const Album& otro) {
    if (this == &otro) return *this;

    // 1. Liberar recursos existentes
    delete[] nombre;
    delete[] rutaAlmacenamiento;

    for (int i = 0; i < fotos.obtenerTamanio(); ++i) {
        delete fotos[i];
    }
    fotos.vaciar();

    // 2. Copiar atributos simples
    int lenNom = longitudCadena(otro.nombre);
    this->nombre = new char[lenNom + 1];
    copiarCadena(this->nombre, otro.nombre);

    int lenRuta = longitudCadena(otro.rutaAlmacenamiento);
    this->rutaAlmacenamiento = new char[lenRuta + 1];
    copiarCadena(this->rutaAlmacenamiento, otro.rutaAlmacenamiento);

    this->privacidad = otro.privacidad;

    // 3. COPIA PROFUNDA de la lista de fotos
    for (int i = 0; i < otro.fotos.obtenerTamanio(); ++i) {
        if (otro.fotos[i] != nullptr) {
            Foto* nuevaFoto = new Foto(*(otro.fotos[i]));
            nuevaFoto->setAlbumPadre(this);
            this->fotos.insertarAlFinal(nuevaFoto);
        }
    }

    return *this;
}

bool Album::operator==(const Album& otro) const {
    return compararCadenas(this->nombre, otro.nombre) &&
           compararCadenas(this->rutaAlmacenamiento, otro.rutaAlmacenamiento);
}