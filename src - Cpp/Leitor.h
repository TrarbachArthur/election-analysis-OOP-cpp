// Leitor.h
#ifndef LEITOR_H
#define LEITOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "eleicao.h" // Certifique-se de incluir o cabeçalho correto para a classe Eleicao

class Leitor {
private:
    Eleicao eleicao;
    std::string caminhoArquivoCandidatos;
    std::string caminhoArquivoVotacao;

    static const int CD_CARGO;
    static const int NR_VOTAVEL;
    static const int QT_VOTOS;
    static const int CD_CARGO_CAND;
    static const int CD_SITU;
    static const int NR_CAND;
    static const int NM_URNA;
    static const int NR_PART;
    static const int SG_PART;
    static const int NR_FED;
    static const int DT_NASC;
    static const int CD_SIT;
    static const int CD_GEN;
    static const int NM_TIPO;

    static std::string le_conteudo_string(int i, const std::vector<std::string>& separated);
    static int le_conteudo_int(int i, const std::vector<std::string>& separated);

public:
    Leitor(const Eleicao& eleicao, const std::string& caminhoArquivoCandidatos, const std::string& caminhoArquivoVotacao);

    void leArquivos();
};

#endif // LEITOR_H