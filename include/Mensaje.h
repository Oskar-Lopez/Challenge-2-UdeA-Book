#ifndef MENSAJE_H
#define MENSAJE_H

class Usuario;

class Mensaje {
private:
    char* texto;
    char* fechaEnvio;
    bool leido;
    Usuario* emisor;
    Usuario* receptor;

    static int longitudCadena(const char* cadena);
    static void copiarCadena(char* destino, const char* origen);
    static bool compararCadenas(const char* a, const char* b);

public:
    Mensaje();
    Mensaje(const char* texto, const char* fecha,
            Usuario* emisor, Usuario* receptor);
    Mensaje(const Mensaje& otro);
    ~Mensaje();

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

    void marcarComoLeido();
    void marcarComoNoLeido();
    int obtenerLongitudTexto() const;

    bool operator==(const Mensaje& otro) const;
    Mensaje& operator=(const Mensaje& otro);

    friend void imprimirMensaje(const Mensaje& m);
};

#endif
