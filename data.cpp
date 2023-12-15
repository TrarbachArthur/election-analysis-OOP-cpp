#include "data.h"

Data::Data() : dia(0), mes(0), ano(0) {}

Data::Data(int dia, int mes, int ano) : dia(dia), mes(mes), ano(ano) {}

Data::Data(string& dataStr) {
    vector<string> separated;
    istringstream ss(dataStr);
    string token;

    while (getline(ss, token, '/')) {
        separated.push_back(token);
    }

    if (separated.size() != 3) throw invalid_argument("Data inválida");

    this->dia = stoi(separated[0]);
    this->mes = stoi(separated[1]);
    this->ano = stoi(separated[2]);
}

int Data::getDiffAnos(const Data& data) const {
    int idade = data.ano - this->ano;

    if (data.mes < this->mes) {
        idade--;
    }
    else if (data.mes == this->mes && data.dia < this->dia) {
        idade--;
    }

    return idade;
}
bool Data::operator>(const Data& data2) const {
    if (this->getDiffAnos(data2) < 0) return true;

    return false; 
}
bool Data::operator<(const Data& data2) const {
    if (this->getDiffAnos(data2) > 0) return true;

    return false; 
}
bool Data::operator==(const Data& data2) const {
    if (this->getDiffAnos(data2) == 0) return true;

    return false;
}

ostream& operator<<(ostream& os, const Data& t) {
    os << std::to_string(t.dia) + "/" + std::to_string(t.mes) + "/" + std::to_string(t.ano);
    return os;
}