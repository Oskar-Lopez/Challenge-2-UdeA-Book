#ifndef USUARIO_H
#define USUARIO_H

#include "ListaLigada.h"

class Mensaje;
class Album;

class Usuario {
private:
    char* username;
    char* fechaNacimiento;
    char* correo;
    char* fotoPerfil;
    char* ciudad;
    char* pais;
    char* fechaInscripcion;

    ListaLigada<Usuario*> amigos;
    ListaLigada<Usuario*> solicitudes;
    ListaLigada<Mensaje*> mensajesEnviados;
    ListaLigada<Mensaje*> mensajesRecibidos;
    ListaLigada<Album*> albumes;

    static int longitudCadena(const char* cadena);
    static void copiarCadena(char* destino, const char* origen);
    static bool compararCadenas(const char* a, const char* b);
    static int compararFechas(const char* a, const char* b);

public:
    Usuario();
    Usuario(const char* username, const char* fechaNacimiento, const char* correo,
            const char* fotoPerfil, const char* ciudad, const char* pais,
            const char* fechaInscripcion);
    Usuario(const Usuario& otro);
    ~Usuario();

    const char* getUsername() const;         void setUsername(const char* username);
    const char* getFechaNacimiento() const;  void setFechaNacimiento(const char* fecha);
    const char* getCorreo() const;           void setCorreo(const char* correo);
    const char* getFotoPerfil() const;       void setFotoPerfil(const char* foto);
    const char* getCiudad() const;           void setCiudad(const char* ciudad);
    const char* getPais() const;             void setPais(const char* pais);
    const char* getFechaInscripcion() const; void setFechaInscripcion(const char* fecha);

    ListaLigada<Usuario*>& getAmigos();
    ListaLigada<Usuario*>& getSolicitudes();
    ListaLigada<Mensaje*>& getMensajesEnviados();
    ListaLigada<Mensaje*>& getMensajesRecibidos();
    ListaLigada<Album*>& getAlbumes();

    const ListaLigada<Usuario*>& getAmigos() const;
    const ListaLigada<Usuario*>& getSolicitudes() const;
    const ListaLigada<Mensaje*>& getMensajesEnviados() const;
    const ListaLigada<Mensaje*>& getMensajesRecibidos() const;
    const ListaLigada<Album*>& getAlbumes() const;

    void enviarSolicitud(Usuario* destino);
    void aceptarSolicitud(Usuario* origen);
    void verSugerencias(int k) const;
    void enviarMensaje(Usuario* amigo, const char* texto, const char* fecha);
    void buscarMensajes(const char* inicio, const char* fin) const;

    bool esAmigo(const Usuario* otro) const;
    bool tieneSolicitudDe(const Usuario* otro) const;
    void agregarAlbum(Album* album);

    unsigned long calcularMemoriaBytes() const;

    bool operator==(const Usuario& otro) const;
    bool operator!=(const Usuario& otro) const;
    Usuario& operator=(const Usuario& otro);

    friend void imprimirUsuario(const Usuario& u);
};

#endif
