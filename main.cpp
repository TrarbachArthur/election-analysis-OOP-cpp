#include <iostream>
#include <string>
#include <ctime>
#include <iomanip>
#include "leitor.h"
#include "relatorio.h"

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 5) {
        cout << "Usage: ./deputados <opcao_de_cargo> <caminho_arquivo_candidatos> <caminho_arquivo_votacao> <data>" << endl;
        return 1;
    }

    // locale loc("pt_BR.utf8");
    // locale::global(loc);
    // cout.imbue(loc);

    int opcaoCargo;
    string opcaoCargoStr = argv[1];

    if (opcaoCargoStr == "--federal") {
        opcaoCargo = 6;
    } else if (opcaoCargoStr == "--estadual") {
        opcaoCargo = 7;
    } else {
        throw runtime_error("Opcao de cargo invalida");
    }

    string caminhoArquivoCandidatos = argv[2];
    string caminhoArquivoVotacao = argv[3];
    Data data;
    string dataStr = argv[4];

    try {
        data = Data(dataStr);
    }
    catch (invalid_argument& e) {
        cout << "Data invalida" << endl;
        return 1;
    }

    Eleicao eleicao((TipoCandidato)opcaoCargo, data);
    Leitor leitor(eleicao, caminhoArquivoCandidatos, caminhoArquivoVotacao);

    leitor.leArquivos();
    eleicao.processaEleicao();

    Relatorio relatorio(eleicao);
    relatorio.geraRelatorios();

    return 0;
}
