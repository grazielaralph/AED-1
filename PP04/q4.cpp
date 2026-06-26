#include <iostream>
#include <string>

struct Reading {
    int value = 0;
    std::string category = "";
};

template<typename T>
class Node {
public:
    T item;
    Node<T>* next;
    Node(): next(nullptr) {}
    Node(T item): item(item), next(nullptr) {}
};

template<typename T>
class ListNavigator {
private:
    Node<T>* current;
public:
    ListNavigator(Node<T>* start): current(start) {}
    bool end() { return current == nullptr; }
    void next() { current = current->next; }
    bool getCurrentItem(T& item) {
        if (current == nullptr) return false;
        item = current->item;
        return true;
    }
};

template<typename T>
class SinglyLinkedList {
private:
    Node<T>* first = nullptr;
    Node<T>* last  = nullptr;
    int length = 0;
    void succ(Node<T>*& p) { p = p->next; }
public:
    // first é nó sentinela; last aponta para o último nó real (ou first se vazio)
    SinglyLinkedList() { first = new Node<T>{}; last = first; length = 0; }
    bool empty() { return length == 0; }
    void insert(T item) { last->next = new Node<T>(item); succ(last); length++; }
    ListNavigator<T> get_ListNavigator() const { return ListNavigator<T>{first->next}; }
};

class HashTable {
private:
    SinglyLinkedList<Reading>* table;
    int M;
    int hash(int c) const { return c % M; }
public:
    HashTable(int m): M(m) { table = new SinglyLinkedList<Reading>[M]; }

    void insert(int value, std::string category) {
        int bucket = hash(value);
        Reading r;
        r.value = value;
        r.category = category;
        table[bucket].insert(r);
    }

    std::string search(int value) {
        int bucket = hash(value);
        auto nav = table[bucket].get_ListNavigator();
        while (!nav.end()) {
            Reading r;
            nav.getCurrentItem(r);
            if (r.value == value)
                return r.category;
            nav.next();
        }
        return "Nao encontrada";
    }
};

int main() {
    int M, n; std::cin >> M >> n;
    HashTable h(M);
    for (int i = 0; i < n; i++) {
        int c; std::string cat; std::cin >> c >> cat;
        h.insert(c, cat);
    }
    int q; std::cin >> q;
    for (int i = 0; i < q; i++) {
        int c; std::cin >> c;
        std::cout << h.search(c) << "\n";
    }
    return 0;
}