#include "leitor.h"

static string iso_8859_1_to_utf8(string &str) {
    // adaptado de: https://stackoverflow.com/a/39884120 :-)
    string strOut;
    for (string::iterator it = str.begin(); it != str.end(); ++it)
    {
        uint8_t ch = *it;
        if (ch < 0x80)
        {
        // já está na faixa ASCII (bit mais significativo 0), só copiar para a saída
        strOut.push_back(ch);
        }
        else
        {
        // está na faixa ASCII-estendido, escrever 2 bytes de acordo com UTF-8
        // o primeiro byte codifica os 2 bits mais significativos do byte original (ISO-8859-1)
        strOut.push_back(0b11000000 | (ch >> 6));
        // o segundo byte codifica os 6 bits menos significativos do byte original (ISO-8859-1)
        strOut.push_back(0b10000000 | (ch & 0b00111111));
        }
    }
    return strOut;
}

Leitor::Leitor(Eleicao& eleicao, string& caminhoArquivoCandidatos, string& caminhoArquivoVotacao)
    : eleicao(eleicao), caminhoArquivoCandidatos(caminhoArquivoCandidatos), caminhoArquivoVotacao(caminhoArquivoVotacao) {}

void Leitor::leArquivos() {
    // LENDO O ARQ DE CANDIDATOS
    string line;
    try {
        ifstream file(caminhoArquivoCandidatos);
        
        if (!file.is_open()) {
            cerr << "Erro ao abrir o arquivo de candidatos." << endl;
            exit(1);
        }
        
        getline(file, line); // Ignora a primeira linha
        
        while (getline(file, line, '\n')) {
            if (line.size() == 0) break;

            line = iso_8859_1_to_utf8(line);
            vector<string> separated;
            istringstream ss(line);
            string token;

            while (getline(ss, token, ';')) {
                token = token.substr(1, token.length() - 2);
                separated.push_back(token);
            }

            // cout << separated[CD_CARGO_CAND] << endl;
            int cargo = stoi(separated[CD_CARGO_CAND]);
            //cout << separated[CD_SITU] << endl;
            int situacaoCandidatura = stoi(separated[CD_SITU]);
            //cout << separated[NR_CAND] << endl;
            int numeroCandidato = stoi(separated[NR_CAND]);
            //cout << separated[NM_URNA] << endl;
            string nomeCandidato = separated[NM_URNA];
            // cout << separated[NR_PART] << endl;
            int numeroPartido = stoi(separated[NR_PART]);
            // cout << separated[SG_PART] << endl;
            string siglaPartido = separated[SG_PART];
            // cout << separated[NR_FED] << endl;
            int numeroFederacao = stoi(separated[NR_FED]);
            // cout << separated[DT_NASC] << endl;
            string strNascimento = separated[DT_NASC];
            // cout << separated[CD_SIT] << endl;
            int situacaoTurno = stoi(separated[CD_SIT]);
            // cout << separated[CD_GEN] << endl;
            int genero = stoi(separated[CD_GEN]);
            // cout << separated[NM_TIPO] << endl;
            string strTipoVoto = separated[NM_TIPO];

            Data dataNascimento;
            try {
                dataNascimento = Data(strNascimento);
            } catch (const exception& e) {
                // Ignora candidatos com data de nascimento inválida
                continue;
            }

            bool ehFederado = numeroFederacao != -1;
            bool ehEleito = situacaoTurno == 2 || situacaoTurno == 3;
            bool ehVotoLegenda = strTipoVoto == "Válido (legenda)";
            bool ehDeferido = situacaoCandidatura == 2 || situacaoCandidatura == 16;

            eleicao.processaCandidato(
                (TipoCandidato) cargo,
                ehDeferido,
                numeroCandidato,
                nomeCandidato,
                numeroPartido,
                siglaPartido,
                ehFederado,
                dataNascimento,
                ehEleito,
                (Genero) genero,
                ehVotoLegenda
            );
        }
    } catch (const exception& e) {
        cerr << e.what() << endl;
        cerr << "Erro ao ler o arquivo de candidatos." << endl;
        exit(1);
    }

    // LENDO O ARQ DE VOTAÇÃO
    try {
        ifstream file(caminhoArquivoVotacao);
        if (!file.is_open()) {
            cerr << "Erro ao abrir o arquivo de votação." << endl;
            exit(1);
        }

        string line;
        getline(file, line); // Ignora a primeira linha

        while (getline(file, line)) {
            vector<string> separated;
            istringstream ss(line);
            string token;

            while (getline(ss, token, ';')) {
                token = token.substr(1, token.length() - 2);
                separated.push_back(token);
            }

            int cargo = stoi(separated[CD_CARGO]);
            int numeroVotado = stoi(separated[NR_VOTAVEL]);
            int qtdVotos = stoi(separated[QT_VOTOS]);

            if (numeroVotado != 95 && numeroVotado != 96 && numeroVotado != 97 && numeroVotado != 98) {
                //cout << "Voto para " << numeroVotado << endl;
                eleicao.processaVotos(
                    (TipoCandidato) cargo,
                    numeroVotado,
                    qtdVotos
                );
            }
        }
    } catch (const exception& e) {
        cerr << "Erro ao ler o arquivo de votação." << endl;
        exit(1);
    }
}