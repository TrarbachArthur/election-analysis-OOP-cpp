#include <iostream>
#include <iomanip>
#include "eleicao.h" // Certifique-se de incluir o cabeçalho correto para a classe Eleicao

class Relatorio {
private:
    Eleicao eleicao;
    static std::locale localeBR;
    static std::ostream& floatOut(std::ostream& os) {
        os.imbue(localeBR);
        os << std::fixed << std::setprecision(2);
        return os;
    }

    static std::ostream& intOut(std::ostream& os) {
        os.imbue(localeBR);
        os << std::fixed << std::setprecision(0);
        return os;
    }

public:
    Relatorio(const Eleicao& eleicao) : eleicao(eleicao) {}

    void geraRelatorio1() const {
        std::cout << "Número de vagas: " << eleicao.getNumeroVagas() << std::endl << std::endl;
    }

    void geraRelatorio2() const {
        std::string s = (eleicao.getOpcaoCargo() == TipoCandidato::FEDERAL) ? "federais" : "estaduais";

        std::cout << "Deputados " << s << " eleitos:" << std::endl;

        int i = 1;
        for (const Candidato& c : eleicao.getEleitos()) {
            std::cout << i << " - " << (c.ehFederado() ? "*" : "") << c.toString() << std::endl;
            i++;
        }

        std::cout << std::endl;
    }

    void geraRelatorio3() const {
        std::cout << "Candidatos mais votados (em ordem decrescente de votação e respeitando número de vagas):" << std::endl;

        int i = 1;

        for (const Candidato& c : eleicao.getCandidatosMaisVotados()) {
            if (i > eleicao.getNumeroVagas()) break;
            std::cout << i << " - " << (c.ehFederado() ? "*" : "") << c.toString() << std::endl;
            i++;
        }

        std::cout << std::endl;
    }

    void geraRelatorio4() const {
        std::cout << "Teriam sido eleitos se a votação fosse majoritária, e não foram eleitos:" << std::endl;
        std::cout << "(com sua posição no ranking de mais votados)" << std::endl;

        std::vector<Candidato> eleitos = eleicao.getEleitos();
        int i = 1;

        for (const Candidato& c : eleicao.getCandidatosMaisVotados()) {
            if (i > eleicao.getNumeroVagas()) break;
            if (std::find(eleitos.begin(), eleitos.end(), c) == eleitos.end()) {
                std::cout << i << " - " << (c.ehFederado() ? "*" : "") << c.toString() << std::endl;
            }
            i++;
        }

        std::cout << std::endl;
    }

    void geraRelatorio5() const {
        std::cout << "Eleitos, que se beneficiaram do sistema proporcional:" << std::endl;
        std::cout << "(com sua posição no ranking de mais votados)" << std::endl;

        std::vector<Candidato> candidatosMaisVotados = eleicao.getCandidatosMaisVotados();
        std::vector<Candidato> maisVotadosLimitada(candidatosMaisVotados.begin(), candidatosMaisVotados.begin() + eleicao.getNumeroVagas());

        for (const Candidato& c : eleicao.getEleitos()) {
            if (std::find(maisVotadosLimitada.begin(), maisVotadosLimitada.end(), c) == maisVotadosLimitada.end()) {
                std::cout << candidatosMaisVotados.size() + 1 << " - " << (c.ehFederado() ? "*" : "") << c.toString() << std::endl;
            }
        }

        std::cout << std::endl;
    }

    void geraRelatorio6() const {
        std::cout << "Votação dos partidos e número de candidatos eleitos:" << std::endl;

        int i = 1;
        for (const Partido& p : eleicao.getPartidosMaisVotados()) {
            int votosTotais = p.getVotosTotais();
            int votosLegenda = p.getVotosLegenda();
            int votosNominais = votosTotais - votosLegenda;

            std::cout << i << " - " << p.toString() << ", " << nfInt << votosTotais << (votosTotais > 1 ? " votos (" : " voto (");
            std::cout << nfInt << votosNominais << ((votosNominais > 0) ? " nominais e " : " nominal e ");
            std::cout << nfInt << votosLegenda << " de legenda), " << p.getQtdEleitos();
            std::cout << (p.getQtdEleitos() > 1) ? " candidatos eleitos" : " candidato eleito";
            std::cout << std::endl;

            i++;
        }

        std::cout << std::endl;
    }

    void geraRelatorio7() const {
        std::cout << "Primeiro e último colocados de cada partido:" << std::endl;

        std::vector<Partido> partidosOrdenados = eleicao.getPartidosValues();
        std::sort(partidosOrdenados.begin(), partidosOrdenados.end(),
            [](const Partido& p1, const Partido& p2) {
                std::vector<Candidato> p1MaisVotados = p1.getCandidatosMaisVotados();
                std::vector<Candidato> p2MaisVotados = p2.getCandidatosMaisVotados();

                if (p1MaisVotados.empty()) return true;
                if (p2MaisVotados.empty()) return false;

                int dif = p2MaisVotados[0].getVotos() - p1MaisVotados[0].getVotos();
                if (dif != 0) return dif < 0;

                return p1.getNumero() < p2.getNumero();
            }
        );

        int i = 1;
        for (const Partido& p : partidosOrdenados) {
            std::vector<Candidato> candidatosMaisVotados = p.getCandidatosMaisVotados();

            if (!candidatosMaisVotados.empty() && candidatosMaisVotados[0].getVotos() > 0) {
                const Candidato& maisVotado = candidatosMaisVotados[0];
                const Candidato& menosVotado = candidatosMaisVotados[candidatosMaisVotados.size() - 1];

                std::cout << i << " - " << p.toString() << ", " << maisVotado.getNome() << " (" << maisVotado.getNumero() << ", " << nfInt << maisVotado.getVotos() << (maisVotado.getVotos() > 1 ? " votos) / " : " voto) / ");
                std::cout << menosVotado.getNome() << " (" << menosVotado.getNumero() << ", " << nfInt << menosVotado.getVotos() << (menosVotado.getVotos() > 1 ? " votos)" : " voto)") << std::endl;
                i++;
            }
        }
        std::cout << std::endl;
    }

    void geraRelatorio8() const {
        int menor30 = 0;
        int menor40 = 0;
        int menor50 = 0;
        int menor60 = 0;
        int maior60 = 0;
        int total = 0;

        for (const Candidato& c : eleicao.getEleitos()) {
            int idade = Period::between(c.getDataNascimento(), eleicao.getData()).getYears();

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

        std::cout << "Eleitos, por faixa etária (na data da eleição):" << std::endl;
        std::cout << "      Idade < 30: " << menor30 << " (" << nfFloat << (float) 100 * menor30 / total << "%)" << std::endl;
        std::cout << "30 <= Idade < 40: " << menor40 << " (" << nfFloat << (float) 100 * menor40 / total << "%)" << std::endl;
        std::cout << "40 <= Idade < 50: " << menor50 << " (" << nfFloat << (float) 100 * menor50 / total << "%)" << std::endl;
        std::cout << "50 <= Idade < 60: " << menor60 << " (" << nfFloat << (float) 100 * menor60 / total << "%)" << std::endl;
        std::cout << "60 <= Idade     : " << maior60 << " (" << nfFloat << (float) 100 * maior60 / total << "%)" << std::endl;
        std::cout << std::endl;
    }

    void geraRelatorio9() const {
        int qtdFeminino = 0;
        int qtdMasculino = 0;
        int qtdTotal = 0;

        for (const Candidato& c : eleicao.getEleitos()) {
            if (c.getGenero() == Genero::FEMININO) {
                qtdFeminino++;
            } else if (c.getGenero() == Genero::MASCULINO) {
                qtdMasculino++;
            }
        }

        qtdTotal = qtdFeminino + qtdMasculino;

        std::cout << "Eleitos, por gênero:" << std::endl;
        std::cout << "Feminino:  " << qtdFeminino << " (" << nfFloat << (float) 100 * qtdFeminino / qtdTotal << "%)" << std::endl;
        std::cout << "Masculino: " << qtdMasculino << " (" << nfFloat << (float) 100 * qtdMasculino / qtdTotal << "%)" << std::endl;

        std::cout << std::endl;
    }

    void geraRelatorio10() {
      int votosNominais = 0;
      int votosLegenda = 0;
      int votosTotal = 0;
  
      for (const auto& pair : eleicao.getCandidatos()) {
          const Candidato& c = pair.second;
          votosNominais += c.getVotos();
      }
  
      for (const auto& pair : eleicao.getPartidos()) {
          const Partido& p = pair.second;
          votosLegenda += p.getVotosLegenda();
      }
  
      votosTotal = votosLegenda + votosNominais;
  
      std::cout << "Total de votos válidos:     " << nfInt.format(votosTotal) << std::endl;
      std::cout << "Total de votos nominais:    " << nfInt.format(votosNominais) << " (" << nfFloat.format((float)100 * votosNominais / votosTotal) << "%)" << std::endl;
      std::cout << "Total de votos de legenda:  " << nfInt.format(votosLegenda) << " (" << nfFloat.format((float)100 * votosLegenda / votosTotal) << "%)" << std::endl;
  
      std::cout << std::endl;
  }
  
  void geraRelatorios() {
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
