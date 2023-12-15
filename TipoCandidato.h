#ifndef UTIL_H
#define UTIL_H

#include <iostream>

enum TipoCandidato {
    OUTRO = 0,
    FEDERAL = 6,
    ESTADUAL = 7
};

class Util {
public:
    static TipoCandidato parseInt(int codigo);

    int getInt() const;

private:
    Util(int valor);

    int valor;
};

#endif  // UTIL_H