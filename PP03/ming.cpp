#include <iostream>
using namespace std;

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