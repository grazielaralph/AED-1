#include <iostream>

template <typename T>
struct Item {
    T key;
};

template <typename T>
struct Node {
    Item<T> item;
    Node<T> *left, *right;
};

template <typename T>
class BST {
    Node<T>* root;

    void insert(const Item<T>& x, Node<T>*& p) {
        if (p == nullptr) {
            p = new Node<T>();
            p->left = p->right = nullptr;
            p->item = x; }
        else if (x.key < p->item.key)
            insert(x, p->left);
        else if (x.key > p->item.key)
            insert(x, p->right);
        else
            std::cout << "Erro: item ja existe na BST\n";
    }

public:
    BST() : root(nullptr) {}
    void insert(const Item<T>& x) { insert(x, root); }

    // troca p->left por p->right
    int max() {
        Node<T>* p = root;
        while (p->right != nullptr)
            p = p->right;
        return p->item.key;
    }
};

int main() {
    int n; std::cin >> n;
    BST<int> t;
    for (int i=0; i<n; i++){
        Item<int> x;
        std::cin >> x.key;
        t.insert(x); }
    std::cout << t.max() << "\n";
    return 0;
}