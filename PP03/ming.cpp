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
    T& getItem();
};

template<typename T>
T& Node<T>::getItem() { return item; }

//------------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------------

template<typename T>
class NodeAVL {
private:
    T item;
    int height = 1;
public:
    NodeAVL<T>* left;
    NodeAVL<T>* right;
    NodeAVL(): left(nullptr),right(nullptr) {}
    NodeAVL(T item): item(item), left(nullptr), right(nullptr) {}
    T& getItem();
};

template<typename T>
T& NodeAVL<T>::getItem() { return item; }

//-----------------------------------------------------------------------------------------------------------

template <typename T>
class AvlTree{
private:
	//eu coloco root como privado ou como publico?
public:
	AvlTree<T>* root;
	AvlTree(): root(nullptr){};
	//sao todos void? 
	//metodos basicos
	void insert(Key key);
	void insertRec(NodeAVL& node, Key key);
	void findMAX(NodeAVL node);
	void delete(Key key);
	void deleteRec(NodeAVL &node, Key key);
	void preOrder();
	void preOrderRec(NodeAVL node);
	void inOrder();
	void inOrderRec(NodeAVL node);
	void postOrder();
	void postOrderRec(NodeAVL node);
	//metodos de balanceamento
	void balance(NodeAVL& node);
	void updateHeight(NodeAVL node);
	void height(NodeAVL node);
	void balFactor(NodeAVL node);
	//metodos de rotacao
	void rotateR();
	void rotateL();
	void rotateLR();
	void rotateRL();
}

//------------------------------------------------------------------------------------------
constexpr size_t hash(string_view s, size_t M){
    if(s.empty() || M==0){
        return 0;
    }

    size_t hashValue = 0;

    for(size_t i = 0; i < s.length(); i++){
        unsigned char c = static_cast <unsigned char>(s[i]);
        hashValue = (hashValue * 128 + c) % M;
    }

    return hashValue;
}

template <typename T>
class HashTable{
private:
	Deque<T>* table; 
	int M;
    T lastFound; //guarda o ultimo item quebrado
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
};

template <typename T>
void HashTable<T>::insert (T item){
    int index = ::hash(item.getKey(), M);

    if(!table[index].empty()){
        //Percorre o deque desse indice procurando a chave
    ListNavigator<T> nav = table[index].getDequeNavigator();
    T current;

    //caso o navigator encontre a chave, ele so atualiza o valor
    while(nav.getCurrentItem(current)){
        if(current.getKey() == item.getKey()){
            table[index].removeFront();
            table[index].insertBack(item);
            return;
        }
        if(nav.end()){
            break;
        }
        nav.next();

        }
   
    }

    //se o navigator nao achar a chave, ele insere no final do deque
    table[index].insertBack(item); 
    
}

template <typename T>
const T* HashTable<T>::search (string key){
    int index = ::hash(key, M);

    if(table[index].empty()){
        return nullptr;
    }

    ListNavigator<T> nav = table[index].getDequeNavigator();
    T current;

    while(nav.getCurrentItem(current)){
        if(current.getKey() == key){
            lastFound = current; //copia para o atributo da classe
            return &lastFound;
        }

        if(nav.end()){
            break;
        }

        nav.next();
    }
    

    return nullptr; //quando nao achar 
}

//------------------------------------------------------------------------------------------

int main(){
	return 0;
}