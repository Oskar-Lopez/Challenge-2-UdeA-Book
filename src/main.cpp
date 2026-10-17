#include <iostream>
#include "Plataforma.h"
#include "Usuario.h"
#include "Mensaje.h"
#include "Album.h"
#include "Foto.h"

using namespace std;

// =========================================================
// MENÚ PRINCIPAL
// =========================================================

void mostrarMenuPrincipal(Usuario* u) {
    cout << "\n=================================================\n";
    cout << "        Bienvenido a Ude@Book, " << u->getUsername() << "\n";
    cout << "=================================================\n";
    cout << " 1. Administrar amistades\n";
    cout << " 2. Visitar perfil de un amigo\n";
    cout << " 3. Ver sugerencias de amistad\n";
    cout << " 4. Administrar mensajes\n";
    cout << " 5. Ver mis mejores amigos (3 fotos)\n";
    cout << " 0. Cerrar sesion\n";
    cout << "=================================================\n";
    cout << " Su opcion: ";
}

// =========================================================
// SUBMENÚ: AMISTADES
// =========================================================

void menuAmistades(Usuario* u, Plataforma& plataforma) {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n--- Administrar amistades ---\n";
        cout << " 1. Enviar solicitud de amistad\n";
        cout << " 2. Aceptar solicitud recibida\n";
        cout << " 3. Ver solicitudes pendientes\n";
        cout << " 0. Volver\n";
        cout << " Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            char usernameDestino[128];
            cout << " Username del destinatario: ";
            cin >> usernameDestino;
            Plataforma::reiniciarIteraciones();
            Usuario* destino = plataforma.buscarUsuarioPorUsername(usernameDestino);
            if (destino == nullptr) {
                cout << " Usuario no encontrado.\n";
            } else {
                u->enviarSolicitud(destino);
            }
            plataforma.mostrarReporteMetricas("ENVIAR SOLICITUD");
        }
        else if (opcion == 2) {
            char usernameOrigen[128];
            cout << " Username del remitente: ";
            cin >> usernameOrigen;
            Plataforma::reiniciarIteraciones();
            Usuario* origen = plataforma.buscarUsuarioPorUsername(usernameOrigen);
            if (origen == nullptr) {
                cout << " Usuario no encontrado.\n";
            } else {
                u->aceptarSolicitud(origen);
            }
            plataforma.mostrarReporteMetricas("ACEPTAR SOLICITUD");
        }
        else if (opcion == 3) {
            cout << " Solicitudes pendientes:\n";
            ListaLigada<Usuario*>& sol = u->getSolicitudes();
            for (int i = 0; i < sol.obtenerTamanio(); ++i) {
                cout << "  - " << sol[i]->getUsername() << "\n";
            }
        }
    }
}

// =========================================================
// SUBMENÚ: MENSAJES
// =========================================================

void menuMensajes(Usuario* u, Plataforma& plataforma) {
    int opcion = -1;
    while (opcion != 0) {
        cout << "\n--- Administrar mensajes ---\n";
        cout << " 1. Enviar mensaje\n";
        cout << " 2. Leer mensajes no leidos\n";
        cout << " 3. Buscar mensajes por rango de fecha\n";
        cout << " 0. Volver\n";
        cout << " Opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            char destino[128], texto[512], fecha[64];
            cout << " Username del amigo: ";
            cin >> destino;
            cin.ignore();
            cout << " Texto (max 512): ";
            cin.getline(texto, 512);
            cout << " Fecha (YYYY-MM-DD HH:MM): ";
            cin.getline(fecha, 64);
            Plataforma::reiniciarIteraciones();
            Usuario* d = plataforma.buscarUsuarioPorUsername(destino);
            if (d == nullptr) {
                cout << " Usuario no encontrado.\n";
            } else {
                u->enviarMensaje(d, texto, fecha);
            }
            plataforma.mostrarReporteMetricas("ENVIAR MENSAJE");
        }
        else if (opcion == 2) {
            ListaLigada<Mensaje*>& rec = u->getMensajesRecibidos();
            cout << "\n--- Mensajes no leidos ---\n";
            int contador = 0;
            for (int i = 0; i < rec.obtenerTamanio(); ++i) {
                Mensaje* m = rec[i];
                if (!m->getLeido()) {
                    cout << " De: " << m->getEmisor()->getUsername()
                    << " [" << m->getFechaEnvio() << "]\n"
                    << "   " << m->getTexto() << "\n";
                    m->marcarComoLeido();
                    contador++;
                }
            }
            if (contador == 0) cout << " No hay mensajes nuevos.\n";
        }
        else if (opcion == 3) {
            char inicio[64], fin[64];
            cin.ignore();
            cout << " Fecha inicio (YYYY-MM-DD HH:MM): ";
            cin.getline(inicio, 64);
            cout << " Fecha fin    (YYYY-MM-DD HH:MM): ";
            cin.getline(fin, 64);
            Plataforma::reiniciarIteraciones();
            plataforma.buscarMensajesPorFecha(u, inicio, fin);
            plataforma.mostrarReporteMetricas("BUSCAR MENSAJES");
        }
    }
}

// =========================================================
// SUBMENÚ: VISITAR PERFIL
// =========================================================

void menuVisitarPerfil(Usuario* u, Plataforma& plataforma) {
    char username[128];
    cout << " Username del amigo a visitar: ";
    cin >> username;
    Plataforma::reiniciarIteraciones();
    Usuario* amigo = plataforma.buscarUsuarioPorUsername(username);
    if (amigo == nullptr || !u->esAmigo(amigo)) {
        cout << " No es tu amigo o no existe.\n";
        return;
    }
    cout << "\n--- Perfil de " << amigo->getUsername() << " ---\n";
    cout << " Ciudad: " << amigo->getCiudad() << ", " << amigo->getPais() << "\n";
    cout << " Correo: " << amigo->getCorreo() << "\n";

    ListaLigada<Album*>& albums = amigo->getAlbumes();
    int visibles = 0;
    cout << "\n Albumes visibles:\n";
    for (int i = 0; i < albums.obtenerTamanio(); ++i) {
        if (albums[i]->esVisibleParaAmigos()) {
            cout << "  [" << (visibles + 1) << "] " << albums[i]->getNombre()
            << " (" << albums[i]->getFotos().obtenerTamanio() << " fotos)\n";
            visibles++;
        }
    }

    if (visibles == 0) {
        cout << " No hay albumes visibles.\n";
        plataforma.mostrarReporteMetricas("VISITAR PERFIL");
        return;
    }

    int seleccion;
    cout << " Selecciona el album (numero) o 0 para salir: ";
    cin >> seleccion;
    if (seleccion < 1 || seleccion > visibles) {
        plataforma.mostrarReporteMetricas("VISITAR PERFIL");
        return;
    }

    int contador = 0;
    Album* elegido = nullptr;
    for (int i = 0; i < albums.obtenerTamanio(); ++i) {
        if (albums[i]->esVisibleParaAmigos()) {
            contador++;
            if (contador == seleccion) { elegido = albums[i]; break; }
        }
    }

    if (elegido != nullptr) {
        plataforma.recorrerCarrusel(u, elegido);
    }

    plataforma.mostrarReporteMetricas("VISITAR PERFIL");
}

// =========================================================
// MAIN
// =========================================================

int main() {
    cout << "===== UDE@BOOK - RED SOCIAL =====\n\n";

    Plataforma plataforma;

    // Rutas relativas (requiere que Working Directory sea %{sourceDir})
    bool ok = plataforma.cargarDatosDesdeDisco(
        "data/usuarios.txt",
        "data/amistades.txt",
        "data/solicitudes.txt",
        "data/mensajes.txt",
        "data/albumes.txt",
        "data/fotos.txt"
        );

    if (!ok) {
        cout << "Error al cargar los datos. Verifica la carpeta data/.\n";
        return 1;
    }

    cout << "Usuarios cargados: " << plataforma.getCantidadUsuarios() << "\n";
    cout << "Memoria consumida: " << plataforma.getMemoriaConsumida() << " Bytes\n\n";

    char usernameLogin[128];
    cout << " Ingresa tu username para iniciar sesion: ";
    cin >> usernameLogin;

    Usuario* usuarioActual = plataforma.buscarUsuarioPorUsername(usernameLogin);
    if (usuarioActual == nullptr) {
        cout << " Usuario no encontrado. Saliendo.\n";
        return 1;
    }

    int opcion = -1;
    while (opcion != 0) {
        mostrarMenuPrincipal(usuarioActual);
        cin >> opcion;

        if (opcion == 1) {
            menuAmistades(usuarioActual, plataforma);
        }
        else if (opcion == 2) {
            menuVisitarPerfil(usuarioActual, plataforma);
        }
        else if (opcion == 3) {
            int k;
            cout << " Cuantas sugerencias (1-20)? ";
            cin >> k;
            Plataforma::reiniciarIteraciones();
            plataforma.verSugerenciasDeAmistad(usuarioActual, k);
            plataforma.mostrarReporteMetricas("SUGERENCIAS");
        }
        else if (opcion == 4) {
            menuMensajes(usuarioActual, plataforma);
        }
        else if (opcion == 5) {
            Plataforma::reiniciarIteraciones();
            plataforma.mostrarMejoresAmigos(usuarioActual);
            plataforma.mostrarReporteMetricas("MEJORES AMIGOS");
        }
        else if (opcion == 0) {
            cout << " Cerrando sesion...\n";
            bool guardado = plataforma.guardarDatosADisco(
                "data/usuarios.txt",
                "data/amistades.txt",
                "data/solicitudes.txt",
                "data/mensajes.txt",
                "data/albumes.txt",
                "data/fotos.txt"
                );
            if (guardado) {
                cout << " Datos guardados correctamente.\n";
            } else {
                cout << " Error al guardar los datos.\n";
            }
        }
        else {
            cout << " Opcion no valida.\n";
        }
    }

    cout << "\n===== Gracias por utilizar Ude@Book =====\n";
    return 0;
}