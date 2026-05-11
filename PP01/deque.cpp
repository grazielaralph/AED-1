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
	return current->prev == nullptr;
}

template<typename T>
bool ListNavigator<T>::end(){
	return current->next == nullptr;
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
class Deque{
private:
	Node<T>* front;
	Node<T>* back;
	int length;
	void succ(Node<T>*& p);
	void prev(Node<T>*& p);
public:
	//construtores
	Deque(){
		front = new Node<T>{};
		back = new Node<T>{};
		front->next=back;
		back->prev=front;
		length=0;
	}

	//destrutor
	~Deque(){
		if(length!=0){
			Node<T>* p = front->next;
			while(p!=back){
				delete p; //apaga o nó que p recebeu, no caso nó corrente
				succ(p);
			}
		}
		//mesmo que o deque esteja vazio, é necessario 
		delete front;
		delete back;
	}

	//metodos da classe
	void insertFront(T item);
	void insertBack(T item);
	void removeFront();
	void removeBack();
	T front();
	T back();
	ListNavigator<T> const getDequeNavigator();
	int size();
	bool empty();
};

template <typename T>
void Deque<T>::succ(Node<T>*& p){
	p=p->next;
}

template <typename T>
void Deque<T>::prev(Node<T>*& p){
	p=p->prev;
}

template <typename T>
void Deque<T>::insertFront(T item){
	Node<T>* pNew = new Node<T>(item);
	pNew->next = front->next;
	pNew->next->prev = pNew;
	front->next = pNew;
	pNew->prev = front;
	length++;
}

template <typename T>
void Deque<T>::insertBack(T item){
	Node<T>* pNew = new Node<T>(item);
	pNew->prev = back->prev; //prev.pNew recebe prev.back
	pNew->prev->next = pNew; //acesso o ultimo item da fila e falo pro next dele apontar pro nó novo
	back->prev = pNew; //prev.back recebe o endereço do novo item
	pNew->next=back; //next.pNew recebe o endereço do back
	length++;
}

template <typename T>
void Deque<T>::removeFront(){
	if(empty()) return; //para nao deletar sentinela sem querer
	Node<T>* p = front->next;
	front->next = p->next;
	p->next->prev = front; //prev.nó sucessor recebe o front
	delete p;
	length--;
}

template <typename T>
void Deque<T>::removeBack(){
	if(empty()) return;
	Node<T>* p = back->prev;
	back->prev = p->prev;
	p->prev->next = back;
	delete p;
	length--;
}

template <typename T>
const T* Deque<T>::front() const{
	if(empty()){
		cout<<"Deque vazio!";
		return nullptr;
	}else{
		return &front->next->get_item();	
	}
}


template <typename T>
const T* Deque<T>::back() const{
	if(empty()){
		cout<<"Deque vazio!";
		return nullptr;
	}else{
		return &back->prev->get_item();
	}
}

template <typename T>
ListNavigator<T> const Deque<T>::getDequeNavigator(){
	return ListNavigator<T>{front->next};
}

template <typename T>
int Deque<T>::size(){
	return length;
}

template <typename T>
bool Deque<T>::empty(){
	if(length == 0){
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------------------------------------
template <typename T>
class Queue{
private: 
    int length = 0;
    Deque<T> dequeQueue;
public:
	Queue():length(0){}
	~Queue(){} //aciona o destrutor do deque para destruir a fila
	void enqueue(T item);
	void dequeue();
	const T& front();
	bool empty();
	int size();
	ListNavigator getQueueNavigator();
    };

template <typename T>
void Queue<T>::enqueue(T item){
   	dequeQueue.insertBack(item);
   }

template <typename    
void Queue<T>::dequeue(){
   	dequeQueue.removeFront();
   }

template <typename T>
const T& Queue<T>::front(){
   	return dequeQueue.front();
   }

template <typename T>   
bool Queue<T>::empty(){
   	if(length == 0){
   		return true;
   	}
   	return false;
   }

template <typename T>
int Queue<T>::size(){
   	return length;
   }

template <typename T>
ListNavigator Queue<T>::getQueueNavigator(){
   	return dequeQueue.getDequeNavigator();
   }

//-----------------------------------------------------------------------------------------------------------
   
template <typename T>
class Stack{
private:
   	int length;
   	Deque<T> dequeStack;
public:
   	Stack():length(0){}
   	void push(T item);
   	void pop();
   	const T& top();
   	bool empty();
   	int size();
   	ListNavigator getStackNavigator();
   }

template <typename T>
void Stack<T>::push(T item){
   	dequeStack.insertFront(item);
   }
   
template <typename T>
void Stack<T>::pop(){
   	dequeStack.removeFront();
   }

template <typename T>
const T& Stack<T>::top(){
   	return dequeStack.front();
   }

template <typename T>
bool Stack<T>::empty(){
   	if(length == 0){
   		return true;
   	}
   	return false;
   }

template <typename T>
int Stack<T>::size(){
   	return length;
   }

template <typename T>
ListNavigator Stack<T>::getQueueNavigator(){
   	return dequeStack.getDequeNavigator();
   }
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
int main(){
	return 0;
}