#include <iostream>
#include <limits>
#include <cmath> //o c indica que a biblioteca veio do c
using namespace std;

const int NIL = -1; //cte de verificacao da busca

struct Disciplina{
	string codigo;
	string nome;
	int carga_horaria;
};

//saida de uma disciplina
void print(Disciplina d){
	cout << d.nome << ", " << d.codigo << ", " << d.carga_horaria << "h \n";
}


int busca (string key, Disciplina disciplinas[], int tamanho){
	int inicio =0; //comeca pela esquerda 
	int fim = tamanho-1; //comeca pela direita 

	while (inicio<=fim){
		int meio = floor((inicio+fim)/2);
		if(key == disciplinas[meio].codigo){
			return meio;
		}else if(key < disciplinas[meio].codigo){
			fim = meio-1;

		}else{
			inicio = meio+1;
		}

	}
	return NIL;
}


int main(){
	int N = 0;
	//quantidade de disciplinas 
	cin >> N;
	cin.ignore(numeric_limits<streamsize>::max(), '\n'); //limpa o buffer

	Disciplina* disciplinas; //vetor dinamico
	disciplinas = new Disciplina[N+1]; //cria vetor com n disciplinas 

	//instancia do vetor
	for(int i=0; i<N; i++){
		getline(cin, disciplinas[i].nome);
		cin >> disciplinas[i].codigo;
		cin >> disciplinas[i].carga_horaria;
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
	}

	

	//busca sequencial com sentinela
	string cod_pesquisa;
	cin >> cod_pesquisa;
	int pos = busca(cod_pesquisa, disciplinas, N);
	if (pos==NIL){
		cout << "Nenhuma disciplina com codigo " << cod_pesquisa << " foi encontrada.\n";
	}else{
		print(disciplinas[pos]);

	}


	return 0;
}