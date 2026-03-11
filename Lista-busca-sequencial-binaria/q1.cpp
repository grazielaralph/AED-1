#include <iostream>
using namespace std;

struct Disciplina{
	string codigo;
	string nome;
	int carga_horaria; //também pode ser short int 
};

void print(Disciplina d){
	cout << d.nome << ", " << d.codigo << ", " << d.carga_horaria << "h \n";
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
	
	print(disciplina);

	return 0;
}