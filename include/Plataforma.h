#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "ListaLigada.h"
#include "Usuario.h"

class Album;

class Plataforma {
private:
    ListaLigada<Usuario*> listaUsuarios;
    static int contadorIteraciones;
    long memoriaConsumida;

    bool compararCadenas(const char* a, const char* b) const;
    int  cadenaAEntero(const char* str) const;
    int  longitudCadena(const char* str) const;

public:
    Plataforma();
    ~Plataforma();

    bool agregarUsuario(Usuario* nuevoUsuario);
    Usuario* buscarUsuarioPorUsername(const char* username);
    ListaLigada<Usuario*>& getListaUsuarios();
    int getCantidadUsuarios() const;

    bool cargarDatosDesdeDisco(const char* rutaUsuarios,
                               const char* rutaAmistades,
                               const char* rutaSolicitudes,
                               const char* rutaMensajes,
                               const char* rutaAlbumes,
                               const char* rutaFotos);

    bool guardarDatosADisco(const char* rutaUsuarios,
                            const char* rutaAmistades,
                            const char* rutaSolicitudes,
                            const char* rutaMensajes,
                            const char* rutaAlbumes,
                            const char* rutaFotos) const;

    static void reiniciarIteraciones();
    static void registrarIteracion(int cantidad = 1);
    static int  getIteraciones();

    void registrarMemoria(long bytes);
    void liberarMemoria(long bytes);
    long getMemoriaConsumida() const;

    void mostrarReporteMetricas(const char* nombreFuncionalidad) const;

    void recorrerCarrusel(Usuario* visitante, Album* album);
    void mostrarMejoresAmigos(Usuario* usuarioActual);
    void verSugerenciasDeAmistad(Usuario* usuarioActual, int k);
    void buscarMensajesPorFecha(Usuario* usuarioActual,
                                const char* inicio, const char* fin);
};

#endif
