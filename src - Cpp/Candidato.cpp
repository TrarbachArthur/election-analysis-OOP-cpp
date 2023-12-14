#include <iostream>
#include <iomanip>
#include <locale>
#include <string>
#include <chrono>
#include "Partido.h"  // Substitua pelo cabeçalho correto para a classe Partido
#include "Genero.h"   // Substitua pelo cabeçalho correto para a enum Genero

class Candidato {
private:
    int votosLegenda;
    int numero;
    std::string sigla;
    std::map<int, Candidato*> candidatosDeferidos;
    std::map<int, Candidato*> candidatosIndeferidos;
    int qtdEleitos;
    std::vector<Candidato*> candidatosMaisVotados;

    std::chrono::system_clock::time_point dataNascimento; // Usado para representar a data de nascimento

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
    ) : tipo(tipo),
        ehDeferido(ehDeferido),
        numero(numero),
        nome(nome),
        partido(partido),
        ehEleito(ehEleito),
        dataNascimento(dataNascimento),
        ehFederado(ehFederado),
        genero(genero),
        ehVotoLegenda(ehVotoLegenda) {
        
        partido->addCandidato(this);
    }

    std::chrono::system_clock::time_point getDataNascimento() const {
        return dataNascimento;
    }

    TipoCandidato getTipo() const {
        return tipo;
    }

    bool isDeferido() const {
        return ehDeferido;
    }

    const std::string& getNome() const {
        return nome;
    }

    int getNumero() const {
        return numero;
    }

    Partido* getPartido() const {
        return partido;
    }

    int getVotos() const {
        return votosNominais;
    }

    bool isEleito() const {
        return ehEleito;
    }

    LocalDate getDataNascimento() const {
        return dataNascimento;
    }

    bool isFederado() const {
        return ehFederado;
    }

    Genero getGenero() const {
        return genero;
    }

    bool isVotoLegenda() const {
        return ehVotoLegenda;
    }

    void processaVotos(int votos) {
        if (isVotoLegenda()) {
            partido->processaVotos(votos);
        } else {
            votosNominais += votos;
        }
    }

    std::string toString() const {
        std::locale loc("pt_BR.utf8");
        std::cout.imbue(loc);

        return (
            nome +
            " (" +
            partido->getSigla() +
            ", " +
            std::to_string(getVotos()) +
            " votos)"
        );
    }

    bool operator<(const Candidato& c) const {
        int dif = c.getVotos() - getVotos();

        if (dif != 0) {
            return dif < 0;
        } else {
            return dataNascimento < c.getDataNascimento();
        }
    }
};