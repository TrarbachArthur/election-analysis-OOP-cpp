#include "data.h"

Data::Data(int dia, int mes, int ano) : dia(dia), mes(mes), ano(ano) {}

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