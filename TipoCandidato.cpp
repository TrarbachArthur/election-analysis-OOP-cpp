#include <iostream>

enum TipoCandidato {
    OUTRO = 0,
    FEDERAL = 6,
    ESTADUAL = 7
};

class Util {
public:
    static TipoCandidato parseInt(int codigo) {
        if (codigo == FEDERAL)
            return FEDERAL;
        else if (codigo == ESTADUAL)
            return ESTADUAL;
        return OUTRO;
    }

    int getInt() const {
        return valor;
    }

private:
    Util(int valor) : valor(valor) {}

    int valor;
};