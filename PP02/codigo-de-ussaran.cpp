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
	string key; //simbolo ianteco
	string value; //simbolo azuri
public:
	SymbolPair() : key(""), value(""){}
	SymbolPair(string k, string v): key(k), value(v){}
	string getKey() ;
	string getValue() const;
	void setValue(string v);
};

string SymbolPair::getKey(){return key;}
string SymbolPair::getValue() const{return value;}
void SymbolPair::setValue(string v){value = v;}

//------------------------------------------------------------------------------------------------------

template <typename T>
class HashTable{
private:
	Deque<T>* table; 
	int M;

    int hash (string key){
        int sum = 0;
        for(char c  : key){
            sum += (int) c; //faz um casting de cada caracter para o seu valor em ascii e soma
        }
        return sum % M; //retorna o valor equivalente a string
    }

public:
    //construtor
    HashTable(int size): M(size){
        table = new Deque<T>[M];
    }

    //destrutor
    ~HashTable(){
        delete[]  table;
    }

    void insert (T item);
    const T* search (string key);
    void remove (string key);
};

template <typename T>
void HashTable<T>::insert (T item){
    int index = hash(item.getKey());

    //Percorre o deque desse indice procurando a chave
    ListNavigator<T> nav = table[index].getDequeNavigator();
    T current;

    //caso o navigator encontre a chave, ele so atualiza o valor
    while(nav.getCurrentItem(current)){
        if(current.getKey() == item.getKey()){
            current.setValue(item.getValue());
            return;
        }
        if(nav.end()){
            break;
        }
        nav.next();

    }

    //se o navigator nao achar a chave, ele insere no final do deque
    table[index].insertBack(item);
}

template <typename T>
const T* HashTable<T>::search (string key){
    int index = hash(key);

    ListNavigator<T> nav = table[index].getDequeNavigator();
    T current;

    while(nav.getCurrentItem(current)){
        if(current.getKey() == key){
            return table[index].front(); //achamoo
        }

        if(nav.end()){
            break;
        }
    }

    return nullptr; //quando nao achar 
}

template <typename T>
void HashTable<T>::remove (string key){
    int index = hash(key);

    Deque<T> temp; //objetivo: reconstruir o deque sem o elemento a ser removido
    ListNavigator<T> nav = table[index].getDequeNavigator();
    T current;

    while(nav.getCurrentItem(current)){
        if(current.getKey() != key){
            temp.insertBack(current); //se nao for a chave a ser removida, sera copiada pro novo deque
        }
        if(nav.end()){
            break;
        }
        nav.next();
    }

    table[index] = temp;
}

//------------------------------------------------------------------------------------------------------
void fillDict(HashTable<SymbolPair>& dict) {
    string symbols[][2] = {
        {":::", "A"}, {".::","B"}, {":.:","C"}, {"::.", "D"},
        {":..","E"},  {".:.","F"}, {"..:", "G"}, {"...","H"},
        {"|::","I"},  {":|:","J"}, {"::|","K"},  {"|.:","L"},
        {".|:","M"},  {".:| ","N"},{"|:.","O"},  {":|.","P"},
        {":.| ","Q"}, {"|..","R"}, {"|.","S"},   {"..|","T"},
        {".||","U"},  {"|.|","V"}, {"||.","W"},  {"-.-","X"},
        {".--","Y"},  {"--.","Z"}, {"---"," "},  {"~","~"}
    };

    int n = sizeof(symbols) / sizeof(symbols[0]);
    for (int i = 0; i < n; i++)
        dict.insert(SymbolPair(symbols[i][0], symbols[i][1]));
}

string translateLine (const string& line, HashTable<SymbolPair>& dict){
    string result = "";
    int i = 0;

    while(i<line.size()){
        if(line.size() - i == 1){
            //verifica se e o final com os dois pontos
            result += ":";
            break;
        }
        string symbol = line.substr(i, 3);
        const SymbolPair* pair = dict.search(symbol);
        if(pair){
            result += pair->getValue();
        }
        i += 3;
    }
    return result;
}

//------------------------------------------------------------------------------------------------------
int main(){
    HashTable<SymbolPair> dict(35);

    //inserindo os simbolos na tabela
    fillDict(dict);


    return 0;
}