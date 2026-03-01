#include<iostream>

struct Pizza{
	std::string nome;
	float preco;
	bool delivery; //true->delivery; false->para comer na pizzaria
};

void print_pizza(Pizza p){
	std::cout << p.nome << " - " << "R$" << p.preco << " - " ;
	std::cout << "Entrega: " << (p.delivery?"Delivery":"Mesa")<< "\n" ; 

}

//passagem de parametro por referencia-> no caso, a função altera o nome diretamente no endereço de memória da pizza
//nesse exemplo, ele altera diretamente no endereço da p1
void nomear_pizza(Pizza &pizza, std::string novo_nome){
	pizza.nome = novo_nome;
}

int main(){

	Pizza p1 = {"Marguerita", 55.30f, true};
	Pizza p2 = {"Calabresa", 59.10f, false};
	Pizza p3 = {"Brasileira", 66.50f, true};

	std::cout << "------------- Cardápio de Pizzas  -------------\n";
	//mostrando as pizzas
	print_pizza(p1);
	print_pizza(p2);
	print_pizza(p3);

	std::cout << "\n";
	std::cout<<"------------------------\n";
	std::string novo_nome = "Alho";
	nomear_pizza(p1, novo_nome);
	print_pizza(p1);

	novo_nome = "Atum";
	nomear_pizza(p2, novo_nome);
	print_pizza(p2);


	return 0;
}