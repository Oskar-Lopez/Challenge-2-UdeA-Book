#ifndef ALBUM_H
#define ALBUM_H

#include "ListaLigada.h"
#include "Foto.h"

class Album {
private:
    char* nombre;
    char* rutaAlmacenamiento;
    char privacidad;          // 'P': Público, 'V': Privado, 'A': Amigos
    ListaLigada<Foto*> fotos;

    // Métodos auxiliares privados para cadenas
    static int longitudCadena(const char* cadena);
    static void copiarCadena(char* destino, const char* origen);
    static bool compararCadenas(const char* a, const char* b);

public:
    // Constructores y Destructor
    Album();
    Album(const char* nombre, const char* ruta, char privacidad = 'P');
    Album(const Album& otro);
    ~Album();

    // Getters y Setters
    const char* getNombre() const;
    void setNombre(const char* nombre);

    const char* getRutaAlmacenamiento() const;
    void setRutaAlmacenamiento(const char* ruta);

    char getPrivacidad() const;
    void setPrivacidad(char privacidad);

    ListaLigada<Foto*>& getFotos();
    const ListaLigada<Foto*>& getFotos() const;

    // Métodos de negocio
    void agregarFoto(Foto* f);
    bool esVisibleParaAmigos() const;
    unsigned long obtenerMemoriaConsumida() const; // Requisito VII

    // Sobrecarga de operadores
    Album& operator=(const Album& otro);
    bool operator==(const Album& otro) const;
};

#endif
