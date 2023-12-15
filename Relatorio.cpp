#include "Relatorio.h"


Relatorio::Relatorio(Eleicao& eleicao) : eleicao(eleicao) { }

void Relatorio::geraRelatorio1() const {
    cout << "Número de vagas: " << eleicao.getNumeroVagas() << endl << endl;
}

void Relatorio::geraRelatorio2() const {
    string s = (eleicao.getOpcaoCargo() == TipoCandidato::FEDERAL) ? "federais" : "estaduais";

    cout << "Deputados " << s << " eleitos:" << endl;
    
    int i = 1;
    for (Candidato* c : eleicao.getEleitos()) {
        cout << to_string(i) << " - " << (c->isFederado() ? "*" : "") << c;
        i++;
    }

    cout << endl;
}

void Relatorio::geraRelatorio3() const {
    cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << endl;

    int i = 1;

    for (const Candidato* c : eleicao.getCandidatosMaisVotados()) {
        if (i > eleicao.getNumeroVagas()) break;
        cout << to_string(i) << " - " << (c->isFederado() ? "*" : "") << c;
        i++;
    }

    cout << endl;
}

void Relatorio::geraRelatorio4() const {
    cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;

    vector<Candidato*> eleitos = eleicao.getEleitos();
    int i = 1;

    for (const Candidato* c : eleicao.getCandidatosMaisVotados()) {
        if (i > eleicao.getNumeroVagas()) break;
        if (find(eleitos.begin(), eleitos.end(), c) == eleitos.end()) {
            cout << i << " - " << (c->isFederado() ? "*" : "") << c;
        }
        i++;
    }

    cout << endl;
}

void Relatorio::geraRelatorio5() const {
    cout << "Eleitos, que se beneficiaram do sistema proporcional:" << endl;
    cout << "(com sua posição no ranking de mais votados)" << endl;

    vector<Candidato*> candidatosMaisVotados = eleicao.getCandidatosMaisVotados();

    for (const Candidato* c : eleicao.getEleitos()) {
        auto itr_candidato = find(candidatosMaisVotados.begin(), candidatosMaisVotados.end(), c);
        int pos = itr_candidato - candidatosMaisVotados.begin();
        
        if (pos >= eleicao.getNumeroVagas()) {
            cout << to_string(pos + 1) << " - " << (c->isFederado() ? "*" : "") << c;
        }
    }

    cout << endl;
}

void Relatorio::geraRelatorio6() const {
    cout << "Votação dos partidos e número de candidatos eleitos:" << endl;

    int i = 1;
    for (const Partido* p : eleicao.getPartidosMaisVotados()) {
        int votosTotais = p->getVotosTotais();
        int votosLegenda = p->getVotosLegenda();
        int votosNominais = votosTotais - votosLegenda;

        cout << i << " - " << *p << ", " << to_string(votosTotais) << (votosTotais > 1 ? " votos (" : " voto (");
        cout << to_string(votosNominais) << ((votosNominais > 0) ? " nominais e " : " nominal e ");
        cout << to_string(votosLegenda) << " de legenda), " << p->getQtdEleitos();
        cout << (p->getQtdEleitos() > 1 ? " candidatos eleitos" : " candidato eleito");
        cout << endl;

        i++;
    }

    cout << endl;
}

void Relatorio::geraRelatorio7() const {
    cout << "Primeiro e último colocados de cada partido:" << endl;

    vector<Partido*> partidosOrdenados = eleicao.getPartidosValues();
    sort(partidosOrdenados.begin(), partidosOrdenados.end(),
        [](const Partido* p1, const Partido* p2) {
            vector<Candidato*> p1MaisVotados = p1->getCandidatosMaisVotados();
            vector<Candidato*> p2MaisVotados = p2->getCandidatosMaisVotados();

            if (p1MaisVotados.empty()) return true;
            if (p2MaisVotados.empty()) return false;

            int dif = p2MaisVotados[0]->getVotos() - p1MaisVotados[0]->getVotos();
            if (dif != 0) return dif < 0;

            return p1->getNumero() > p2->getNumero();
        }
    );

    int i = 1;
    for (const Partido* p : partidosOrdenados) {
        vector<Candidato*> candidatosMaisVotados = p->getCandidatosMaisVotados();

        if (!candidatosMaisVotados.empty() && candidatosMaisVotados[0]->getVotos() > 0) {
            const Candidato* maisVotado = candidatosMaisVotados[0];
            const Candidato* menosVotado = candidatosMaisVotados[candidatosMaisVotados.size() - 1];

            cout << i << " - " << *p << ", " << maisVotado->getNome() << " (" << maisVotado->getNumero() << ", " << maisVotado->getVotos() << (maisVotado->getVotos() > 1 ? " votos) / " : " voto) / ");
            cout << menosVotado->getNome() << " (" << menosVotado->getNumero() << ", " << menosVotado->getVotos() << (menosVotado->getVotos() > 1 ? " votos)" : " voto)") << endl;
            i++;
        }
    }
    cout << endl;
}

void Relatorio::geraRelatorio8() const {
    int menor30 = 0;
    int menor40 = 0;
    int menor50 = 0;
    int menor60 = 0;
    int maior60 = 0;
    int total = 0;

    for (const Candidato* c : eleicao.getEleitos()) {
        int idade = c->getDataNascimento().getDiffAnos(eleicao.getData());

        if (idade < 30) {
            menor30++;
        } else if (idade < 40) {
            menor40++;
        } else if (idade < 50) {
            menor50++;
        } else if (idade < 60) {
            menor60++;
        } else {
            maior60++;
        }
    }

    total = menor30 + menor40 + menor50 + menor60 + maior60;

    cout << fixed << setprecision(2);
    cout << "Eleitos, por faixa etária (na data da eleição):" << endl;
    cout << "      Idade < 30: " << menor30 << " (" << (float) 100 * menor30 / total << "%)" << endl;
    cout << "30 <= Idade < 40: " << menor40 << " (" << (float) 100 * menor40 / total << "%)" << endl;
    cout << "40 <= Idade < 50: " << menor50 << " (" << (float) 100 * menor50 / total << "%)" << endl;
    cout << "50 <= Idade < 60: " << menor60 << " (" << (float) 100 * menor60 / total << "%)" << endl;
    cout << "60 <= Idade     : " << maior60 << " (" << (float) 100 * maior60 / total << "%)" << endl;
    cout << endl;
}

void Relatorio::geraRelatorio9() const {
    int qtdFeminino = 0;
    int qtdMasculino = 0;
    int qtdTotal = 0;

    for (const Candidato* c : eleicao.getEleitos()) {
        if (c->getGenero() == Genero::FEMININO) {
            qtdFeminino++;
        } else if (c->getGenero() == Genero::MASCULINO) {
            qtdMasculino++;
        }
    }

    qtdTotal = qtdFeminino + qtdMasculino;

    cout << fixed << setprecision(2);
    cout << "Eleitos, por gênero:" << endl;
    cout << "Feminino:  " << qtdFeminino << " (" << (float) 100 * qtdFeminino / qtdTotal << "%)" << endl;
    cout << "Masculino: " << qtdMasculino << " (" << (float) 100 * qtdMasculino / qtdTotal << "%)" << endl;

    cout << endl;
}

void Relatorio::geraRelatorio10() {
    int votosNominais = 0;
    int votosLegenda = 0;
    int votosTotal = 0;

    for (const auto& pair : eleicao.getCandidatos()) {
        votosNominais += pair.second->getVotos();
    }

    for (const auto& pair : eleicao.getPartidos()) {
        votosLegenda += pair.second->getVotosLegenda();
    }

    votosTotal = votosLegenda + votosNominais;
    
    cout << fixed << setprecision(2);   
    cout << "Total de votos válidos:     " << votosTotal << endl;
    cout << "Total de votos nominais:    " << votosNominais << " (" << (float)100 * votosNominais / votosTotal << "%)" << endl;
    cout << "Total de votos de legenda:  " << votosLegenda << " (" << (float)100 * votosLegenda / votosTotal << "%)" << endl;

    cout << endl;
}

void Relatorio::geraRelatorios() {
    geraRelatorio1();
    geraRelatorio2();
    geraRelatorio3();
    geraRelatorio4();
    geraRelatorio5();
    geraRelatorio6();
    geraRelatorio7();
    geraRelatorio8();
    geraRelatorio9();
    geraRelatorio10();
}
