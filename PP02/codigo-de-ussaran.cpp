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
    Node<T>* current; //ponteiro que ira apontar pro item da vez
public:
    ListNavigator(Node<T>* start): current(start){}
    bool begin();
    bool end();//verifica se esta no final da fila
    void next();
    void prev();
    bool getCurrentItem(T&); //pega o item corrente
};

template <typename T>
bool ListNavigator<T>::begin(){
    return current->prev == nullptr;
}

template<typename T>
bool ListNavigator<T>::end(){
    return current->next->next == nullptr;
}

template <typename T>
void ListNavigator<T>::next(){
    current = current->next; //o ponteiro do navigator recebe o endereco do proximo no
}

template <typename T>
void ListNavigator<T>::prev(){
    current = current->prev; //o ponteiro do navigator recebe o endereco do no anterior
}

template <typename T>
bool ListNavigator<T>::getCurrentItem(T& item){
    if(current == nullptr){
        return false;
    }
    item = current->get_item(); //pega o item cujo endereco esta armazenado no ponteiro "navegante"
    return true;
}

//-----------------------------------------------------------------------------------------------------------

template <typename T>
class Deque{
private:
    Node<T>* pFrontSent;
    Node<T>* pBackSent;
    int length;
    void succ(Node<T>*& p);
    void prev(Node<T>*& p);
public:
    //construtor
    Deque(){
        pFrontSent = new Node<T>{};
        pBackSent = new Node<T>{};
        pFrontSent->next=pBackSent;
        pBackSent->prev=pFrontSent;
        length=0;
    }

    //destrutor
    ~Deque(){
        if(length!=0){
            Node<T>* p = pFrontSent->next;
            while(p != pBackSent){
                Node<T>* next = p->next;
                delete p; //apaga o no que p recebeu, no caso no corrente
                p = next;
            }
        }
        //mesmo que o deque esteja vazio, e necessario 
        delete pFrontSent;
        delete pBackSent;
    }

    //metodos da classe
    void insertFront(T item);
    void insertBack(T item);
    void removeFront();
    void removeBack();
    const T* front() const;
    const T* back() const;
    ListNavigator<T> const getDequeNavigator();
    int size();
    bool empty() const;
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
    pNew->next = pFrontSent->next;
    pNew->next->prev = pNew;
    pFrontSent->next = pNew;
    pNew->prev = pFrontSent;
    length++;
}

template <typename T>
void Deque<T>::insertBack(T item){
    Node<T>* pNew = new Node<T>(item);
    pNew->prev = pBackSent->prev; 
    pNew->prev->next = pNew; 
    pBackSent->prev = pNew; 
    pNew->next=pBackSent; 
    length++;
}

template <typename T>
void Deque<T>::removeFront(){
    if(empty()) return; //para nao deletar sentinela sem querer
    Node<T>* p = pFrontSent->next;
    pFrontSent->next = p->next;
    p->next->prev = pFrontSent; 
    delete p;
    length--;
}

template <typename T>
void Deque<T>::removeBack(){
    if(empty()) return;
    Node<T>* p = pBackSent->prev;
    pBackSent->prev = p->prev;
    p->prev->next = pBackSent;
    delete p;
    length--;
}

template <typename T>
const T* Deque<T>::front() const{
    if(empty()){
        cout<<"Deque vazio!";
        return nullptr;
    }else{
        return &pFrontSent->next->get_item();    
    }
}


template <typename T>
const T* Deque<T>::back() const{
    if(empty()){
        cout<<"Deque vazio!";
        return nullptr;
    }else{
        return &pBackSent->prev->get_item();
    }
}

template <typename T>
ListNavigator<T> const Deque<T>::getDequeNavigator(){
    return ListNavigator<T>(pFrontSent->next);
}

template <typename T>
int Deque<T>::size(){
    return length;
}

template <typename T>
bool Deque<T>::empty() const{
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
    const T* front();
    bool empty();
    int size();
    ListNavigator<T> getQueueNavigator();
    };

template <typename T>
void Queue<T>::enqueue(T item){
       dequeQueue.insertBack(item);
   }

template <typename T>
void Queue<T>::dequeue(){
       dequeQueue.removeFront();
   }

template <typename T>
const T* Queue<T>::front(){
       return dequeQueue.front();
   }

template <typename T>   
bool Queue<T>::empty(){
       return dequeQueue.empty();
   }

template <typename T>
int Queue<T>::size(){
       return dequeQueue.size();
   }

template <typename T>
ListNavigator<T> Queue<T>::getQueueNavigator(){
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
       ListNavigator<T> getStackNavigator();
   };

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
       return *dequeStack.front();
   }

template <typename T>
bool Stack<T>::empty(){
       return dequeStack.empty();
   }

template <typename T>
int Stack<T>::size(){
       return dequeStack.size();
   }

template <typename T>
ListNavigator<T> Stack<T>::getStackNavigator(){
       return dequeStack.getDequeNavigator();
   }

//------------------------------------------------------------------------------------------------------

class SymbolPair{
private:
	String key; //simbolo ianteco
	String value; //simbolo azuri
public:
	SymbolPair() : key(""), value(""){}
	SymbolPair(string k, string v): key(k), value(v){}
	String getKey();
	String getValue();
	void setValue(String v);
};

String SymbolPair::getKey(){return key;}
String SymbolPair::getValue(){return value;}
void SymbolPair::setValue(String v){value = v;}