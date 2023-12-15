#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <iostream>
#include <iomanip>
#include <locale>
#include <string>
#include <map>
#include "data.h"
#include "partido.h"

class Partido;
class Data;

enum class TipoCandidato {
    OUTRO = 0,
    FEDERAL = 6,
    ESTADUAL = 7
};

enum class Genero {
    MASCULINO = 0,
    FEMININO = 1,
    OUTRO = 2
};

class Candidato {
private:
    TipoCandidato tipo;
    bool ehDeferido;
    int numero;
    std::string nome;
    Partido& partido;
    bool ehFederado;
    Data dataNascimento;
    bool ehEleito;
    int votosNominais;
    Genero genero;
    bool ehVotoLegenda;

public:
    Candidato(
        TipoCandidato tipo,
        bool ehDeferido,
        int numero,
        const std::string& nome,
        Partido& partido,
        bool ehFederado,
        const Data& dataNascimento,
        bool ehEleito,
        Genero genero,
        bool ehVotoLegenda
    );

    TipoCandidato getTipo() const;
    bool isDeferido() const;
    const std::string& getNome() const;
    int getNumero() const;
    Partido& getPartido() const;
    int getVotos() const;
    bool isEleito() const;
    const Data& getDataNascimento() const;
    bool isFederado() const;
    Genero getGenero() const;
    bool isVotoLegenda() const;

    void processaVotos(int votos);
    friend ostream& operator<<(ostream& os, const Candidato& t);

    bool operator>(const Candidato* c) const;
};

#endif // CANDIDATO_H