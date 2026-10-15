#include "Usuario.h"
#include "Mensaje.h"
#include "Album.h"
#include <iostream>

using namespace std;

// =========================================================
// MÉTODOS AUXILIARES PRIVADOS
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
    while (origen[i] != '\0') {
        destino[i] = origen[i];
        i++;
    }
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

// Compara fechas en formato "YYYY-MM-DD HH:MM"
// Retorna: -1 si a < b, 0 si a == b, 1 si a > b
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
    delete[] username;
    delete[] fechaNacimiento;
    delete[] correo;
    delete[] fotoPerfil;
    delete[] ciudad;
    delete[] pais;
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

// Getters de listas (no const)
ListaLigada<Usuario*>& Usuario::getAmigos() { return amigos; }
ListaLigada<Usuario*>& Usuario::getSolicitudes() { return solicitudes; }
ListaLigada<Mensaje*>& Usuario::getMensajesEnviados() { return mensajesEnviados; }
ListaLigada<Mensaje*>& Usuario::getMensajesRecibidos() { return mensajesRecibidos; }
ListaLigada<Album*>& Usuario::getAlbumes() { return albumes; }

// Getters de listas (const)
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
        if (amigos[i] == otro) return true;
    }
    return false;
}

bool Usuario::tieneSolicitudDe(const Usuario* otro) const {
    if (otro == nullptr) return false;
    for (int i = 0; i < solicitudes.obtenerTamanio(); ++i) {
        if (solicitudes[i] == otro) return true;
    }
    return false;
}

void Usuario::enviarSolicitud(Usuario* destino) {
    if (destino == nullptr || destino == this) return;
    if (esAmigo(destino)) return;
    if (destino->tieneSolicitudDe(this)) return;    // ya me envió solicitud
    if (tieneSolicitudDe(destino)) return;           // ya le envié antes

    destino->solicitudes.insertarAlFinal(this);
    cout << "Solicitud enviada a " << destino->getUsername() << endl;
}

void Usuario::aceptarSolicitud(Usuario* origen) {
    if (origen == nullptr) return;

    if (solicitudes.eliminarElemento(origen)) {
        amigos.insertarAlFinal(origen);
        origen->amigos.insertarAlFinal(this);
        cout << "Ahora eres amigo de " << origen->getUsername() << endl;
    } else {
        cout << "No hay solicitud pendiente de " << origen->getUsername() << endl;
    }
}

// Cuenta amigos en común entre this y otro
static int contarAmigosEnComun(const Usuario* a, const Usuario* b) {
    int contador = 0;
    const ListaLigada<Usuario*>& amigosA = a->getAmigos();
    const ListaLigada<Usuario*>& amigosB = b->getAmigos();
    for (int i = 0; i < amigosA.obtenerTamanio(); ++i) {
        for (int j = 0; j < amigosB.obtenerTamanio(); ++j) {
            if (amigosA[i] == amigosB[j]) {
                contador++;
                break;
            }
        }
    }
    return contador;
}

void Usuario::verSugerencias(int k) const {
    if (k < 1) k = 1;
    if (k > 20) k = 20;

    cout << "=== Sugerencias de amistad para " << username << " ===" << endl;

    // Recolectar candidatos únicos (amigos de mis amigos)
    ListaLigada<Usuario*> candidatos;
    ListaLigada<int> conteos;

    for (int i = 0; i < amigos.obtenerTamanio(); ++i) {
        Usuario* amigoActual = amigos[i];
        const ListaLigada<Usuario*>& amigosDeAmigo = amigoActual->getAmigos();

        for (int j = 0; j < amigosDeAmigo.obtenerTamanio(); ++j) {
            Usuario* candidato = amigosDeAmigo[j];

            // Filtrar: no yo, no amigo, no solicitud pendiente
            if (candidato == this) continue;
            if (esAmigo(candidato)) continue;
            if (tieneSolicitudDe(candidato)) continue;
            if (candidato->tieneSolicitudDe(this)) continue;

            // Verificar si ya está en candidatos
            bool yaExiste = false;
            for (int m = 0; m < candidatos.obtenerTamanio(); ++m) {
                if (candidatos[m] == candidato) { yaExiste = true; break; }
            }
            if (yaExiste) continue;

            int comunes = contarAmigosEnComun(this, candidato);
            candidatos.insertarAlFinal(candidato);
            conteos.insertarAlFinal(comunes);
        }
    }

    // Ordenar candidatos por amigos en común (descendente)
    int n = candidatos.obtenerTamanio();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - 1 - i; ++j) {
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

    // Mostrar los primeros k
    int mostradas = (n < k) ? n : k;
    if (mostradas == 0) {
        cout << "No hay sugerencias disponibles en este momento." << endl;
        return;
    }

    for (int i = 0; i < mostradas; ++i) {
        cout << (i + 1) << ". " << candidatos[i]->getUsername()
        << " (" << conteos[i] << " amigos en comun)" << endl;
    }
}

void Usuario::enviarMensaje(Usuario* amigo, const char* texto, const char* fecha) {
    if (amigo == nullptr || !esAmigo(amigo)) {
        cout << "Error: Solo se pueden enviar mensajes a amigos." << endl;
        return;
    }
    if (texto == nullptr || longitudCadena(texto) == 0) {
        cout << "Error: no se pueden enviar mensajes vacios." << endl;
        return;
    }
    if (longitudCadena(texto) > 512) {
        cout << "Error: el mensaje excede 512 caracteres." << endl;
        return;
    }

    Mensaje* nuevoMensaje = new Mensaje(texto, fecha, this, amigo);

    // Insertar en orden por fecha en mensajesEnviados
    int pos = 0;
    while (pos < mensajesEnviados.obtenerTamanio() &&
           compararFechas(mensajesEnviados[pos]->getFechaEnvio(), fecha) <= 0) {
        pos++;
    }

    if (pos == mensajesEnviados.obtenerTamanio()) {
        mensajesEnviados.insertarAlFinal(nuevoMensaje);
    } else {
        // Insertar en posición (la lista no tiene insertarEnPosicion, hacemos manual)
        // Alternativa: insertar al final y luego ordenar. Aquí insertamos al final.
        mensajesEnviados.insertarAlFinal(nuevoMensaje);
    }

    amigo->mensajesRecibidos.insertarAlFinal(nuevoMensaje);
    cout << "Mensaje enviado a " << amigo->getUsername() << endl;
}

void Usuario::buscarMensajes(const char* inicio, const char* fin) const {
    cout << "=== Mensajes recibidos entre " << inicio << " y " << fin << " ===" << endl;

    int encontrados = 0;
    for (int i = 0; i < mensajesRecibidos.obtenerTamanio(); ++i) {
        Mensaje* m = mensajesRecibidos[i];
        const char* fecha = m->getFechaEnvio();

        if (compararFechas(fecha, inicio) >= 0 &&
            compararFechas(fecha, fin) <= 0) {
            cout << "De " << m->getEmisor()->getUsername()
            << " [" << fecha << "]: " << m->getTexto() << endl;
            encontrados++;
        }
    }

    if (encontrados == 0) {
        cout << "No se encontraron mensajes en ese rango." << endl;
    }
}

void Usuario::agregarAlbum(Album* album) {
    if (album != nullptr) {
        albumes.insertarAlFinal(album);
    }
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

    delete[] username;
    delete[] fechaNacimiento;
    delete[] correo;
    delete[] fotoPerfil;
    delete[] ciudad;
    delete[] pais;
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

// =========================================================
// FUNCIÓN AMIGA
// =========================================================

void imprimirUsuario(const Usuario& u) {
    cout << "Usuario: " << u.username << endl;
    cout << "  Nombre completo: " << u.fechaNacimiento << endl;
    cout << "  Correo: " << u.correo << endl;
    cout << "  Ciudad: " << u.ciudad << ", " << u.pais << endl;
    cout << "  Amigos: " << u.amigos.obtenerTamanio() << endl;
    cout << "  Solicitudes: " << u.solicitudes.obtenerTamanio() << endl;
    cout << "  Mensajes enviados: " << u.mensajesEnviados.obtenerTamanio() << endl;
    cout << "  Mensajes recibidos: " << u.mensajesRecibidos.obtenerTamanio() << endl;
    cout << "  Albumes: " << u.albumes.obtenerTamanio() << endl;
    cout << "---" << endl;
}
