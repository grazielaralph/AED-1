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
    Node<T>* current; 
public:
    ListNavigator(Node<T>* start): current(start){}
    bool begin();
    bool end();
    void next();
    void prev();
    bool getCurrentItem(T&); 
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
    current = current->next; 
}

template <typename T>
void ListNavigator<T>::prev(){
    current = current->prev; 
}

template <typename T>
bool ListNavigator<T>::getCurrentItem(T& item){
    if(current == nullptr){
        return false;
    }
    item = current->getItem(); 
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
    Deque(){
        pFrontSent = new Node<T>{};
        pBackSent = new Node<T>{};
        pFrontSent->next=pBackSent;
        pBackSent->prev=pFrontSent;
        length=0;
    }

    ~Deque(){
        if(length!=0){
            Node<T>* p = pFrontSent->next;
            while(p != pBackSent){
                Node<T>* next = p->next;
                delete p; 
                p = next;
            }
        }
        delete pFrontSent;
        delete pBackSent;
    }

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
    if(empty()) return; 
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
        return nullptr;
    }else{
        return &pFrontSent->next->getItem();    
    }
}

template <typename T>
const T* Deque<T>::back() const{
    if(empty()){
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
    return length == 0;
}

//------------------------------------------------------------------------------------------

template<typename T>
class NodeAVL {
private:
    T item;
public:
    int height = 1;
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

    // Metodos basicos recursivos 
    void insertRec(NodeAVL<T>*& node, const T& item);
    void deleteRec(NodeAVL<T>*& node, const Key& key);
    void preOrderRec(NodeAVL<T>* node);
    void inOrderRec(NodeAVL<T>* node);
    void postOrderRec(NodeAVL<T>* node);
    NodeAVL<T>* findMAXRec(NodeAVL<T>* node);
    NodeAVL<T>* searchRec(NodeAVL<T>* node, const Key& key) const;
    bool updateRec(NodeAVL<T>* node, const Key& key, const T& newItem);

    // Metodos de balanceamento 
    void balance(NodeAVL<T>*& node);
    void updateHeight(NodeAVL<T>* node);
    int height(NodeAVL<T>* node);
    int balFactor(NodeAVL<T>* node);
public:
    AvlTree(): root(nullptr){};

    void insert(T item);
    T* findMAX();
    void remove(Key key);
    void preOrder();
    void inOrder();
    void postOrder();
    T* search(const Key& key);
    bool update (const Key& key, const T& newItem);

    NodeAVL<T>* rotateR(NodeAVL<T>* y);
    NodeAVL<T>* rotateL(NodeAVL<T>* x);
    NodeAVL<T>* rotateLR(NodeAVL<T>* z);
    NodeAVL<T>* rotateRL(NodeAVL<T>* z);
};

template <typename T, typename Key>
NodeAVL<T>* AvlTree<T, Key>::findMAXRec(NodeAVL<T>* node){
    if(node->right == nullptr){
        return node;
    }
    return findMAXRec(node->right);
}

template <typename T, typename Key>
T* AvlTree<T, Key>::findMAX(){
    if(root == nullptr){
        return nullptr;
    }
    return &findMAXRec(root)->getItem();
}

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

template <typename T, typename Key>
void AvlTree<T, Key>::preOrderRec(NodeAVL<T>* node){
    if(node == nullptr){
        return;
    }
    cout << node->getItem().getKey() << " ";
    preOrderRec(node->left);
    preOrderRec(node->right);
}

template <typename T, typename Key>
void AvlTree<T, Key>::inOrderRec(NodeAVL<T>* node){
    if(node == nullptr){
        return;
    }
    inOrderRec(node->left);
    cout << node->getItem().getKey() << " ";
    inOrderRec(node->right);
}

template <typename T, typename Key>
void AvlTree<T, Key>::postOrderRec(NodeAVL<T>* node){
    if(node == nullptr){
        return;
    }
    postOrderRec(node->left);
    postOrderRec(node->right);
    cout << node->getItem().getKey();
}

template <typename T, typename Key>
int AvlTree<T, Key>::height(NodeAVL<T>* node){
    if(node == nullptr){
        return 0;
    }
    return node->height;
}

template <typename T, typename Key>
void AvlTree<T, Key>::insertRec(NodeAVL<T>*& node, const T& item){
    if(node == nullptr){
        node = new NodeAVL<T>(item);
        return;
    }
    if(item.getKey() < node->getItem().getKey()){
        insertRec(node->left, item);
    }else if(item.getKey() > node->getItem().getKey()){
        insertRec(node->right, item);
    }else{
        return; 
    }

    balance(node);
}

template <typename T, typename Key>
void AvlTree<T, Key>::insert(T item){
    insertRec(root, item);
}

template <typename T, typename Key>
int AvlTree<T, Key>::balFactor(NodeAVL<T>* node){
    if(node == nullptr){
        return 0;
    }
    return -height(node->left) + height(node->right);
}

template <typename T, typename Key>
void AvlTree<T, Key>::updateHeight(NodeAVL<T>* node){
    if(node != nullptr) {
        node->height = 1 + max(height(node->left), height(node->right));
    }
}

template <typename T, typename Key>
void AvlTree<T, Key>::balance(NodeAVL<T>*& node){
    if (node == nullptr) return;
    
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

template <typename T, typename Key> 
NodeAVL<T>* AvlTree<T, Key>::rotateR(NodeAVL<T>* y){
    NodeAVL<T> *x = y->left;
    NodeAVL<T> *T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

template <typename T, typename Key> 
NodeAVL<T>* AvlTree<T, Key>::rotateL(NodeAVL<T>* x){
    NodeAVL<T> *y = x->right;
    NodeAVL<T> *T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

template <typename T, typename Key> 
NodeAVL<T>* AvlTree<T, Key>::rotateLR(NodeAVL<T>* z){
    z->left = rotateL(z->left); 
    return rotateR(z); 
}

template <typename T, typename Key> 
NodeAVL<T>* AvlTree<T, Key>::rotateRL(NodeAVL<T>* z){
    z->right = rotateR(z->right); 
    return rotateL(z); 
}

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
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            node = nullptr;
            return;
        } else if (node->left == nullptr) {
            NodeAVL<T>* temp = node;
            node = node->right;
            delete temp;
            return;
        } else if (node->right == nullptr) {
            NodeAVL<T>* temp = node;
            node = node->left;
            delete temp;
            return;
        } else {
            NodeAVL<T>* predecessor = findMAXRec(node->left);
            node->getItem() = predecessor->getItem(); 
            deleteRec(node->left, predecessor->getItem().getKey());
        }
    }
    balance(node);
}

template <typename T, typename Key>
void AvlTree<T, Key>::remove(Key key){
    deleteRec(root, key);
}

template <typename T, typename Key>
NodeAVL<T>* AvlTree<T, Key>::searchRec(NodeAVL<T>* node, const Key& key) const{
    if(node == nullptr){
        return nullptr;
    }

    if(key < node->getItem().getKey()) {
        return searchRec(node->left, key); 
    } else if(key > node->getItem().getKey()){
        return searchRec(node->right, key); 
    }else{
        return node; 
    }
}

template <typename T, typename Key>
T* AvlTree<T, Key>::search(const Key& key){
    NodeAVL<T>* res = searchRec(root, key);
    if(res == nullptr){
        return nullptr;
    }
    return &res->getItem(); 
}

template <typename T, typename Key>
bool AvlTree<T, Key>::updateRec(NodeAVL<T>* node, const Key& key, const T& newItem) {
    if(node == nullptr){
        return false;
    }

    if(key < node->getItem().getKey()){
        return updateRec(node->left, key, newItem);
    } else if(key > node->getItem().getKey()){ 
        return updateRec(node->right, key, newItem);
    }else{
        node->getItem() = newItem;
        return true;
    }
}

template <typename T, typename Key>
bool AvlTree<T, Key>::update(const Key& key, const T& newItem){
    return updateRec(root, key, newItem);
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
    T lastFound; 
public:
    HashTable(int size): M(size){
        table = new Deque<T>[M];
    }

    ~HashTable(){
        delete[] table;
    }

    void insert (T item);
    const T* search (string key);
};

template <typename T>
void HashTable<T>::insert (T item){
    int index = ::hash(item.getKey(), M);

    if(!table[index].empty()){
        ListNavigator<T> nav = table[index].getDequeNavigator();
        T current;

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
            lastFound = current; 
            return &lastFound;
        }
        if(nav.end()){
            break;
        }
        nav.next();
    }
    return nullptr; 
}

//------------------------------------------------------------------------------------------

class IndexEntry{
private:
    string word;
    string urls[200];
    int count = 0;
public:
    IndexEntry(){}
    IndexEntry(string w): word(w), count(0){}

    bool addUrl(string url);
    string getKey() const;
    int getCount() const;
    string getUrl(int i) const;
    void printUrls();
};

bool IndexEntry::addUrl(string url){
    if(count>=200){
        return false; 
    }

    for(int i = 0; i < count; i++){
        if(urls[i] == url){
            return false; 
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

void IndexEntry::printUrls(){
    for(int i = 0; i < count; i++) {
        cout << urls[i] << endl;
    }
}
//------------------------------------------------------------------------------------------

class WebEntry{
private:
    string url;
    string content;
public: 
    WebEntry(){}
    WebEntry(string u, string c): url(u), content(c) {}

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

class StopWord{
private:
    string word;
public:
    StopWord() {}
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
    Deque<string> tokenizar(string texto);
public:
    Ming(): TH_WEB(251), TH_STOP(97){}

    void indexarPagina(string url, string conteudo);
    void carregarStopWord(string palavra);
    void buscar(string termo);
};

Deque<string> Ming::tokenizar(string texto){
    Deque<string> tokens;
    string atual = "";

    for(char c : texto){
        if (c == ' '){
            if(!atual.empty()){
                tokens.insertBack(atual);
                atual = "";
            }
        }else{
            atual += c;
        }
    }

    if(!atual.empty()){
        tokens.insertBack(atual);
    }

    return tokens;
}

void Ming::indexarPagina(string url, string conteudo){
    TH_WEB.insert(WebEntry(url, conteudo));

    Deque<string> palavras = tokenizar(conteudo);
    ListNavigator<string> nav = palavras.getDequeNavigator();
    string palavraAtual;

    while(nav.getCurrentItem(palavraAtual)){
        transform(palavraAtual.begin(), palavraAtual.end(), palavraAtual.begin(), ::tolower);

        if(TH_STOP.search(palavraAtual) != nullptr){
            if(nav.end()){
                break;
            }
            nav.next();
            continue;
        }

        IndexEntry* existente = AVL_INDICE.search(palavraAtual);

        if(existente == nullptr){
            IndexEntry novo(palavraAtual);
            novo.addUrl(url);
            AVL_INDICE.insert(novo);
        }else{
            if(existente->addUrl(url)){
                AVL_INDICE.update(palavraAtual, *existente);
            }
        } 

        if(nav.end()){
            break;
        }   
        nav.next();
    }
}

void Ming::carregarStopWord(string palavra){
    transform(palavra.begin(), palavra.end(), palavra.begin(), ::tolower);
    TH_STOP.insert(StopWord(palavra));
}

void Ming::buscar(string consulta){
    Deque<string> termosBrutos = tokenizar(consulta);
    ListNavigator<string> navTermos = termosBrutos.getDequeNavigator();

    Deque<string> termosValidos;
    string termoAtual;

    while(navTermos.getCurrentItem(termoAtual)){
        transform(termoAtual.begin(), termoAtual.end(), termoAtual.begin(), ::tolower);

        if (TH_STOP.search(termoAtual) == nullptr) {
            termosValidos.insertBack(termoAtual);
        }

        if(navTermos.end()){
            break;
        }
        navTermos.next();
    }

    ListNavigator<string> navValidos = termosValidos.getDequeNavigator();
    string primeiraPalavra;

    if (!navValidos.getCurrentItem(primeiraPalavra)) {
        cout << "Nenhum resultado." << endl;
        return;
    }

    string resultadoUrls[200];
    int qtdUrlsResultado = 0;

    IndexEntry* nPrimeiro = AVL_INDICE.search(primeiraPalavra);
    
    if (nPrimeiro == nullptr) {
        cout << "Nenhum resultado." << endl;
        return;
    }

    int totalPrimeiro = nPrimeiro->getCount();
    for(int i = 0; i < totalPrimeiro; i++) {
        if (qtdUrlsResultado < 200) {
            resultadoUrls[qtdUrlsResultado++] = nPrimeiro->getUrl(i);
        }
    }

    if(!navValidos.end()){
        navValidos.next(); 
        string proximaPalavra;

        while(navValidos.getCurrentItem(proximaPalavra)){
            IndexEntry* nProximo = AVL_INDICE.search(proximaPalavra);

            if (nProximo == nullptr) {
                cout << "Nenhum resultado." << endl;
                return;
            }

            string intersecaoRodada[200]; 
            int qtdIntersecao = 0;

            for (int i = 0; i < qtdUrlsResultado; i++){
                string urlParaVerificar = resultadoUrls[i];
                bool encontrou = false;
                
                int totalProximo = nProximo->getCount();
                for(int j = 0; j < totalProximo; j++) {
                    if(nProximo->getUrl(j) == urlParaVerificar) {
                        encontrou = true;
                        break;
                    }
                }
                
                if (encontrou && qtdIntersecao < 200) {
                    intersecaoRodada[qtdIntersecao++] = urlParaVerificar;
                }
            }
            
            qtdUrlsResultado = qtdIntersecao;
            for (int i = 0; i < qtdUrlsResultado; i++) {
                resultadoUrls[i] = intersecaoRodada[i];
            }

            if (navValidos.end()) break;
            navValidos.next();
        }
    }

    if (qtdUrlsResultado == 0) {
        cout << "Nenhum resultado." << endl;
        return;
    }

    for (int i = 0; i < qtdUrlsResultado - 1; i++) {
        for (int j = 0; j < qtdUrlsResultado - i - 1; j++) {
            if (resultadoUrls[j] > resultadoUrls[j + 1]) {
                string temp = resultadoUrls[j];
                resultadoUrls[j] = resultadoUrls[j + 1];
                resultadoUrls[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < qtdUrlsResultado; i++) {
        cout << resultadoUrls[i] << endl;
    }
}

//------------------------------------------------------------------------------------------
int main(){
    Ming sistema;

    string stopWords[] = {
        "a", "an", "the", "this", "that", "these", "those", "it", "its", "he", "she", "they", "we", "you", "i", "his", "her", "their", "our", "my",
        "of", "in", "on", "at", "to", "for", "by", "with", "from", "into", "over", "under", "about", "and", "or", "but", "nor", "so", "yet", "as",
        "is", "are", "was", "were", "be", "been", "being", "has", "have", "had", "do", "does", "did", "will", "would", "can", "could", "may", "might", "shall"
    };

    for (const string& sw : stopWords) {
        sistema.carregarStopWord(sw);
    }
    
    int N; 
    if(!(cin >> N)) {
        return 0;
    }
    string linha;
    getline(cin, linha); 

    for(int i = 0; i < N; i++){
        string url = "";
        string conteudoPagina = "";

        while(getline(cin, linha)){
            if(linha.find("<page url=") != string::npos){
                size_t inicio_real = linha.find("\"") + 1;
                size_t fim = linha.find("\"", inicio_real);
                url = linha.substr(inicio_real, fim - inicio_real);
            } else if(linha.find("</page>") != string::npos){  
                break;
            }else if(linha.find("<a href=") != string::npos){ 
                continue;
            }else{
                if(!linha.empty()){
                    if(!conteudoPagina.empty()){
                        conteudoPagina += " ";
                    }
                    conteudoPagina += linha;
                }
            }
        }
        sistema.indexarPagina(url, conteudoPagina);
    }

    string consulta;
    if(getline(cin, consulta)){
        sistema.buscar(consulta);
    } 

    return 0;
}