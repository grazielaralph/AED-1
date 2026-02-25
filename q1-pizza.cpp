#include<iostream>

struct Pizza{
	std::string nome;
	float preco;
	bool delivery; //true->delivery; false->para comer na pizzaria
};

int main(){
	Pizza p1 = {"Marguerita", 55.30f, true};
	Pizza p2 = {"Calabresa", 59.10f, false};

	//mostrando a pizza p1
	std::cout << p1.nome << " - " << "R$" << p1.preco << " - " ;
	std::cout << "delivery: " << (p1.delivery?"sim":"não")<< "\n" ; 

	//mostrando a pizza p2
	std::cout << p2.nome << " - " << "R$" << p2.preco << " - " ;
	std::cout << "delivery: " << (p2.delivery?"sim":"não")<< "\n" ; 

	return 0;
}