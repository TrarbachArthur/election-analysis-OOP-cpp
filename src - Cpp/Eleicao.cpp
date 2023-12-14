#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <locale>
#include <chrono>
#include "Candidato.h"  // Certifique-se de incluir o cabeçalho correto para a classe Candidato
#include "Partido.h"    // Certifique-se de incluir o cabeçalho correto para a classe Partido
#include "TipoCandidato.h"  // Certifique-se de incluir o cabeçalho correto para a enum TipoCandidato

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
    Eleicao(TipoCandidato opcaoCargo, const std::chrono::system_clock::time_point& data)
        : opcaoCargo(opcaoCargo), data(data) {}

    TipoCandidato getOpcaoCargo() const {
        return opcaoCargo;
    }

    std::unordered_map<int, Partido> getPartidos() const {
        return partidos;
    }

    std::vector<Partido> getPartidosValues() const {
        std::vector<Partido> result;
        for (const auto& kv : partidos) {
            result.push_back(kv.second);
        }
        return result;
    }

    void addPartido(const Partido& partido) {
        partidos[partido.getNumero()] = partido;
    }

    std::unordered_map<int, Candidato> getCandidatos() const {
        return candidatos;
    }

    std::vector<Candidato> getCandidatosValues() const {
        std::vector<Candidato> result;
        for (const auto& kv : candidatos) {
            result.push_back(kv.second);
        }
        return result;
    }

    void addCandidato(const Candidato& candidato) {
        candidatos[candidato.getNumero()] = candidato;
    }

    std::vector<Candidato> getEleitos() const {
        return eleitos;
    }

    void addEleito(const Candidato& eleito) {
        eleitos.push_back(eleito);
    }

    std::chrono::system_clock::time_point getData() const {
        return data;
    }

    int getNumeroVagas() const {
        return numeroVagas;
    }

    std::vector<Candidato> getCandidatosMaisVotados() const {
        return candidatosMaisVotados;
    }

    std::vector<Partido> getPartidosMaisVotados() const {
        return partidosMaisVotados;
    }

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
    ) {
        Partido partido = partidos[numeroPart];

        if (cargo != this->opcaoCargo) return; // Ignora candidatos de outros cargos
        if (!ehDeferido && !ehVotoLegenda) return;

        auto it = candidatos.find(numeroCand);
        if (it != candidatos.end() && (it->second.isDeferido() || (it->second.isVotoLegenda() && !ehDeferido))) {
            return;
        }

        Candidato candidato(cargo, ehDeferido, numeroCand, nomeCand, &partido, ehFederado, dataNasc, ehEleito, genero, ehVotoLegenda);
        candidatos[candidato.getNumero()] = candidato;

        if (candidato.isEleito()) {
            eleitos.push_back(candidato);
        }
    }

    void processaVotos(
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

        Partido partido = partidos[numeroVotado];

        if (partido.getNumero() > 0) {
            partido.processaVotos(qtdVotos);
        }
    }

    void processaEleicao() {
        numeroVagas = static_cast<int>(eleitos.size());

        // Ordena lista de candidatos mais votados
        candidatosMaisVotados = getCandidatosValues();
        std::sort(candidatosMaisVotados.begin(), candidatosMaisVotados.end());

        // Ordena lista de partidos conforme votos totais
        partidosMaisVotados = getPartidosValues();
        std::sort(partidosMaisVotados.begin(), partidosMaisVotados.end(),
            [](const Partido& a, const Partido& b) {
                return a.getVotosTotais() > b.getVotosTotais();
            }
        );

        // Gera e ordena lista de candidatos mais votados por partido
        for (auto& kv : partidos) {
            kv.second.processaCandidatosMaisVotados();
        }

        // Ordena lista de candidatos eleitos
        std::sort(eleitos.begin(), eleitos.end());
    }
};