#include <iostream>
using namespace std;

struct Disciplina{
	string codigo;
	string nome;
	int carga_horaria;
};

void print(Disciplina d){
	cout << d.nome << ", " << d.codigo << ", " << d.carga_horaria << "h \n";
}

int main(){
	string codigo;
	string nome;
	int carga_horaria;
	
	
	getline(std::cin, nome);
	cin >> codigo;
	cin >> carga_horaria;
	Disciplina disciplina = {codigo, nome, carga_horaria};
	
	print(disciplina);

	return 0;
}