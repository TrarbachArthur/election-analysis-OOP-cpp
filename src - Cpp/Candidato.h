// Candidato.h
#ifndef CANDIDATO_H
#define CANDIDATO_H

#include <iostream>
#include <iomanip>
#include <locale>
#include <string>
#include <chrono>
#include <map>
#include "Partido.h"  // Substitua pelo cabeçalho correto para a classe Partido
#include "Genero.h"
#include "TipoCandidato.h"    // Substitua pelo cabeçalho correto para a enum Genero

class Candidato {
private:
    TipoCandidato tipo;
    bool ehDeferido;
    int numero;
    std::string nome;
    Partido* partido;
    bool ehFederado;
    std::chrono::system_clock::time_point dataNascimento;
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
        Partido* partido,
        bool ehFederado,
        const std::chrono::system_clock::time_point& dataNascimento,
        bool ehEleito,
        Genero genero,
        bool ehVotoLegenda
    );

    TipoCandidato getTipo() const;
    bool isDeferido() const;
    const std::string& getNome() const;
    int getNumero() const;
    Partido* getPartido() const;
    int getVotos() const;
    bool isEleito() const;
    std::chrono::system_clock::time_point getDataNascimento() const;
    bool isFederado() const;
    Genero getGenero() const;
    bool isVotoLegenda() const;

    void processaVotos(int votos);
    std::string toString() const;

    bool operator<(const Candidato& c) const;
};

#endif // CANDIDATO_H