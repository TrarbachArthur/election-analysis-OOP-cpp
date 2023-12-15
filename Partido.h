#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "candidato.h"

using namespace std;

class Partido {
private:
    int votosLegenda;
    int numero;
    string sigla;
    unordered_map<int, Candidato&> candidatosDeferidos;
    unordered_map<int, Candidato&> candidatosIndeferidos;

    int qtdEleitos;
    vector<Candidato&> candidatosMaisVotados;

public:
    Partido(int numero, const string& sigla);

    int getVotosLegenda() const;
    int getNumero() const;
    const string& getSigla() const;
    const unordered_map<int, Candidato&>& getCandidatosDeferidos() const;
    const unordered_map<int, Candidato&>& getCandidatosIndeferidos() const;
    void addCandidato(Candidato& candidato);
    int getQtdEleitos() const;
    const vector<Candidato&>& getCandidatosMaisVotados() const;
    void processaVotos(int votos);
    int getVotosTotais() const;
    void processaCandidatosMaisVotados();
    friend ostream& operator<<(ostream& os, const Partido& partido);
    bool operator>(const Partido& p) const;
};

#endif // PARTIDO_H