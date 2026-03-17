#include <iostream>
#include <limits>
using namespace std;

struct Disciplina{
	string codigo;
	string nome;
	int carga_horaria;
};

void print(Disciplina d){
	cout << d.nome << ", " << d.codigo << ", " << d.carga_horaria << "h \n";
}

void printDisciplinas(Disciplina disciplinas[], int tam){
	for (int i = 0; i < tam; ++i)
	{
		print(disciplinas[i]);
	}

}

int main(){
	int N = 0;
	cin >> N;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	Disciplina* disciplinas; //vetor dinamico
	disciplinas = new Disciplina[N]; //cria vetor com n disciplinas

	for(int i=0; i<N; i++){
		getline(cin, disciplinas[i].nome);
		cin >> disciplinas[i].codigo;
		cin >> disciplinas[i].carga_horaria;
	 	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}


	//passo o vetor disciplina 
	printDisciplinas(disciplinas, N);


	delete[] disciplinas;
	disciplinas = nullptr;


	return 0;
}