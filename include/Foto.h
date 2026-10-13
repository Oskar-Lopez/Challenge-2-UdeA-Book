#ifndef FOTO_H
#define FOTO_H

class Album;

class Foto {
private:
    char* fechaCaptura; // Fecha "YYYY-MM-DD"
    char* rutaArchivo;
    long tamanioBytes;
    int likes;
    Album* albumPadre;

    // Métodos auxiliares privados para manejo seguro de char*
    static int longitudCadena(const char* cadena);
    static void copiarCadena(char* destino, const char* origen);
    static bool compararCadenas(const char* a, const char* b);

public:
    // Constructores y Destructor
    Foto();
    Foto(const char* fechaCaptura, const char* rutaArchivo, long tamanioBytes, int likes = 0, Album* albumPadre = nullptr);
    Foto(const Foto& otra);
    ~Foto();

    // Getters y Setters
    const char* getFechaCaptura() const;
    void setFechaCaptura(const char* fecha);

    const char* getRutaArchivo() const;
    void setRutaArchivo(const char* ruta);

    long getTamanioBytes() const;
    void setTamanioBytes(long tamanio);

    int getLikes() const;
    void setLikes(int likes);

    Album* getAlbumPadre() const;
    void setAlbumPadre(Album* album);

    // Métodos de negocio
    void darQuitarLike(bool incrementar);
    unsigned long obtenerMemoriaConsumida() const;

    // Sobrecarga de operadores
    Foto& operator=(const Foto& otra);
    bool operator==(const Foto& otra) const;
};

#endif
