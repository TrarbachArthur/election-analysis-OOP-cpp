#include "partido.h"

Partido::Partido(int numero, const string& sigla) : votosLegenda(0), numero(numero), sigla(sigla), qtdEleitos(0) {}

int Partido::getVotosLegenda() const {
    return votosLegenda;
}

int Partido::getNumero() const {
    return numero;
}

const string& Partido::getSigla() const {
    return sigla;
}

const unordered_map<int, Candidato*>& Partido::getCandidatosDeferidos() const {
    return candidatosDeferidos;
}

const unordered_map<int, Candidato*>& Partido::getCandidatosIndeferidos() const {
    return candidatosIndeferidos;
}

void Partido::addCandidato(Candidato* candidato) {
    if (candidato->isDeferido()) {
        this->candidatosDeferidos.insert(pair<int, Candidato*>(candidato->getNumero(), candidato));
        if (candidato->isEleito()) qtdEleitos++;
    }
    else {
        this->candidatosIndeferidos.insert(pair<int, Candidato*>(candidato->getNumero(), candidato));
    }
}

int Partido::getQtdEleitos() const {
    return qtdEleitos;
}

const vector<Candidato*>& Partido::getCandidatosMaisVotados() const {
    return candidatosMaisVotados;
}

void Partido::processaVotos(int votos) {
    votosLegenda += votos;
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

    sort(candidatosMaisVotados.begin(), candidatosMaisVotados.end(), [](const Candidato* c1, const Candidato* c2) {
        return *c1 > c2;
    });
}

ostream& operator<<(ostream& os, const Partido& partido) {
    os << partido.getSigla() << " - " << partido.getNumero();
    return os;
}

bool Partido::operator>(const Partido& p) const {
    int dif = p.getVotosTotais() - getVotosTotais();

    if (dif != 0) {
        return dif < 0;
    } else {
        return getNumero() < p.getNumero();
    }
}