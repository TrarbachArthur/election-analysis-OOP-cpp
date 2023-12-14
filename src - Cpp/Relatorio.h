// Relatorio.h
#ifndef RELATORIO_H
#define RELATORIO_H

#include <iostream>
#include <iomanip>
#include "eleicao.h" // Certifique-se de incluir o cabeçalho correto para a classe Eleicao

class Relatorio {
private:
    Eleicao eleicao;
    static std::locale localeBR;
    static std::ostream& floatOut(std::ostream& os);
    static std::ostream& intOut(std::ostream& os);

public:
    Relatorio(const Eleicao& eleicao);

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