#include<iostream>
#include <list>
using namespace std;

//lista generica
template <typename T>
class List{
private: 
	T* itens;
	int length=0;
	int max_length=0;
	bool valid_position(int pos) const;
public:
	//construtores
	List()=default;

	List(int max_length_):max_length(max_length_){
		itens = new T[max_length];
		length=0;
	}
	

	//destrutor pra matar a lista
	~List(){
		delete[] itens;
		itens = nullptr;
	}

	//metodos
	T* get_item(int pos) const;
	void insert(T item);
	int get_length() const;
	bool del(int pos);
	bool empty() const;
};

template<typename T>
bool List<T>::valid_position(int pos) const{
	return pos>0 && pos<=length;
}

template <typename T>
T* List<T>::get_item(int pos) const{
	if(valid_position(pos)){
		return &itens[pos];
	}
	return nullptr;
}

template <typename T>
void List<T>::insert(T item){
	if(length < max_length){
		length++;
		itens[length] = item;
	}else{
		cout << "Lista cheia\n";
	}
}

template<typename T>
int List<T>::get_length() const{
	return length;
}

template <typename T>
bool List<T>::empty(){
	return length == 0;
}

template<typename T>
bool List<T>::del(int pos){
	if(!empty() && valid_position(pos)){
		for(int i=pos; i<=length-1; i++){
			itens[i] = itens[i+1];
		}
		length--;
		return true;
	}
	return false;
}

class Pizza{
private:
	string nome;
	float preco;
	float porcentagem;
public:
	//construtores
	Pizza()=default; //construtor padrao
	Pizza(string name, float price, float percent):
	nome(name),
	preco(price),
	porcentagem(percent){}

	//metodos de acesso
	string getNome() const;
	float getPreco() const;
	float getPorcentagem() const;
};

string Pizza::getNome() const{
	return nome;
}

float Pizza::getPreco() const{
	return preco;
}

float Pizza::getPorcentagem() const{
	return porcentagem;
}

//funcao 
void print(const Pizza& p){
	cout<< p.getNome()<<"-";
	cout<< p.getPreco()<<"-";
	cout<< p.getPorcentagem()<<"\n";
}

class ShoppingCart{
private:
	static constexpr MAX_LENGTH=50; 
	/*forma mais elegante de definir uma cte
	inclusive como ela é estática, ela é criada antes de todo o programa
	e como consequência a gente pode acessar de qualquer lugar do codigo por referencia
	a classe
	Ex.: ShoppingCart::MAX_LENGTH*/
	List<Pizza> pizzas{MAX_LENGTH};//no construtor a gente define a quantidade de pizzas que colocaremos na lista
public:
	ShoppingCart()=default;
	void add_pizza(const Pizza& p);
	float calculateTotalPrice();
	const List<Pizza>& get_pizzas();
}

void ShoppingCart::add_pizza(Pizza p){
	pizzas.insert(p);
}

float ShoppingCart::calculateTotalPrice(){
	float soma = 0.0f;
	for (int i = 1; i <= pizzas.get_length(); ++i){
		Pizza* ptr_pizza = pizzas.get_item(i);
		float desconto = ptr_pizza->getPreco() * ptr_pizza->getPorcentagem()/100;
		soma = soma + ptr_pizza->getPreco - desconto;
	}
	return soma;
	/*Dica: evitar fazer saída de dados desnecessária em metodos 
	cuja função não é saída de dados para o usuario*/
}

const ShoppingCart::List<Pizza>& get_pizzas(){
	return pizzas;

}

void print(const ShoppingCart& sc){
	const List<Pizza> pizzas = sc.get_pizzas();
	if(pizzas.empty()){
		cout<<"Carrinho vazio!"<<endl;
	}else{
		for (int i=1; i<=pizzas.get_length(); i++){
			Pizza* pizza_ptr = pizzas.get_item(i);
			cout << i << "-"
			print(*item_ptr);
		}

	}

}

int main(){
	Pizza p1 = {"Marguerita do Mark", 55.30f, 3.0f};
	Pizza p2 = {"Calabresa  do Mark", 59.10f, 5.0f};
	Pizza p3 = {"Brasileira do Mark", 66.50f, 0.0f};
	Pizza p4 = {"Napolitana do Mark", 40.00f, 20.0f};
	Pizza p5 = {"Chocolate do Mark", 80.60f, 11.0f};

	ShoppingCart sc{}; //as chaves vazias convocam o construtor default
	sc.add_pizza(p1);
	sc.add_pizza(p1);
	sc.add_pizza(p1);
	sc.add_pizza(p1);
	sc.add_pizza(p1);

	sc.add_pizza(p2);
	sc.add_pizza(p2);
	sc.add_pizza(p2);
	sc.add_pizza(p2);

	sc.add_pizza(p3);
	sc.add_pizza(p3);
	sc.add_pizza(p3);
	sc.add_pizza(p3);
	sc.add_pizza(p3);
	sc.add_pizza(p3);
	sc.add_pizza(p3);
	sc.add_pizza(p3);
	sc.add_pizza(p3);

	sc.add_pizza(p4);
	sc.add_pizza(p4);
	sc.add_pizza(p4);
	sc.add_pizza(p4);
	sc.add_pizza(p4);
	sc.add_pizza(p4);
	sc.add_pizza(p4);
	sc.add_pizza(p4);

	sc.add_pizza(p5);
	sc.add_pizza(p5);

	print(sc);

	return 0;
}	

