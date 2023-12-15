#ifndef date_h
#define date_h
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Data {

private:
  int dia;
  int mes;
  int ano;

public:
  Data();
  Data(int dia, int mes, int ano);
  Data(string& dataStr);
  int getDiffAnos(const Data& data) const;
  bool operator>(const Data& data2) const;
  bool operator<(const Data& data2) const;
  bool operator==(const Data& data2) const;

  friend ostream& operator<<(ostream& os, const Data& t);
};

#endif