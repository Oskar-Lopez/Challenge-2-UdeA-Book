#ifndef USUARIO_H
#define USUARIO_H

#include "ListaLigada.h"

// Forward declarations (evita inclusiones circulares)
class Mensaje;
class Album;

class Usuario {
private:
    // Cadenas dinámicas nativas en char*
    char* username;
    char* fechaNacimiento;
    char* correo;
    char* fotoPerfil;
    char* ciudad;
    char* pais;
    char* fechaInscripcion;

    // Listas genéricas propias
    ListaLigada<Usuario*> amigos;
    ListaLigada<Usuario*> solicitudes;
    ListaLigada<Mensaje*> mensajesEnviados;
    ListaLigada<Mensaje*> mensajesRecibidos;
    ListaLigada<Album*> albumes;

    // Métodos auxiliares estáticos para manipulación manual de cadenas
    static int longitudCadena(const char* cadena);
    static void copiarCadena(char* destino, const char* origen);
    static bool compararCadenas(const char* a, const char* b);
    static int compararFechas(const char* a, const char* b);

public:
    // Constructores y Destructor
    Usuario();
    Usuario(const char* username, const char* fechaNacimiento, const char* correo,
            const char* fotoPerfil, const char* ciudad, const char* pais,
            const char* fechaInscripcion);
    Usuario(const Usuario& otro);
    ~Usuario();

    // Getters y Setters
    const char* getUsername() const;
    void setUsername(const char* username);

    const char* getFechaNacimiento() const;
    void setFechaNacimiento(const char* fecha);

    const char* getCorreo() const;
    void setCorreo(const char* correo);

    const char* getFotoPerfil() const;
    void setFotoPerfil(const char* foto);

    const char* getCiudad() const;
    void setCiudad(const char* ciudad);

    const char* getPais() const;
    void setPais(const char* pais);

    const char* getFechaInscripcion() const;
    void setFechaInscripcion(const char* fecha);

    // Acceso a listas por referencia
    ListaLigada<Usuario*>& getAmigos();
    ListaLigada<Usuario*>& getSolicitudes();
    ListaLigada<Mensaje*>& getMensajesEnviados();
    ListaLigada<Mensaje*>& getMensajesRecibidos();
    ListaLigada<Album*>& getAlbumes();

    // Versiones const (para métodos const como verSugerencias)
    const ListaLigada<Usuario*>& getAmigos() const;
    const ListaLigada<Usuario*>& getSolicitudes() const;
    const ListaLigada<Mensaje*>& getMensajesEnviados() const;
    const ListaLigada<Mensaje*>& getMensajesRecibidos() const;
    const ListaLigada<Album*>& getAlbumes() const;

    // Métodos de negocio según el diagrama UML
    void enviarSolicitud(Usuario* destino);
    void aceptarSolicitud(Usuario* origen);
    void verSugerencias(int k) const;
    void enviarMensaje(Usuario* amigo, const char* texto, const char* fecha);
    void buscarMensajes(const char* inicio, const char* fin) const;

    // Métodos auxiliares de relación
    bool esAmigo(const Usuario* otro) const;
    bool tieneSolicitudDe(const Usuario* otro) const;
    void agregarAlbum(Album* album);

    // Sobrecarga de operadores
    bool operator==(const Usuario& otro) const;
    bool operator!=(const Usuario& otro) const;
    Usuario& operator=(const Usuario& otro);

    // Función amiga
    friend void imprimirUsuario(const Usuario& u);
};

#endif
