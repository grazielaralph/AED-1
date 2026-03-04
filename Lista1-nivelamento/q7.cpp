//ajeitar depois 
#include<iostream>
const int TAM=5;

struct Pizza{
	std::string nome;
	float preco;
	bool delivery; //true->delivery; false->para comer na pizzaria
};

void print_pizza(Pizza p){
	std::cout << p.nome << " - " << "R$" << p.preco << " - " ;
	std::cout << "Entrega: " << (p.delivery?"Delivery":"Mesa")<< "\n" ; 

}

void print_pizzas(const Pizza pizzas[], int tamanho){
	for (int i=0; i<tamanho; i++){
		print_pizza(pizzas[i]);
	}
	std::cout<<std::endl;
}


//passagem de parametro por referencia-> no caso, a função altera o nome diretamente no endereço de memória da pizza
//nesse exemplo, ele altera diretamente no endereço da p1
void nomear_pizza(Pizza &pizza, std::string novo_nome){
	pizza.nome = novo_nome;
}

float calcula_preco(Pizza pizzas[], int tamanho){
	float precoTotal=0.0f;

	for(int i=0; i<tamanho; i++){
		precoTotal = precoTotal + pizzas[i].preco;
	}

	return precoTotal;
}

int main(){

	// criando as pizzas
	Pizza p1 = {"Marguerita", 55.30f, true};
	Pizza p2 = {"Calabresa", 59.10f, false};
	Pizza p3 = {"Brasileira", 66.50f, true};
	Pizza p4 = {"Napolitana", 40.00f, true};
	Pizza p5 = {"Chocolate", 80.60f, false};

	// criando e inicializando o vetor
	Pizza pizzas[TAM] = {p1, p2, p3, p4, p5};



	//cardápio
	std::cout << "------------- Cardápio de Pizzas  -------------\n";
	print_pizzas(pizzas, TAM);
	

	/*std::cout << "\n";
	std::cout<<"-----------------Atualizando Pizzas-----------------------\n";
	std::string novo_nome = "Alho";
	nomear_pizza(pizzas[0], novo_nome);
	print_pizza(pizzas, 0);

	novo_nome = "Atum";
	nomear_pizza(pizzas[1], novo_nome);
	print_pizza(pizzas, 2);*/


	std::cout << "\n";
	std::cout<<"-------------------TOTAL--------------------\n";
	float valorTotal = calcula_preco(pizzas, TAM);
	std::cout << "Total: R$" << valorTotal;
	std::cout << "\n";

	//pizzas que são delivery
	std::cout<<"\n-------------------PIZZAS PARA ENTREGA--------------------\n";
	for (int i=0; i<TAM; i++){
		if(pizzas[i].delivery){
			print_pizza(pizzas[i]);
		}
	}
	return 0;
}