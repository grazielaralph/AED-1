#include<iostream>
#include <list>
using namespace std;

//lista generica
template <typename T>
class List{
private: 
	T* itens;
	int length = 0;
	int max_length = 0;
	bool valid_position(int pos) const;
public:
	//construtores
	List()=default;

	List(int max_length_):max_length(max_length_){
		itens = new Task[max_length];
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
	bool empty();
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
	int porcentagem;
public:
	//construtores
	Pizza()=default; //construtor padrao
	Pizza(string name, float price, int percent):
	nome(name),
	preco(price),
	porcentagem(percent){}

	//metodos de acesso
	string getNome();
	float getPreco();
	int getPorcentagem();
};

string Pizza::getNome(){
	return nome;
}

float Pizza::getPreco(){
	return preco;
}

int Pizza::getPorcentagem(){
	return porcentagem;
}

class ShoppingCart{
private:
	list<Pizza> pizzas;
public:
	void add_pizza(Pizza p);
	float calculateTotalPrice();
	list<Pizza> get_pizzas();
}

void ShoppingCart::add_pizza(Pizza p){
	
}


