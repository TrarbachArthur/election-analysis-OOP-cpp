// Partido.h
#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include "Candidato.h"


class Partido {
private:
    int votosLegenda;
    int numero;
    std::string sigla;
    std::map<int, Candidato*> candidatosDeferidos;
    std::map<int, Candidato*> candidatosIndeferidos;
    int qtdEleitos;
    std::vector<Candidato*> candidatosMaisVotados;

public:
    Partido(int numero, const std::string& sigla);

    int getVotosLegenda() const;
    int getNumero() const;
    const std::string& getSigla() const;
    const std::map<int, Candidato*>& getCandidatosDeferidos() const;
    const std::map<int, Candidato*>& getCandidatosIndeferidos() const;
    int getQtdEleitos() const;
    const std::vector<Candidato*>& getCandidatosMaisVotados() const;
    void processaVotos(int votos);
    int getVotosTotais() const;
    void processaCandidatosMaisVotados();
    friend std::ostream& operator<<(std::ostream& os, const Partido& partido);
    bool operator<(const Partido& p) const;
    void addCandidato(Candidato* candidato);
};

#endif // PARTIDO_H