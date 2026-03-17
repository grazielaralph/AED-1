#include <iostream>
#include <limits>
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

void printDisciplinas(Disciplina disciplinas[], int tam){
	for (int i = 0; i < tam; ++i)
		{
			disciplinas[i].print();
		}
	
}

void Disciplina::print(){
	cout << nome << ", " << codigo << ", " << carga_horaria << "h \n";
}

int main(){
	int N = 0;
	cin >> N;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	Disciplina* disciplinas; //vetor dinamico
	disciplinas = new Disciplina[N]; //cria vetor com n disciplinas

	//instancia do array
	for(int i=0; i<N; i++){
		getline(cin, disciplinas[i].nome);
		cin >> disciplinas[i].codigo;
		cin >> disciplinas[i].carga_horaria;
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	//passo o vetor disciplina 
	printDisciplinas(disciplinas, N);


	return 0;
}