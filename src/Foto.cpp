#include "Foto.h"

int Foto::longitudCadena(const char* cadena) {
    if (cadena == nullptr) return 0;
    int len = 0;
    while (cadena[len] != '\0') {
        len++;
    }
    return len;
}

void Foto::copiarCadena(char* destino, const char* origen) {
    if (origen == nullptr || destino == nullptr) return;
    int i = 0;
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

bool Foto::compararCadenas(const char* a, const char* b) {
    if (a == nullptr || b == nullptr) return a == b;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

Foto::Foto() {
    fechaCaptura = new char[1];
    fechaCaptura[0] = '\0';
    rutaArchivo = new char[1];
    rutaArchivo[0] = '\0';
    tamanioBytes = 0;
    likes = 0;
    albumPadre = nullptr;
}

Foto::Foto(const char* fecha, const char* ruta, long tamanio, int likes, Album* album) {
    int lenFecha = longitudCadena(fecha);
    fechaCaptura = new char[lenFecha + 1];
    copiarCadena(fechaCaptura, fecha);

    int lenRuta = longitudCadena(ruta);
    rutaArchivo = new char[lenRuta + 1];
    copiarCadena(rutaArchivo, ruta);

    this->tamanioBytes = tamanio;
    this->likes = (likes < 0) ? 0 : likes;
    this->albumPadre = album;
}

Foto::Foto(const Foto& otra) {
    int lenFecha = longitudCadena(otra.fechaCaptura);
    fechaCaptura = new char[lenFecha + 1];
    copiarCadena(fechaCaptura, otra.fechaCaptura);

    int lenRuta = longitudCadena(otra.rutaArchivo);
    rutaArchivo = new char[lenRuta + 1];
    copiarCadena(rutaArchivo, otra.rutaArchivo);

    this->tamanioBytes = otra.tamanioBytes;
    this->likes = otra.likes;
    this->albumPadre = otra.albumPadre;
}

Foto::~Foto() {
    delete[] fechaCaptura;
    delete[] rutaArchivo;
    fechaCaptura = nullptr;
    rutaArchivo = nullptr;
    albumPadre = nullptr;
}

const char* Foto::getFechaCaptura() const { return fechaCaptura; }
void Foto::setFechaCaptura(const char* fecha) {
    delete[] fechaCaptura;
    int len = longitudCadena(fecha);
    fechaCaptura = new char[len + 1];
    copiarCadena(fechaCaptura, fecha);
}

const char* Foto::getRutaArchivo() const { return rutaArchivo; }
void Foto::setRutaArchivo(const char* ruta) {
    delete[] rutaArchivo;
    int len = longitudCadena(ruta);
    rutaArchivo = new char[len + 1];
    copiarCadena(rutaArchivo, ruta);
}

long Foto::getTamanioBytes() const { return tamanioBytes; }
void Foto::setTamanioBytes(long tamanio) { tamanioBytes = tamanio; }

int Foto::getLikes() const { return likes; }
void Foto::setLikes(int l) { likes = (l < 0) ? 0 : l; }

Album* Foto::getAlbumPadre() const { return albumPadre; }
void Foto::setAlbumPadre(Album* album) { albumPadre = album; }

void Foto::darQuitarLike(bool incrementar) {
    if (incrementar) {
        likes++;
    } else if (likes > 0) {
        likes--;
    }
}

unsigned long Foto::obtenerMemoriaConsumida() const {
    unsigned long total = sizeof(*this);
    if (fechaCaptura) total += (longitudCadena(fechaCaptura) + 1) * sizeof(char);
    if (rutaArchivo) total += (longitudCadena(rutaArchivo) + 1) * sizeof(char);
    return total;
}

Foto& Foto::operator=(const Foto& otra) {
    if (this == &otra) return *this;

    delete[] fechaCaptura;
    delete[] rutaArchivo;

    int lenFecha = longitudCadena(otra.fechaCaptura);
    fechaCaptura = new char[lenFecha + 1];
    copiarCadena(fechaCaptura, otra.fechaCaptura);

    int lenRuta = longitudCadena(otra.rutaArchivo);
    rutaArchivo = new char[lenRuta + 1];
    copiarCadena(rutaArchivo, otra.rutaArchivo);

    this->tamanioBytes = otra.tamanioBytes;
    this->likes = otra.likes;
    this->albumPadre = otra.albumPadre;

    return *this;
}

bool Foto::operator==(const Foto& otra) const {
    return compararCadenas(this->rutaArchivo, otra.rutaArchivo);
}