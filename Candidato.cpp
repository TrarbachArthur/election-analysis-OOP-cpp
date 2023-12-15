#include "candidato.h"

Candidato::Candidato(
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
) : tipo(tipo),
    ehDeferido(ehDeferido),
    numero(numero),
    nome(nome),
    partido(partido),
    ehFederado(ehFederado),
    dataNascimento(dataNascimento),
    ehEleito(ehEleito),
    genero(genero),
    ehVotoLegenda(ehVotoLegenda) {}

TipoCandidato Candidato::getTipo() const {
    return tipo;
}

bool Candidato::isDeferido() const {
    return ehDeferido;
}

const std::string& Candidato::getNome() const {
    return nome;
}

int Candidato::getNumero() const {
    return numero;
}

Partido& Candidato::getPartido() const {
    return partido;
}

int Candidato::getVotos() const {
    return votosNominais;
}

bool Candidato::isEleito() const {
    return ehEleito;
}

const Data& Candidato::getDataNascimento() const {
    return dataNascimento;
}

bool Candidato::isFederado() const {
    return ehFederado;
}

Genero Candidato::getGenero() const {
    return genero;
}

bool Candidato::isVotoLegenda() const {
    return ehVotoLegenda;
}

void Candidato::processaVotos(int votos) {
    if (isVotoLegenda()) {
        partido.processaVotos(votos);
    } else {
        votosNominais += votos;
    }
}

ostream& operator<<(ostream& os, const Candidato& t) {
    os << t.nome << " (" << t.partido.getSigla() << ", "; 
    os << t.getVotos() << " votos)" << endl;
    return os;
}

bool Candidato::operator>(const Candidato* c) const {
    int dif = c->getVotos() - getVotos();

    if (dif != 0) {
        return dif < 0;
    } else {
        return dataNascimento < c->getDataNascimento();
    }
}
