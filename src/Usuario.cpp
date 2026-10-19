#include "Usuario.h"
#include "Mensaje.h"
#include "Album.h"
#include "Plataforma.h"
#include <iostream>

using namespace std;

// =========================================================
// AUXILIARES DE CADENAS
// =========================================================

int Usuario::longitudCadena(const char* cadena) {
    if (cadena == nullptr) return 0;
    int len = 0;
    while (cadena[len] != '\0') len++;
    return len;
}

void Usuario::copiarCadena(char* destino, const char* origen) {
    if (destino == nullptr || origen == nullptr) return;
    int i = 0;
    while (origen[i] != '\0') { destino[i] = origen[i]; i++; }
    destino[i] = '\0';
}

bool Usuario::compararCadenas(const char* a, const char* b) {
    if (a == nullptr || b == nullptr) return a == b;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

int Usuario::compararFechas(const char* a, const char* b) {
    if (a == nullptr && b == nullptr) return 0;
    if (a == nullptr) return -1;
    if (b == nullptr) return 1;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] < b[i]) return -1;
        if (a[i] > b[i]) return 1;
        i++;
    }
    if (a[i] == '\0' && b[i] == '\0') return 0;
    return (a[i] == '\0') ? -1 : 1;
}

// =========================================================
// CONSTRUCTORES Y DESTRUCTOR
// =========================================================

Usuario::Usuario() {
    username = new char[1];         username[0] = '\0';
    fechaNacimiento = new char[1];  fechaNacimiento[0] = '\0';
    correo = new char[1];           correo[0] = '\0';
    fotoPerfil = new char[1];       fotoPerfil[0] = '\0';
    ciudad = new char[1];           ciudad[0] = '\0';
    pais = new char[1];             pais[0] = '\0';
    fechaInscripcion = new char[1]; fechaInscripcion[0] = '\0';
}

Usuario::Usuario(const char* username, const char* fechaNacimiento, const char* correo,
                 const char* fotoPerfil, const char* ciudad, const char* pais,
                 const char* fechaInscripcion) {
    this->username = new char[longitudCadena(username) + 1];
    copiarCadena(this->username, username != nullptr ? username : "");

    this->fechaNacimiento = new char[longitudCadena(fechaNacimiento) + 1];
    copiarCadena(this->fechaNacimiento, fechaNacimiento != nullptr ? fechaNacimiento : "");

    this->correo = new char[longitudCadena(correo) + 1];
    copiarCadena(this->correo, correo != nullptr ? correo : "");

    this->fotoPerfil = new char[longitudCadena(fotoPerfil) + 1];
    copiarCadena(this->fotoPerfil, fotoPerfil != nullptr ? fotoPerfil : "");

    this->ciudad = new char[longitudCadena(ciudad) + 1];
    copiarCadena(this->ciudad, ciudad != nullptr ? ciudad : "");

    this->pais = new char[longitudCadena(pais) + 1];
    copiarCadena(this->pais, pais != nullptr ? pais : "");

    this->fechaInscripcion = new char[longitudCadena(fechaInscripcion) + 1];
    copiarCadena(this->fechaInscripcion, fechaInscripcion != nullptr ? fechaInscripcion : "");
}

Usuario::Usuario(const Usuario& otro) {
    username = new char[longitudCadena(otro.username) + 1];
    copiarCadena(username, otro.username);
    fechaNacimiento = new char[longitudCadena(otro.fechaNacimiento) + 1];
    copiarCadena(fechaNacimiento, otro.fechaNacimiento);
    correo = new char[longitudCadena(otro.correo) + 1];
    copiarCadena(correo, otro.correo);
    fotoPerfil = new char[longitudCadena(otro.fotoPerfil) + 1];
    copiarCadena(fotoPerfil, otro.fotoPerfil);
    ciudad = new char[longitudCadena(otro.ciudad) + 1];
    copiarCadena(ciudad, otro.ciudad);
    pais = new char[longitudCadena(otro.pais) + 1];
    copiarCadena(pais, otro.pais);
    fechaInscripcion = new char[longitudCadena(otro.fechaInscripcion) + 1];
    copiarCadena(fechaInscripcion, otro.fechaInscripcion);

    amigos = otro.amigos;
    solicitudes = otro.solicitudes;
    mensajesEnviados = otro.mensajesEnviados;
    mensajesRecibidos = otro.mensajesRecibidos;
    albumes = otro.albumes;
}

Usuario::~Usuario() {
    delete[] username;         delete[] fechaNacimiento;
    delete[] correo;           delete[] fotoPerfil;
    delete[] ciudad;           delete[] pais;
    delete[] fechaInscripcion;
}

// =========================================================
// GETTERS Y SETTERS
// =========================================================

const char* Usuario::getUsername() const { return username; }
void Usuario::setUsername(const char* username) {
    delete[] this->username;
    this->username = new char[longitudCadena(username) + 1];
    copiarCadena(this->username, username != nullptr ? username : "");
}

const char* Usuario::getFechaNacimiento() const { return fechaNacimiento; }
void Usuario::setFechaNacimiento(const char* fecha) {
    delete[] this->fechaNacimiento;
    this->fechaNacimiento = new char[longitudCadena(fecha) + 1];
    copiarCadena(this->fechaNacimiento, fecha != nullptr ? fecha : "");
}

const char* Usuario::getCorreo() const { return correo; }
void Usuario::setCorreo(const char* correo) {
    delete[] this->correo;
    this->correo = new char[longitudCadena(correo) + 1];
    copiarCadena(this->correo, correo != nullptr ? correo : "");
}

const char* Usuario::getFotoPerfil() const { return fotoPerfil; }
void Usuario::setFotoPerfil(const char* foto) {
    delete[] this->fotoPerfil;
    this->fotoPerfil = new char[longitudCadena(foto) + 1];
    copiarCadena(this->fotoPerfil, foto != nullptr ? foto : "");
}

const char* Usuario::getCiudad() const { return ciudad; }
void Usuario::setCiudad(const char* ciudad) {
    delete[] this->ciudad;
    this->ciudad = new char[longitudCadena(ciudad) + 1];
    copiarCadena(this->ciudad, ciudad != nullptr ? ciudad : "");
}

const char* Usuario::getPais() const { return pais; }
void Usuario::setPais(const char* pais) {
    delete[] this->pais;
    this->pais = new char[longitudCadena(pais) + 1];
    copiarCadena(this->pais, pais != nullptr ? pais : "");
}

const char* Usuario::getFechaInscripcion() const { return fechaInscripcion; }
void Usuario::setFechaInscripcion(const char* fecha) {
    delete[] this->fechaInscripcion;
    this->fechaInscripcion = new char[longitudCadena(fecha) + 1];
    copiarCadena(this->fechaInscripcion, fecha != nullptr ? fecha : "");
}

ListaLigada<Usuario*>& Usuario::getAmigos() { return amigos; }
ListaLigada<Usuario*>& Usuario::getSolicitudes() { return solicitudes; }
ListaLigada<Mensaje*>& Usuario::getMensajesEnviados() { return mensajesEnviados; }
ListaLigada<Mensaje*>& Usuario::getMensajesRecibidos() { return mensajesRecibidos; }
ListaLigada<Album*>& Usuario::getAlbumes() { return albumes; }

const ListaLigada<Usuario*>& Usuario::getAmigos() const { return amigos; }
const ListaLigada<Usuario*>& Usuario::getSolicitudes() const { return solicitudes; }
const ListaLigada<Mensaje*>& Usuario::getMensajesEnviados() const { return mensajesEnviados; }
const ListaLigada<Mensaje*>& Usuario::getMensajesRecibidos() const { return mensajesRecibidos; }
const ListaLigada<Album*>& Usuario::getAlbumes() const { return albumes; }

// =========================================================
// MÉTODOS DE NEGOCIO
// =========================================================

bool Usuario::esAmigo(const Usuario* otro) const {
    if (otro == nullptr) return false;
    for (int i = 0; i < amigos.obtenerTamanio(); ++i) {
        Plataforma::registrarIteracion();
        if (amigos[i] == otro) return true;
    }
    return false;
}

bool Usuario::tieneSolicitudDe(const Usuario* otro) const {
    if (otro == nullptr) return false;
    for (int i = 0; i < solicitudes.obtenerTamanio(); ++i) {
        Plataforma::registrarIteracion();
        if (solicitudes[i] == otro) return true;
    }
    return false;
}

void Usuario::enviarSolicitud(Usuario* destino) {
    if (destino == nullptr || destino == this) return;
    if (esAmigo(destino)) return;
    if (destino->tieneSolicitudDe(this)) return;
    if (tieneSolicitudDe(destino)) return;

    destino->solicitudes.insertarAlFinal(this);
    Plataforma::registrarIteracion();
    cout << "Solicitud enviada a " << destino->getUsername() << endl;
}

void Usuario::aceptarSolicitud(Usuario* origen) {
    if (origen == nullptr) return;
    if (solicitudes.eliminarElemento(origen)) {
        amigos.insertarAlFinal(origen);
        origen->amigos.insertarAlFinal(this);
        Plataforma::registrarIteracion(2);
        cout << "Ahora eres amigo de " << origen->getUsername() << endl;
    }
}

static int contarAmigosEnComun(const Usuario* a, const Usuario* b) {
    int contador = 0;
    const ListaLigada<Usuario*>& amigosA = a->getAmigos();
    const ListaLigada<Usuario*>& amigosB = b->getAmigos();
    for (int i = 0; i < amigosA.obtenerTamanio(); ++i) {
        Plataforma::registrarIteracion();
        for (int j = 0; j < amigosB.obtenerTamanio(); ++j) {
            Plataforma::registrarIteracion();
            if (amigosA[i] == amigosB[j]) { contador++; break; }
        }
    }
    return contador;
}

void Usuario::verSugerencias(int k) const {
    if (k < 1) k = 1;
    if (k > 20) k = 20;
    cout << "=== Sugerencias de amistad para " << username << " ===\n";

    ListaLigada<Usuario*> candidatos;
    ListaLigada<int> conteos;

    for (int i = 0; i < amigos.obtenerTamanio(); ++i) {
        Plataforma::registrarIteracion();
        Usuario* amigoActual = amigos[i];
        const ListaLigada<Usuario*>& amigosDeAmigo = amigoActual->getAmigos();
        for (int j = 0; j < amigosDeAmigo.obtenerTamanio(); ++j) {
            Plataforma::registrarIteracion();
            Usuario* candidato = amigosDeAmigo[j];
            if (candidato == this) continue;
            if (esAmigo(candidato)) continue;
            if (tieneSolicitudDe(candidato)) continue;
            if (candidato->tieneSolicitudDe(this)) continue;

            bool yaExiste = false;
            for (int m = 0; m < candidatos.obtenerTamanio(); ++m) {
                Plataforma::registrarIteracion();
                if (candidatos[m] == candidato) { yaExiste = true; break; }
            }
            if (yaExiste) continue;

            int comunes = contarAmigosEnComun(this, candidato);
            candidatos.insertarAlFinal(candidato);
            conteos.insertarAlFinal(comunes);
        }
    }

    int n = candidatos.obtenerTamanio();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
            Plataforma::registrarIteracion();
            if (conteos[j] < conteos[j + 1]) {
                Usuario* tmpU = candidatos[j];
                candidatos[j] = candidatos[j + 1];
                candidatos[j + 1] = tmpU;
                int tmpC = conteos[j];
                conteos[j] = conteos[j + 1];
                conteos[j + 1] = tmpC;
            }
        }
    }

    int mostradas = (n < k) ? n : k;
    if (mostradas == 0) { cout << "No hay sugerencias disponibles.\n"; return; }
    for (int i = 0; i < mostradas; ++i) {
        cout << (i + 1) << ". " << candidatos[i]->getUsername()
        << " (" << conteos[i] << " amigos en comun)\n";
    }
}

void Usuario::enviarMensaje(Usuario* amigo, const char* texto, const char* fecha) {
    if (amigo == nullptr || !esAmigo(amigo)) {
        cout << "Error: Solo se pueden enviar mensajes a amigos.\n"; return;
    }
    if (texto == nullptr || longitudCadena(texto) == 0) {
        cout << "Error: no se pueden enviar mensajes vacios.\n"; return;
    }
    if (longitudCadena(texto) > 512) {
        cout << "Error: el mensaje excede 512 caracteres.\n"; return;
    }
    Mensaje* nuevo = new Mensaje(texto, fecha, this, amigo);
    mensajesEnviados.insertarAlFinal(nuevo);
    amigo->mensajesRecibidos.insertarAlFinal(nuevo);
    Plataforma::registrarIteracion(2);
    cout << "Mensaje enviado a " << amigo->getUsername() << endl;
}

void Usuario::buscarMensajes(const char* inicio, const char* fin) const {
    cout << "=== Mensajes recibidos entre " << inicio << " y " << fin << " ===\n";
    int encontrados = 0;
    for (int i = 0; i < mensajesRecibidos.obtenerTamanio(); ++i) {
        Plataforma::registrarIteracion();
        Mensaje* m = mensajesRecibidos[i];
        const char* fecha = m->getFechaEnvio();
        if (compararFechas(fecha, inicio) >= 0 &&
            compararFechas(fecha, fin) <= 0) {
            cout << "De " << m->getEmisor()->getUsername()
            << " [" << fecha << "]: " << m->getTexto() << "\n";
            encontrados++;
        }
    }
    if (encontrados == 0) cout << "No se encontraron mensajes.\n";
}

void Usuario::agregarAlbum(Album* album) {
    if (album != nullptr) albumes.insertarAlFinal(album);
}

// =========================================================
// MEMORIA
// =========================================================

unsigned long Usuario::calcularMemoriaBytes() const {
    unsigned long total = sizeof(*this);
    total += longitudCadena(username) + 1;
    total += longitudCadena(fechaNacimiento) + 1;
    total += longitudCadena(correo) + 1;
    total += longitudCadena(fotoPerfil) + 1;
    total += longitudCadena(ciudad) + 1;
    total += longitudCadena(pais) + 1;
    total += longitudCadena(fechaInscripcion) + 1;
    total += amigos.obtenerTamanio() * sizeof(Nodo<Usuario*>);
    total += solicitudes.obtenerTamanio() * sizeof(Nodo<Usuario*>);
    total += mensajesEnviados.obtenerTamanio() * sizeof(Nodo<Mensaje*>);
    total += mensajesRecibidos.obtenerTamanio() * sizeof(Nodo<Mensaje*>);
    total += albumes.obtenerTamanio() * sizeof(Nodo<Album*>);
    return total;
}

// =========================================================
// SOBRECARGA DE OPERADORES
// =========================================================

bool Usuario::operator==(const Usuario& otro) const {
    return compararCadenas(this->username, otro.username);
}

bool Usuario::operator!=(const Usuario& otro) const {
    return !(*this == otro);
}

Usuario& Usuario::operator=(const Usuario& otro) {
    if (this == &otro) return *this;
    delete[] username; delete[] fechaNacimiento;
    delete[] correo;   delete[] fotoPerfil;
    delete[] ciudad;   delete[] pais;
    delete[] fechaInscripcion;

    username = new char[longitudCadena(otro.username) + 1];
    copiarCadena(username, otro.username);
    fechaNacimiento = new char[longitudCadena(otro.fechaNacimiento) + 1];
    copiarCadena(fechaNacimiento, otro.fechaNacimiento);
    correo = new char[longitudCadena(otro.correo) + 1];
    copiarCadena(correo, otro.correo);
    fotoPerfil = new char[longitudCadena(otro.fotoPerfil) + 1];
    copiarCadena(fotoPerfil, otro.fotoPerfil);
    ciudad = new char[longitudCadena(otro.ciudad) + 1];
    copiarCadena(ciudad, otro.ciudad);
    pais = new char[longitudCadena(otro.pais) + 1];
    copiarCadena(pais, otro.pais);
    fechaInscripcion = new char[longitudCadena(otro.fechaInscripcion) + 1];
    copiarCadena(fechaInscripcion, otro.fechaInscripcion);

    amigos = otro.amigos;
    solicitudes = otro.solicitudes;
    mensajesEnviados = otro.mensajesEnviados;
    mensajesRecibidos = otro.mensajesRecibidos;
    albumes = otro.albumes;
    return *this;
}

void imprimirUsuario(const Usuario& u) {
    cout << "Usuario: " << u.username << "\n";
    cout << "  Correo: " << u.correo << "\n";
    cout << "  Ciudad: " << u.ciudad << ", " << u.pais << "\n";
    cout << "  Amigos: " << u.amigos.obtenerTamanio() << "\n---\n";
}
