// Relatorio.h
#ifndef RELATORIO_H
#define RELATORIO_H

#include <iostream>
#include <iomanip>
#include "eleicao.h"

using namespace std;

class Relatorio {
private:
    Eleicao& eleicao;

public:
    Relatorio(Eleicao& eleicao);

    void geraRelatorio1() const;

    void geraRelatorio2() const;

    void geraRelatorio3() const;

    void geraRelatorio4() const;

    void geraRelatorio5() const;

    void geraRelatorio6() const;

    void geraRelatorio7() const;

    void geraRelatorio8() const;

    void geraRelatorio9() const;

    void geraRelatorio10();

    void geraRelatorios();
};

#endif // RELATORIO_H