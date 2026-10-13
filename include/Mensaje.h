#ifndef MENSAJE_H
#define MENSAJE_H

class Usuario;  // Forward declaration

class Mensaje {
private:
    char* texto;              // Cuerpo del mensaje (máx. 512)
    char* fechaEnvio;         // Fecha "YYYY-MM-DD HH:MM"
    bool leido;
    Usuario* emisor;
    Usuario* receptor;

    // Métodos auxiliares privados para manejo de char*
    static int longitudCadena(const char* cadena);
    static void copiarCadena(char* destino, const char* origen);
    static bool compararCadenas(const char* a, const char* b);

public:
    // Constructores y destructor
    Mensaje();
    Mensaje(const char* texto, const char* fecha,
            Usuario* emisor, Usuario* receptor);
    Mensaje(const Mensaje& otro);
    ~Mensaje();

    // Getters y setters
    const char* getTexto() const;
    void setTexto(const char* texto);

    const char* getFechaEnvio() const;
    void setFechaEnvio(const char* fecha);

    bool getLeido() const;
    void setLeido(bool leido);

    Usuario* getEmisor() const;
    void setEmisor(Usuario* emisor);

    Usuario* getReceptor() const;
    void setReceptor(Usuario* receptor);

    // Métodos de negocio
    void marcarComoLeido();
    void marcarComoNoLeido();
    int obtenerLongitudTexto() const;

    // Sobrecarga de operadores
    bool operator==(const Mensaje& otro) const;
    Mensaje& operator=(const Mensaje& otro);

    // Función amiga
    friend void imprimirMensaje(const Mensaje& m);
};

#endif
