#include <iostream>

enum Genero {
    MASCULINO = 2,
    FEMININO = 4
};

Genero parseInt(int codigo) {
    if (codigo == MASCULINO)
        return MASCULINO;
    else if (codigo == FEMININO)
        return FEMININO;
    return static_cast<Genero>(0); // Retornando um valor padrão (pode ser ajustado conforme necessário)
}

int getInt(Genero genero) {
    return static_cast<int>(genero);
}