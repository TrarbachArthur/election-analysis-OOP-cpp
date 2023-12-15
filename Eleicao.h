#ifndef ELEICAO_H
#define ELEICAO_H

#include <vector>
#include <unordered_map>
#include "data.h"
#include "candidato.h"
#include "partido.h"

using namespace std;

class Eleicao {
private:
    TipoCandidato opcaoCargo;
    unordered_map<int, Partido> partidos;
    unordered_map<int, Candidato> candidatos;
    vector<Candidato*> eleitos;
    const Data& data;

    int numeroVagas;
    vector<Candidato*> candidatosMaisVotados;
    vector<Partido*> partidosMaisVotados;

public:
    Eleicao(TipoCandidato opcaoCargo, const Data& data);

    TipoCandidato getOpcaoCargo() const;
    const unordered_map<int, Partido>& getPartidos() const;
    const vector<Partido*> getPartidosValues() const;
    void addPartido(Partido& partido);
    const unordered_map<int, Candidato>& getCandidatos() const;
    const vector<Candidato*> getCandidatosValues() const;
    void addCandidato(Candidato& candidato);
    const vector<Candidato*> getEleitos() const;
    void addEleito(Candidato& eleito);
    const Data& getData() const;
    int getNumeroVagas() const;
    const vector<Candidato*>& getCandidatosMaisVotados() const;
    const vector<Partido*>& getPartidosMaisVotados() const;
    void processaCandidato(
        TipoCandidato cargo,
        bool ehDeferido,
        int numeroCand,
        const string& nomeCand,
        int numeroPart,
        const string& siglaPart,
        bool ehFederado,
        const Data& dataNasc,
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

#endif