#include "eleicao.h"

Eleicao::Eleicao(TipoCandidato opcaoCargo, const Data& data): opcaoCargo(opcaoCargo), data(data) {}

TipoCandidato Eleicao::getOpcaoCargo() const {
    return opcaoCargo;
}

const unordered_map<int, Partido&> Eleicao::getPartidos() const {
    return partidos;
}

const vector<Partido&> Eleicao::getPartidosValues() const {
    vector<Partido&> result;
    for (const auto& kv : partidos) {
        result.push_back(kv.second);
    }
    return result;
}

void Eleicao::addPartido(Partido& partido) {
    this->partidos.insert({partido.getNumero(), partido});
}

const unordered_map<int, Candidato&> Eleicao::getCandidatos() const {
    return candidatos;
}

const vector<Candidato&> Eleicao::getCandidatosValues() const {
    vector<Candidato&> result;
    for (const auto& kv : candidatos) {
        result.push_back(kv.second);
    }
    return result;
}

void Eleicao::addCandidato(Candidato& candidato) {
    this->candidatos.insert({candidato.getNumero(), candidato});
}

const vector<Candidato&> Eleicao::getEleitos() const {
    return eleitos;
}

void Eleicao::addEleito(Candidato& eleito) {
    eleitos.push_back(eleito);
}

const Data& Eleicao::getData() const {
    return data;
}

int Eleicao::getNumeroVagas() const {
    return numeroVagas;
}

const vector<Candidato&> Eleicao::getCandidatosMaisVotados() const {
    return candidatosMaisVotados;
}

const vector<Partido&> Eleicao::getPartidosMaisVotados() const {
    return partidosMaisVotados;
}

void Eleicao::processaCandidato(
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
) {
    auto it_part = partidos.find(numeroPart);

    if (it_part == partidos.end()) {
        Partido partido(numeroPart, siglaPart);
        partidos.insert({partido.getNumero(), partido});
    }

    if (cargo != this->opcaoCargo) return; // Ignora candidatos de outros cargos
    if (!ehDeferido && !ehVotoLegenda) return;

    auto it = candidatos.find(numeroCand);
    // Verifica se candidato já foi inserido e define logica para substituição
    if (it != candidatos.end() && (it->second.isDeferido() || (it->second.isVotoLegenda() && !ehDeferido))) {
        return;
    }

    Candidato candidato(cargo, ehDeferido, numeroCand, nomeCand, it_part->second, ehFederado, dataNasc, ehEleito, genero, ehVotoLegenda);
    candidatos.insert({candidato.getNumero(), candidato});

    if (candidato.isEleito()) {
        eleitos.push_back(candidato);
    }
}

void Eleicao::processaVotos(
    TipoCandidato cargo,
    int numeroVotado,
    int qtdVotos
) {
    if (cargo != this->opcaoCargo) return; // Ignora candidatos de outros cargos

    auto it = candidatos.find(numeroVotado);
    if (it != candidatos.end()) {
        it->second.processaVotos(qtdVotos);
        return;
    }

    while (numeroVotado >= 100) {
        numeroVotado %= 10;
    }

    auto part_it = partidos.find(numeroVotado);

    if (part_it != partidos.end()) {
        part_it->second.processaVotos(qtdVotos);
    }
}

void Eleicao::processaEleicao() {
    numeroVagas = static_cast<int>(eleitos.size());

    // Ordena lista de candidatos mais votados
    candidatosMaisVotados = getCandidatosValues();
    sort(candidatosMaisVotados.begin(), candidatosMaisVotados.end(), greater<Candidato&>());

    // Ordena lista de partidos conforme votos totais
    partidosMaisVotados = getPartidosValues();
    sort(partidosMaisVotados.begin(), partidosMaisVotados.end(), greater<Partido&>());

    // Gera e ordena lista de candidatos mais votados por partido
    for (auto& kv : partidos) {
        kv.second.processaCandidatosMaisVotados();
    }

    // Ordena lista de candidatos eleitos
    sort(eleitos.begin(), eleitos.end(), greater<Candidato&>());
}