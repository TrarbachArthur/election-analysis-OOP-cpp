// Leitor.h
#ifndef LEITOR_H
#define LEITOR_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <ctime>
#include <iomanip>
#include "eleicao.h"

using namespace std;

class Leitor {
private:
    Eleicao& eleicao;
    string& caminhoArquivoCandidatos;
    string& caminhoArquivoVotacao;
public:
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
    
    Leitor(Eleicao& eleicao, string& caminhoArquivoCandidatos, string& caminhoArquivoVotacao);

    void leArquivos();
};

#endif