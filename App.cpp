#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "Eleicao.h"
#include "Genero.h"
#include "TipoCandidato.h"
#include "Leitor.h"
#include "Relatorio.h"


int main(int argc, char *argv[]) {
    if (argc < 5) {
        std::cout << "Usage: ./deputados <opcao_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>" << std::endl;
        return 1;
    }

    int opcaoCargo;
    std::string opcaoCargoStr = argv[1];

    if (opcaoCargoStr == "--federal") {
        opcaoCargo = 6;
    } else if (opcaoCargoStr == "--estadual") {
        opcaoCargo = 7;
    } else {
        throw std::runtime_error("Opcao de cargo invalida");
    }

    std::string caminhoArquivoCandidatos = argv[2];
    std::string caminhoArquivoVotacao = argv[3];
    std::tm data = {};

    std::istringstream dateStream(argv[4]);
    dateStream >> std::get_time(&data, "%d/%m/%Y");

    if (dateStream.fail()) {
        std::cout << "Data invalida" << std::endl;
        return 1;
    }

    Eleicao eleicao(static_cast<TipoCandidato>(opcaoCargo), data);
    Leitor leitor(eleicao, caminhoArquivoCandidatos, caminhoArquivoVotacao);

    leitor.leArquivos();
    eleicao.processaEleicao();

    Relatorio relatorio(eleicao);
    relatorio.geraRelatorios();

    return 0;
}
