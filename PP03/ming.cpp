#include <iostream>
#include <string>
#include <string_view>
#include <algorithm>
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
    item = current->getItem(); //pega o item cujo endereco esta armazenado no ponteiro "navegante"
    return true;
}

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
        return &pFrontSent->next->getItem();    
    }
}


template <typename T>
const T* Deque<T>::back() const{
    if(empty()){
        cout<<"Deque vazio!";
        return nullptr;
    }else{
        return &pBackSent->prev->getItem();
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

template <typename T, typename Key>
class AvlTree{
private:
    NodeAVL<T>* root;

    //metodos basicos recursivos
    void insertRec(NodeAVL<T>*& node,const Key& key);
    void deleteRec(NodeAVL<T>*& node, const Key& key);
    void preOrderRec(NodeAVL<T>* node);
    void inOrderRec(NodeAVL<T>* node);
    void postOrderRec(NodeAVL<T>* node);
    NodeAVL<T>* findMAXRec(NodeAVL<T>* node);

    //metodos de balanceamento
    void balance(NodeAVL<T>& node);
    void updateHeight(NodeAVL<T>& node);
    int height(NodeAVL<T> node);
    int balFactor(NodeAVL<T> node);
public:
	AvlTree(): root(nullptr){};

	//metodos basicos
	void insert(T item);
	T* findMAX();
	void remove(Key key);
	void preOrder();
	void inOrder();
	void postOrder();

	//metodos de rotacao
	NodeAVL<T>* rotateR(NodeAVL<T>* y);
	NodeAVL<T>* rotateL(NodeAVL<T>* x);
	NodeAVL<T>* rotateLR(NodeAVL<T>* z);
	NodeAVL<T>* rotateRL(NodeAVL<T>* z);
};

//findMax normal e recursivo rs
template <typename T, typename Key>
NodeAVL<T>* AvlTree<T, Key>::findMAXRec(NodeAVL<T>* node){
    if(node->right == nullptr){
        return node;
    }
    return findMAXRec(node->right);
}

template <typename T, typename Key>
T*   AvlTree<T, Key>::findMAX(){
    if(root == nullptr){
        return nullptr;
    }
    return &findMAXRec(root)->getItem();
}

//metodos de percurso 
template <typename T, typename Key>
void AvlTree<T, Key>::preOrder(){
    preOrderRec(root);
}

template <typename T, typename Key>
void AvlTree<T, Key>::inOrder(){
    inOrderRec(root);
}

template <typename T, typename Key>
void AvlTree<T, Key>::postOrder(){
    postOrderRec(root);
}

// no -> esquerda -> direita
template <typename T, typename Key>
void AvlTree<T, Key>::preOrderRec(NodeAVL<T>* node){
    if(node == nullptr){
        return;
    }
    cout << node->getItem().getKey() << " ";
    preOrderRec(node->left);
    preOrderRec(node->right);
}

// esquerda -> no -> direita
template <typename T, typename Key>
void AvlTree<T, Key>::inOrderRec(NodeAVL<T>* node){
    if(node == nullptr){
        return;
    }
    inOrderRec(node->left);
    cout << node->getItem().getKey() << " ";
    inOrderRec(node->right);
}

//esquerda -> direita -> no
template <typename T, typename Key>
void AvlTree<T, Key>::postOrderRec(NodeAVL<T>* node){
    if(node == nullptr){
        return;
    }
    postOrderRec(node->left);
    postOrderRec(node->right);
    cout << node->getItem().getKey();
}

//metodos basicos
template <typename T, typename Key>
int AvlTree<T, Key>::height(NodeAVL<T>* node){
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

template <typename T, typename Key>
void AvlTree<T, Key>::insertRec(NodeAVL<T>*& node, const Key& key){
    if(node == nullptr){
        node = new NodeAVL<T>(key);
        return;
    }
    if(key < node->getItem().getKey()){
        insertRec(node->left, key);
    }else if(key > node->getItem().getKey()){
        insertRec(node->right, key);
    }else{
        return; //chave duplicada
    }

    balance(node);
}

template <typename T, typename Key>
void AvlTree<T, Key>::insert(T item){
    insertRec(root, key);
}

//metodos de balanceamento
template <typename T, typename Key>
int AvlTree<T, Key>::balFactor(NodeAVL<T>* node){
    if(node == nullptr){
        return 0;
    }
    return -height(node->left) + height(node->right);
}

template <typename T, typename Key>
void AvlTree<T, Key>::updateHeight(NodeAVL<T>& node){
    node->height = 1 + max(height(node->left), height(node->right));
}

template <typename T, typename Key>
void AvlTree<T, Key>::balance(NodeAVL<T>& node){
    updateHeight(node);
    int bf = balFactor(node);

    if(bf < -1){
        if(balFactor(node->left) > 0){
            node = rotateLR(node);
        }else{
            node = rotateR(node);
        }
    }else{
        if(bf>1){
            if(balFactor(node->right) < 0){
                node = rotateRL(node);
            }else{
                node = rotateL(node);
            }
        }
    }
}


//metodos de rotacao
template <typename T, typename Key> //rotacao simples direita
NodeAVL<T>* AvlTree<T, Key>::rotateR(NodeAVL<T>* y){
    NodeAVL<T> *x = y->left;
    NodeAVL<T> *T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

template <typename T, typename Key> //rotacao simples esquerda
NodeAVL<T>* AvlTree<T, Key>::rotateL(NodeAVL<T>* x){
    NodeAVL<T> *y = x->right;
    NodeAVL<T> *T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

template <typename T, typename Key> //rotacao dupla direita
NodeAVL<T>* AvlTree<T, Key>::rotateLR(NodeAVL<T>* z){
    z->left = rotateL(z->left); //rse no filho
    return rotateR(z); //rsd na raiz
}

template <typename T, typename Key> //rotacao dupla esquerda
NodeAVL<T>* AvlTree<T, Key>::rotateRL(NodeAVL<T>* z){
    z->right = rotateR(z->right); //rsd no filho
    return rotateL(z); //rse na raiz
}

//apagar nos
template <typename T, typename Key>
void AvlTree<T, Key>::deleteRec(NodeAVL<T>*& node, const Key& key){
    if(node == nullptr){
        return;
    }

    if (key < node->getItem().getKey()) {
        deleteRec(node->left, key);

    } else if (key > node->getItem().getKey()) {
        deleteRec(node->right, key);

    } else {
        //encontrou o no pra deletar
        if (node->left == nullptr && node->right == nullptr) {
            //caso 1 - folha
            delete node;
            node = nullptr;
            return;

        } else if (node->left == nullptr) {
            //caso 2 - so tem filho direito 
            NodeAVL<T>* temp = node;
            node = node->right;
            delete temp;
            return;

        } else if (node->right == nullptr) {
            //caso 2 - so tem filho esquerdo
            NodeAVL<T>* temp = node;
            node = node->left;
            delete temp;
            return;

        } else {
            //caso 3 - tem dois filhos (o mais dificil)
            //pega o maior da subarvore esquerda (predecessor)
            NodeAVL<T>* predecessor = findMaxRec(node->left);
            node->getItem() = predecessor->getItem(); //copia o item
            //deleta o predecessor na subarvore esquerda
            deleteRec(node->left, predecessor->getItem().getKey());
        }
    }

    //balanceia no backtracking
    balance(node);
}

template <typename T, typename Key>
void AvlTree<T, Key>::remove(Key key){
    deleteRec(root, key);
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

//tipo de dado da avl 
class IndexEntry{
private:
    string word;
    string urls[200];
    int count = 0;
public:
    //construtores
    IndexEntry(){}
    IndexEntry(string w): word(w), count(0){}

    bool addUrl(string url);
    string getKey() const;
    int getCount() const;
    string getUrl(int i) const;
};

bool IndexEntry::addUrl(string url){
    if(count>=200){
        return false; //vetor ta cheio ja fi
    }

    for(int i = 0; i < count; i++){
        if(urls[i] == url){
            return false; //verifica se a url ja existe
        }
    }

    urls[count++] = url;
    return true;
}

string IndexEntry::getKey() const{
    return word;
}

int IndexEntry::getCount() const{
    return count;
}

string IndexEntry::getUrl(int i) const{
    return urls[i];
}

//------------------------------------------------------------------------------------------

//tipo de dado da th_web
class WebEntry{
private:
    string url;
    string content;
public: 
    //construtores
    WebEntry(){}
    WebEntry(string u, string c): url(u), content(c) {}

    //metodos
    string getKey() const;
    string getContent() const;
};

string WebEntry::getKey() const{
    return url;
}

string WebEntry::getContent() const{
    return content;
}

//------------------------------------------------------------------------------------------

// tipo de dado da th_stop
class StopWord{
private:
    string word;
public:
    //construtores
    StopWord():{}
    StopWord(string w): word(w) {}
    
    string getKey() const;
};

string StopWord::getKey() const{
    return word;
}

//------------------------------------------------------------------------------------------

class Ming{
private:
    AvlTree<IndexEntry, string> AVL_INDICE;
    HashTable<WebEntry> TH_WEB;
    HashTable<StopWord> TH_STOP;
public:
    //construtor
    Ming(): TH_WEB(251), TH_STOP(97){}

}

//------------------------------------------------------------------------------------------
int main(){
    //colocar na classe Ming
    int M = 251; //tamanho da tabela hash que mapeia as url's ao conteudo da pagina
    int N = 97; //tamanho da tabela de stopwords, so tem chave



	return 0;
}