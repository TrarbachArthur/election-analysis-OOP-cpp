#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "eleicao.h" // Certifique-se de incluir o cabeçalho correto para a classe Eleicao
#include "util.h"    // Certifique-se de incluir o cabeçalho correto para as enums Genero e TipoCandidato

class Leitor {
private:
    Eleicao eleicao;
    std::string caminhoArquivoCandidatos;
    std::string caminhoArquivoVotacao;

    static const int CD_CARGO = 17;
    static const int NR_VOTAVEL = 19;
    static const int QT_VOTOS = 21;
    static const int CD_CARGO_CAND = 13;
    static const int CD_SITU = 68;
    static const int NR_CAND = 16;
    static const int NM_URNA = 18;
    static const int NR_PART = 27;
    static const int SG_PART = 28;
    static const int NR_FED = 30;
    static const int DT_NASC = 42;
    static const int CD_SIT = 56;
    static const int CD_GEN = 45;
    static const int NM_TIPO = 67;

    static std::string le_conteudo_string(int i, const std::vector<std::string>& separated) {
        std::string x = "";
        try {
            x = separated[i].substr(1, separated[i].length() - 2);
        } catch (const std::exception& e) {
            std::cerr << "Arquivo fora do padrão fornecido!" << std::endl;
            exit(1);
        }
        return x;
    }

    static int le_conteudo_int(int i, const std::vector<std::string>& separated) {
        int y = 0;
        try {
            std::string x = separated[i].substr(1, separated[i].length() - 2);
            y = std::stoi(x);
        } catch (const std::exception& e) {
            std::cerr << "Arquivo fora do padrão fornecido!" << std::endl;
            exit(1);
        }
        return y;
    }

public:
    Leitor(const Eleicao& eleicao, const std::string& caminhoArquivoCandidatos, const std::string& caminhoArquivoVotacao)
        : eleicao(eleicao), caminhoArquivoCandidatos(caminhoArquivoCandidatos), caminhoArquivoVotacao(caminhoArquivoVotacao) {}

    void leArquivos() {
        // LENDO O ARQ DE CANDIDATOS
        try {
            std::ifstream file(caminhoArquivoCandidatos);
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir o arquivo de candidatos." << std::endl;
                exit(1);
            }

            std::string line;
            std::getline(file, line); // Ignora a primeira linha

            while (std::getline(file, line)) {
                std::vector<std::string> separated;
                std::istringstream ss(line);
                std::string token;

                while (std::getline(ss, token, ';')) {
                    separated.push_back(token);
                }

                int cargo = le_conteudo_int(CD_CARGO_CAND, separated);
                int situacaoCandidatura = le_conteudo_int(CD_SITU, separated);
                int numeroCandidato = le_conteudo_int(NR_CAND, separated);
                std::string nomeCandidato = le_conteudo_string(NM_URNA, separated);
                int numeroPartido = le_conteudo_int(NR_PART, separated);
                std::string siglaPartido = le_conteudo_string(SG_PART, separated);
                int numeroFederacao = le_conteudo_int(NR_FED, separated);
                std::string strNascimento = le_conteudo_string(DT_NASC, separated);
                int situacaoTurno = le_conteudo_int(CD_SIT, separated);
                int genero = le_conteudo_int(CD_GEN, separated);
                std::string strTipoVoto = le_conteudo_string(NM_TIPO, separated);

                std::tm dataNascimento = {};
                try {
                    std::istringstream dateStream(strNascimento);
                    dateStream >> std::get_time(&dataNascimento, "%d/%m/%Y");
                } catch (const std::exception& e) {
                    // Ignora candidatos com data de nascimento inválida
                    continue;
                }

                bool ehFederado = numeroFederacao != -1;
                bool ehEleito = situacaoTurno == 2 || situacaoTurno == 3;
                bool ehVotoLegenda = strTipoVoto == "Válido (legenda)";
                bool ehDeferido = situacaoCandidatura == 2 || situacaoCandidatura == 16;

                eleicao.processaCandidato(
                    TipoCandidato::parseInt(cargo),
                    ehDeferido,
                    numeroCandidato,
                    nomeCandidato,
                    numeroPartido,
                    siglaPartido,
                    ehFederado,
                    dataNascimento,
                    ehEleito,
                    Genero::parseInt(genero),
                    ehVotoLegenda
                );
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler o arquivo de candidatos." << std::endl;
            exit(1);
        }

        // LENDO O ARQ DE VOTAÇÃO
        try {
            std::ifstream file(caminhoArquivoVotacao);
            if (!file.is_open()) {
                std::cerr << "Erro ao abrir o arquivo de votação." << std::endl;
                exit(1);
            }

            std::string line;
            std::getline(file, line); // Ignora a primeira linha

            while (std::getline(file, line)) {
                std::vector<std::string> separated;
                std::istringstream ss(line);
                std::string token;

                while (std::getline(ss, token, ';')) {
                    separated.push_back(token);
                }

                int cargo = le_conteudo_int(CD_CARGO, separated);
                int numeroVotado = le_conteudo_int(NR_VOTAVEL, separated);
                int qtdVotos = le_conteudo_int(QT_VOTOS, separated);

                if (numeroVotado != 95 && numeroVotado != 96 && numeroVotado != 97 && numeroVotado != 98) {
                    eleicao.processaVotos(
                        TipoCandidato::parseInt(cargo),
                        numeroVotado,
                        qtdVotos
                    );
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Erro ao ler o arquivo de votação." << std::endl;
            exit(1);
        }
    }
};