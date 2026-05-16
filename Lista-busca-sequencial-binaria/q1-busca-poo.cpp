#include <iostream>
using namespace std;

class Disciplina{
public:
	//atributos
	string codigo;
	string nome;
	int carga_horaria; //também pode ser short int


	Disciplina() = default; //construtor padrao -> serve pra instancia simples sem passagem de parametro
	Disciplina(string cod_, string nome_, int carga_horaria_){
		codigo = cod_;
		nome = nome_;
		carga_horaria = carga_horaria_;
	}

	void print();
};

void Disciplina::print(){
	cout << nome << ", " << codigo << ", " << carga_horaria << "h \n";
}

int main(){
	string codigo = "";
	string nome = "";
	int carga_horaria = 0;
	
	
	getline(std::cin, nome);
	cin >> codigo;
	cin >> carga_horaria;

	//criando e instanciando uma disciplina
	Disciplina disciplina{codigo, nome, carga_horaria};
	
	disciplina.print();

	return 0;
}