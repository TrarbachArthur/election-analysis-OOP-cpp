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
    Partido(int numero, const std::string& sigla) : votosLegenda(0), numero(numero), sigla(sigla), qtdEleitos(0) {}

    int getVotosLegenda() const {
        return votosLegenda;
    }

    int getNumero() const {
        return numero;
    }

    const std::string& getSigla() const {
        return sigla;
    }

    const std::map<int, Candidato*>& getCandidatosDeferidos() const {
        return candidatosDeferidos;
    }

    const std::map<int, Candidato*>& getCandidatosIndeferidos() const {
        return candidatosIndeferidos;
    }

    void addCandidato(Candidato* candidato);

    int getQtdEleitos() const {
        return qtdEleitos;
    }

    const std::vector<Candidato*>& getCandidatosMaisVotados() const {
        return candidatosMaisVotados;
    }

    void processaVotos(int votos) {
        votosLegenda += votos;
    }

    int getVotosTotais() const;

    void processaCandidatosMaisVotados();

    friend std::ostream& operator<<(std::ostream& os, const Partido& partido);
    
    bool operator<(const Partido& p) const;
};


void Partido::addCandidato(Candidato* candidato) {
    if (candidato->isDeferido()) {
        candidatosDeferidos[candidato->getNumero()] = candidato;

        if (candidato->isEleito()) {
            qtdEleitos++;
        }
    } else {
        candidatosIndeferidos[candidato->getNumero()] = candidato;
    }
}

int Partido::getVotosTotais() const {
    int votosTotais = getVotosLegenda();

    for (const auto& pair : candidatosDeferidos) {
        votosTotais += pair.second->getVotos();
    }

    return votosTotais;
}

void Partido::processaCandidatosMaisVotados() {
    candidatosMaisVotados.clear();
    for (const auto& pair : candidatosDeferidos) {
        candidatosMaisVotados.push_back(pair.second);
    }

    std::sort(candidatosMaisVotados.begin(), candidatosMaisVotados.end(), [](const Candidato* c1, const Candidato* c2) {
        return *c1 < *c2;
    });
}

std::ostream& operator<<(std::ostream& os, const Partido& partido) {
    os << partido.getSigla() << " - " << partido.getNumero();
    return os;
}

bool Partido::operator<(const Partido& p) const {
    int dif = p.getVotosTotais() - getVotosTotais();

    if (dif != 0) {
        return dif < 0;
    } else {
        return getNumero() < p.getNumero();
    }
}