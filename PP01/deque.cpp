#include <iostream>
using namespace std;


template<typename T>
class Node {
private:
	T item;
public:
	Node<T>* next;
	Node<T>* prev;
	Node(): next(nullptr),prev(nullptr) {}
	Node(T item): item(item), next(nullptr), prev(nullptr) {}
	T& get_item();
};

template<typename T>
T& Node<T>::get_item() { return item; }


//------------------------------------------------------------------------------------------

template<typename T>
class ListNavigator{
private:
	Node<T>* current; //ponteiro que irá apontar pro item da vez
public:
	ListNavigator(Node<T>* start): current(start){}
	bool begin();
	bool end();//verifica se está no final da fila
	bool next();
	bool prev();
	bool getCurrentItem(T&); //pega o item corrente
};

template <typename T>
bool ListNavigator<T>::begin(){
	//como eu façoooo o begin
}

template<typename T>
bool ListNavigator<T>::end(){
	return current == nullptr;
}

template <typename T>
bool ListNavigator<T>::next(){
	current = current->next; //o ponteiro do navigator recebe o endereço do proximo nó
}

template <typename T>
bool ListNavigator<T>::prev(){
	current = current->prev; //o ponteiro do navigator recebe o endereço do nó anterior
}

template <typename T>
bool ListNavigator<T>::getCurrentItem(T& item){
	if(current == nullptr){
		return false;
	}
	item = current->get_item(); //pega o item cujo endereço está armazenado no ponteiro "navegante"
	return true;
}

//-----------------------------------------------------------------------------------------------------------

template <typename T>
//precisa de construtor e destrutor
class Deque{
private:
	Node<T>* pFrontSent;
	Node<T>* pBackSent;
	Node<T>* front;
	Node<T>* back;
	int length;
	void succ(Node<T>*& p);
	void prev(Node<T>*& p);
public:
	Deque(){
		front = new Node<T>{};
		front -> next;
		back = new Node<T>{};
		back -> prev;

	}
	void insertFront(T item);
	void insertBack(T item);
	void removeFront();
	void removeBack();
	T front();
	T back();
	DequeNavigator<T> const dequeNavigator();
	int size();
	bool empty();
};

int main(){
	return 0;
}