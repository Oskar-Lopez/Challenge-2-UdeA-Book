#ifndef ALBUM_H
#define ALBUM_H

#include "ListaLigada.h"
#include "Foto.h"

class Album {
private:
    char* nombre;
    char* rutaAlmacenamiento;
    char privacidad;         // 'P': Público, 'V': Privado, 'A': Amigos
    ListaLigada<Foto*> fotos;

    static int longitudCadena(const char* cadena);
    static void copiarCadena(char* destino, const char* origen);
    static bool compararCadenas(const char* a, const char* b);

    void liberarFotos();     // Helper para liberar todas las fotos

public:
    Album();
    Album(const char* nombre, const char* ruta, char privacidad = 'P');
    Album(const Album& otro);
    ~Album();

    const char* getNombre() const;
    void setNombre(const char* nombre);

    const char* getRutaAlmacenamiento() const;
    void setRutaAlmacenamiento(const char* ruta);

    char getPrivacidad() const;
    void setPrivacidad(char privacidad);

    ListaLigada<Foto*>& getFotos();
    const ListaLigada<Foto*>& getFotos() const;

    void agregarFoto(Foto* f);
    bool esVisibleParaAmigos() const;
    unsigned long obtenerMemoriaConsumida() const;

    Album& operator=(const Album& otro);
    bool operator==(const Album& otro) const;
};

#endif
