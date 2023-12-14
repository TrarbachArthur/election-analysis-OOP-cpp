// Eleicao.h
#ifndef ELEICAO_H
#define ELEICAO_H

#include <vector>
#include <unordered_map>
#include <chrono>
#include "Candidato.h"
#include "Partido.h"
#include "TipoCandidato.h"

class Eleicao {
private:
    TipoCandidato opcaoCargo;
    std::unordered_map<int, Partido> partidos;
    std::unordered_map<int, Candidato> candidatos;
    std::vector<Candidato> eleitos;
    std::chrono::system_clock::time_point data;

    int numeroVagas;
    std::vector<Candidato> candidatosMaisVotados;
    std::vector<Partido> partidosMaisVotados;

public:
    Eleicao(TipoCandidato opcaoCargo, const std::chrono::system_clock::time_point& data);

    TipoCandidato getOpcaoCargo() const;
    std::unordered_map<int, Partido> getPartidos() const;
    std::vector<Partido> getPartidosValues() const;
    void addPartido(const Partido& partido);
    std::unordered_map<int, Candidato> getCandidatos() const;
    std::vector<Candidato> getCandidatosValues() const;
    void addCandidato(const Candidato& candidato);
    std::vector<Candidato> getEleitos() const;
    void addEleito(const Candidato& eleito);
    std::chrono::system_clock::time_point getData() const;
    int getNumeroVagas() const;
    std::vector<Candidato> getCandidatosMaisVotados() const;
    std::vector<Partido> getPartidosMaisVotados() const;
    void processaCandidato(
        TipoCandidato cargo,
        bool ehDeferido,
        int numeroCand,
        const std::string& nomeCand,
        int numeroPart,
        const std::string& siglaPart,
        bool ehFederado,
        const std::chrono::system_clock::time_point& dataNasc,
        bool ehEleito,
        Genero genero,
        bool ehVotoLegenda
    );
    void processaVotos(
        TipoCandidato cargo,
        int numeroVotado,
        int qtdVotos
    );
    void processaEleicao();
};

#endif // ELEICAO_H