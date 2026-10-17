#include "Plataforma.h"
#include "Mensaje.h"
#include "Album.h"
#include "Foto.h"
#include <iostream>
#include <fstream>

using namespace std;

int Plataforma::contadorIteraciones = 0;

// =========================================================
// GENERADOR PSEUDOALEATORIO PROPIO
// =========================================================

static unsigned long semillaPlataforma = 12345UL;

static int aleatorioPlataforma(int maximo) {
    semillaPlataforma = semillaPlataforma * 1103515245UL + 12345UL;
    unsigned long valor = (semillaPlataforma / 65536UL) % 32768UL;
    if (maximo <= 0) return 0;
    return (int)(valor % (unsigned long)maximo);
}

// =========================================================
// AUXILIAR DE PARSEO
// =========================================================

static int extraerCampo(const char* linea, int inicio, char delim,
                        char* destino, int maxTam) {
    if (linea == nullptr || destino == nullptr) return -1;
    int i = inicio, j = 0;
    while (linea[i] != '\0' && linea[i] != delim &&
           linea[i] != '\r' && linea[i] != '\n' && j < maxTam - 1) {
        destino[j] = linea[i]; i++; j++;
    }
    destino[j] = '\0';
    if (linea[i] == delim) i++;
    return i;
}

// =========================================================
// CONSTRUCTOR / DESTRUCTOR
// =========================================================

Plataforma::Plataforma() : memoriaConsumida(0) {}

Plataforma::~Plataforma() {
    listaUsuarios.vaciar();
    memoriaConsumida = 0;
    contadorIteraciones = 0;
}

// =========================================================
// CONTROL DE USUARIOS
// =========================================================

bool Plataforma::agregarUsuario(Usuario* nuevoUsuario) {
    if (nuevoUsuario == nullptr) return false;
    listaUsuarios.insertarAlFinal(nuevoUsuario);
    return true;
}

Usuario* Plataforma::buscarUsuarioPorUsername(const char* username) {
    if (username == nullptr) return nullptr;
    int tam = listaUsuarios.obtenerTamanio();
    for (int i = 0; i < tam; ++i) {
        registrarIteracion();
        Usuario* u = listaUsuarios[i];
        if (u != nullptr && compararCadenas(u->getUsername(), username)) return u;
    }
    return nullptr;
}

ListaLigada<Usuario*>& Plataforma::getListaUsuarios() { return listaUsuarios; }
int Plataforma::getCantidadUsuarios() const { return listaUsuarios.obtenerTamanio(); }

// =========================================================
// MÉTRICAS
// =========================================================

void Plataforma::reiniciarIteraciones() { contadorIteraciones = 0; }
void Plataforma::registrarIteracion(int cantidad) { contadorIteraciones += cantidad; }
int  Plataforma::getIteraciones() { return contadorIteraciones; }

void Plataforma::registrarMemoria(long bytes) { memoriaConsumida += bytes; }
void Plataforma::liberarMemoria(long bytes) {
    memoriaConsumida -= bytes;
    if (memoriaConsumida < 0) memoriaConsumida = 0;
}
long Plataforma::getMemoriaConsumida() const { return memoriaConsumida; }

void Plataforma::mostrarReporteMetricas(const char* nombre) const {
    cout << "\n============================================\n";
    cout << " [METRICAS - " << (nombre ? nombre : "OPERACION") << "]\n";
    cout << " -> Iteraciones: " << contadorIteraciones << "\n";
    cout << " -> Memoria:     " << memoriaConsumida << " Bytes\n";
    cout << "============================================\n\n";
}

// =========================================================
// AUXILIARES DE CADENAS
// =========================================================

int Plataforma::longitudCadena(const char* str) const {
    if (str == nullptr) return 0;
    int len = 0;
    while (str[len] != '\0') len++;
    return len;
}

bool Plataforma::compararCadenas(const char* a, const char* b) const {
    if (a == nullptr || b == nullptr) return a == b;
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0') {
        if (a[i] != b[i]) return false;
        i++;
    }
    return a[i] == b[i];
}

int Plataforma::cadenaAEntero(const char* str) const {
    if (str == nullptr) return 0;
    int num = 0, i = 0;
    bool neg = false;
    if (str[0] == '-') { neg = true; i = 1; }
    while (str[i] >= '0' && str[i] <= '9') { num = num * 10 + (str[i] - '0'); i++; }
    return neg ? -num : num;
}

static int compararCadenasEntero(const char* a, const char* b) {
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
// CARGA DE DATOS
// =========================================================

bool Plataforma::cargarDatosDesdeDisco(const char* rutaUsuarios,
                                       const char* rutaAmistades,
                                       const char* rutaSolicitudes,
                                       const char* rutaMensajes,
                                       const char* rutaAlbumes,
                                       const char* rutaFotos) {
    char linea[2048];

    // 1. USUARIOS
    if (rutaUsuarios != nullptr) {
        ifstream f(rutaUsuarios);
        if (!f.is_open()) { cout << "Error abriendo " << rutaUsuarios << "\n"; return false; }
        while (f.getline(linea, 2048)) {
            if (longitudCadena(linea) == 0 || linea[0] == '#') continue;
            char uName[128], fNac[64], email[128], foto[512];
            char ciud[128], pa[128], fIns[64];
            int pos = 0;
            pos = extraerCampo(linea, pos, ';', uName, 128);
            pos = extraerCampo(linea, pos, ';', fNac, 64);
            pos = extraerCampo(linea, pos, ';', email, 128);
            pos = extraerCampo(linea, pos, ';', foto, 512);
            pos = extraerCampo(linea, pos, ';', ciud, 128);
            pos = extraerCampo(linea, pos, ';', pa, 128);
            pos = extraerCampo(linea, pos, ';', fIns, 64);
            (void)pos;
            if (longitudCadena(uName) > 0 && buscarUsuarioPorUsername(uName) == nullptr) {
                Usuario* u = new Usuario(uName, fNac, email, foto, ciud, pa, fIns);
                agregarUsuario(u);
                registrarMemoria((long)u->calcularMemoriaBytes());
            }
        }
        f.close();
    }

    // 2. AMISTADES
    if (rutaAmistades != nullptr) {
        ifstream f(rutaAmistades);
        if (!f.is_open()) { cout << "Error abriendo " << rutaAmistades << "\n"; return false; }
        while (f.getline(linea, 2048)) {
            if (longitudCadena(linea) == 0 || linea[0] == '#') continue;
            char orig[128], dest[128];
            int pos = 0;
            pos = extraerCampo(linea, pos, ';', orig, 128);
            pos = extraerCampo(linea, pos, ';', dest, 128);
            (void)pos;
            Usuario* uo = buscarUsuarioPorUsername(orig);
            Usuario* ud = buscarUsuarioPorUsername(dest);
            if (uo && ud && !uo->esAmigo(ud) && !ud->esAmigo(uo)) {
                uo->getAmigos().insertarAlFinal(ud);
                ud->getAmigos().insertarAlFinal(uo);
            }
        }
        f.close();
    }

    // 3. SOLICITUDES
    if (rutaSolicitudes != nullptr) {
        ifstream f(rutaSolicitudes);
        if (!f.is_open()) { cout << "Error abriendo " << rutaSolicitudes << "\n"; return false; }
        while (f.getline(linea, 2048)) {
            if (longitudCadena(linea) == 0 || linea[0] == '#') continue;
            char orig[128], dest[128];
            int pos = 0;
            pos = extraerCampo(linea, pos, ';', orig, 128);
            pos = extraerCampo(linea, pos, ';', dest, 128);
            (void)pos;
            Usuario* uo = buscarUsuarioPorUsername(orig);
            Usuario* ud = buscarUsuarioPorUsername(dest);
            if (uo && ud && !ud->tieneSolicitudDe(uo)) {
                ud->getSolicitudes().insertarAlFinal(uo);
            }
        }
        f.close();
    }

    // 4. MENSAJES
    if (rutaMensajes != nullptr) {
        ifstream f(rutaMensajes);
        if (!f.is_open()) { cout << "Error abriendo " << rutaMensajes << "\n"; return false; }
        while (f.getline(linea, 2048)) {
            if (longitudCadena(linea) == 0 || linea[0] == '#') continue;
            char emi[128], rec[128], fec[64], leidoStr[8], txt[1024];
            int pos = 0;
            pos = extraerCampo(linea, pos, ';', emi, 128);
            pos = extraerCampo(linea, pos, ';', rec, 128);
            pos = extraerCampo(linea, pos, ';', fec, 64);
            pos = extraerCampo(linea, pos, ';', leidoStr, 8);
            pos = extraerCampo(linea, pos, ';', txt, 1024);
            (void)pos;
            Usuario* ue = buscarUsuarioPorUsername(emi);
            Usuario* ur = buscarUsuarioPorUsername(rec);
            if (ue && ur) {
                Mensaje* m = new Mensaje(txt, fec, ue, ur);
                if (leidoStr[0] == '1') m->marcarComoLeido();
                ue->getMensajesEnviados().insertarAlFinal(m);
                ur->getMensajesRecibidos().insertarAlFinal(m);
            }
        }
        f.close();
    }

    // 5. ALBUMES
    if (rutaAlbumes != nullptr) {
        ifstream f(rutaAlbumes);
        if (!f.is_open()) { cout << "Error abriendo " << rutaAlbumes << "\n"; return false; }
        while (f.getline(linea, 2048)) {
            if (longitudCadena(linea) == 0 || linea[0] == '#') continue;
            char prop[128], nomAlb[128], priv[8], ruta[512];
            int pos = 0;
            pos = extraerCampo(linea, pos, ';', prop, 128);
            pos = extraerCampo(linea, pos, ';', nomAlb, 128);
            pos = extraerCampo(linea, pos, ';', priv, 8);
            pos = extraerCampo(linea, pos, ';', ruta, 512);
            (void)pos;
            Usuario* up = buscarUsuarioPorUsername(prop);
            if (up) {
                char p = (priv[0] != '\0') ? priv[0] : 'P';
                Album* alb = new Album(nomAlb, ruta, p);
                up->agregarAlbum(alb);
                registrarMemoria((long)alb->obtenerMemoriaConsumida());
            }
        }
        f.close();
    }

    // 6. FOTOS
    if (rutaFotos != nullptr) {
        ifstream f(rutaFotos);
        if (!f.is_open()) { cout << "Error abriendo " << rutaFotos << "\n"; return false; }
        while (f.getline(linea, 2048)) {
            if (longitudCadena(linea) == 0 || linea[0] == '#') continue;
            char prop[128], nomAlb[128], rutaF[512], fec[64];
            char tamStr[32], likeStr[32];
            int pos = 0;
            pos = extraerCampo(linea, pos, ';', prop, 128);
            pos = extraerCampo(linea, pos, ';', nomAlb, 128);
            pos = extraerCampo(linea, pos, ';', rutaF, 512);
            pos = extraerCampo(linea, pos, ';', fec, 64);
            pos = extraerCampo(linea, pos, ';', tamStr, 32);
            pos = extraerCampo(linea, pos, ';', likeStr, 32);
            (void)pos;
            Usuario* up = buscarUsuarioPorUsername(prop);
            if (up) {
                Album* alb = nullptr;
                for (int i = 0; i < up->getAlbumes().obtenerTamanio(); ++i) {
                    if (compararCadenas(up->getAlbumes()[i]->getNombre(), nomAlb)) {
                        alb = up->getAlbumes()[i];
                        break;
                    }
                }
                if (alb) {
                    Foto* nf = new Foto(fec, rutaF,
                                        (long)cadenaAEntero(tamStr),
                                        cadenaAEntero(likeStr), alb);
                    alb->agregarFoto(nf);
                    registrarMemoria((long)nf->obtenerMemoriaConsumida());
                }
            }
        }
        f.close();
    }

    return true;
}

// =========================================================
// GUARDADO DE DATOS
// =========================================================

bool Plataforma::guardarDatosADisco(const char* rutaUsuarios,
                                    const char* rutaAmistades,
                                    const char* rutaSolicitudes,
                                    const char* rutaMensajes,
                                    const char* rutaAlbumes,
                                    const char* rutaFotos) const {
    // 1. USUARIOS
    if (rutaUsuarios != nullptr) {
        ofstream f(rutaUsuarios);
        if (!f.is_open()) return false;
        for (int i = 0; i < listaUsuarios.obtenerTamanio(); ++i) {
            Usuario* u = listaUsuarios[i];
            if (u == nullptr) continue;
            f << u->getUsername() << ";"
              << u->getFechaNacimiento() << ";"
              << u->getCorreo() << ";"
              << u->getFotoPerfil() << ";"
              << u->getCiudad() << ";"
              << u->getPais() << ";"
              << u->getFechaInscripcion() << "\n";
        }
        f.close();
    }

    // 2. AMISTADES
    if (rutaAmistades != nullptr) {
        ofstream f(rutaAmistades);
        if (!f.is_open()) return false;
        for (int i = 0; i < listaUsuarios.obtenerTamanio(); ++i) {
            Usuario* u = listaUsuarios[i];
            if (u == nullptr) continue;
            for (int j = 0; j < u->getAmigos().obtenerTamanio(); ++j) {
                Usuario* am = u->getAmigos()[j];
                if (compararCadenasEntero(u->getUsername(), am->getUsername()) < 0) {
                    f << u->getUsername() << ";" << am->getUsername() << "\n";
                }
            }
        }
        f.close();
    }

    // 3. SOLICITUDES
    if (rutaSolicitudes != nullptr) {
        ofstream f(rutaSolicitudes);
        if (!f.is_open()) return false;
        for (int i = 0; i < listaUsuarios.obtenerTamanio(); ++i) {
            Usuario* u = listaUsuarios[i];
            if (u == nullptr) continue;
            for (int j = 0; j < u->getSolicitudes().obtenerTamanio(); ++j) {
                f << u->getSolicitudes()[j]->getUsername() << ";"
                  << u->getUsername() << "\n";
            }
        }
        f.close();
    }

    // 4. MENSAJES
    if (rutaMensajes != nullptr) {
        ofstream f(rutaMensajes);
        if (!f.is_open()) return false;
        for (int i = 0; i < listaUsuarios.obtenerTamanio(); ++i) {
            Usuario* u = listaUsuarios[i];
            if (u == nullptr) continue;
            for (int j = 0; j < u->getMensajesEnviados().obtenerTamanio(); ++j) {
                Mensaje* m = u->getMensajesEnviados()[j];
                if (m == nullptr) continue;
                f << m->getEmisor()->getUsername() << ";"
                  << m->getReceptor()->getUsername() << ";"
                  << m->getFechaEnvio() << ";"
                  << (m->getLeido() ? "1" : "0") << ";"
                  << m->getTexto() << "\n";
            }
        }
        f.close();
    }

    // 5. ALBUMES
    if (rutaAlbumes != nullptr) {
        ofstream f(rutaAlbumes);
        if (!f.is_open()) return false;
        for (int i = 0; i < listaUsuarios.obtenerTamanio(); ++i) {
            Usuario* u = listaUsuarios[i];
            if (u == nullptr) continue;
            for (int j = 0; j < u->getAlbumes().obtenerTamanio(); ++j) {
                Album* a = u->getAlbumes()[j];
                if (a == nullptr) continue;
                f << u->getUsername() << ";"
                  << a->getNombre() << ";"
                  << a->getPrivacidad() << ";"
                  << a->getRutaAlmacenamiento() << "\n";
            }
        }
        f.close();
    }

    // 6. FOTOS
    if (rutaFotos != nullptr) {
        ofstream f(rutaFotos);
        if (!f.is_open()) return false;
        for (int i = 0; i < listaUsuarios.obtenerTamanio(); ++i) {
            Usuario* u = listaUsuarios[i];
            if (u == nullptr) continue;
            for (int j = 0; j < u->getAlbumes().obtenerTamanio(); ++j) {
                Album* a = u->getAlbumes()[j];
                if (a == nullptr) continue;
                for (int k = 0; k < a->getFotos().obtenerTamanio(); ++k) {
                    Foto* fo = a->getFotos()[k];
                    if (fo == nullptr) continue;
                    f << u->getUsername() << ";"
                      << a->getNombre() << ";"
                      << fo->getRutaArchivo() << ";"
                      << fo->getFechaCaptura() << ";"
                      << fo->getTamanioBytes() << ";"
                      << fo->getLikes() << "\n";
                }
            }
        }
        f.close();
    }

    return true;
}

// =========================================================
// FUNCIONALIDAD — CARRUSEL
// =========================================================

void Plataforma::recorrerCarrusel(Usuario* visitante, Album* album) {
    if (visitante == nullptr || album == nullptr) return;
    ListaLigada<Foto*>& fotos = album->getFotos();
    int n = fotos.obtenerTamanio();
    if (n == 0) { cout << "El album esta vacio.\n"; return; }

    int idx = 0;
    char opcion = ' ';
    while (opcion != 'e' && opcion != 'E') {
        registrarIteracion();
        Foto* f = fotos[idx];
        cout << "\n========================================\n";
        cout << " Album: " << album->getNombre() << "\n";
        cout << " Foto  [" << (idx + 1) << "/" << n << "]\n";
        cout << " Ruta:  " << f->getRutaArchivo() << "\n";
        cout << " Fecha: " << f->getFechaCaptura() << "\n";
        cout << " Likes: " << f->getLikes() << "\n";
        cout << "========================================\n";
        cout << " [s]iguiente  [p]revia  [l]ike  [q]uitar like  [e]sc salir: ";
        cin >> opcion;

        if (opcion == 's' || opcion == 'S') idx = (idx + 1) % n;
        else if (opcion == 'p' || opcion == 'P') idx = (idx - 1 + n) % n;
        else if (opcion == 'l' || opcion == 'L') { f->darQuitarLike(true); cout << " Like agregado. Total: " << f->getLikes() << "\n"; }
        else if (opcion == 'q' || opcion == 'Q') { f->darQuitarLike(false); cout << " Like quitado. Total: " << f->getLikes() << "\n"; }
    }
}

// =========================================================
// FUNCIONALIDAD — MEJORES AMIGOS
// =========================================================

void Plataforma::mostrarMejoresAmigos(Usuario* usuarioActual) {
    if (usuarioActual == nullptr) return;
    ListaLigada<Usuario*>& amigos = usuarioActual->getAmigos();
    int n = amigos.obtenerTamanio();
    if (n == 0) { cout << "No tienes amigos registrados.\n"; return; }
    cout << "\n--- Mejores amigos de " << usuarioActual->getUsername() << " ---\n";
    int mostrados = 0;
    int intentos = 0;
    int maxMostrar = (n < 3) ? n : 3;
    while (mostrados < maxMostrar && intentos < n * 3) {
        registrarIteracion();
        int idx = aleatorioPlataforma(n);
        Usuario* amigo = amigos[idx];
        if (amigo != nullptr) {
            cout << "  [" << (mostrados + 1) << "] "
                 << amigo->getUsername() << "\n"
                 << "      Foto: " << amigo->getFotoPerfil() << "\n";
            mostrados++;
        }
        intentos++;
    }
}

// =========================================================
// FUNCIONALIDAD — SUGERENCIAS
// =========================================================

void Plataforma::verSugerenciasDeAmistad(Usuario* usuarioActual, int k) {
    if (usuarioActual == nullptr) return;
    usuarioActual->verSugerencias(k);
}

// =========================================================
// FUNCIONALIDAD — BUSCAR MENSAJES
// =========================================================

void Plataforma::buscarMensajesPorFecha(Usuario* usuarioActual,
                                        const char* inicio, const char* fin) {
    if (usuarioActual == nullptr) return;
    usuarioActual->buscarMensajes(inicio, fin);
}