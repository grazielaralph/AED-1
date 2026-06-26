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
            p->item = x;
        } else if (x.key < p->item.key)
            insert(x, p->left);
        else if (x.key > p->item.key)
            insert(x, p->right);
        else
            std::cout << "Erro: item ja existe na BST\n";
    }

public:
    BST() : root(nullptr) {}
    void insert(const Item<T>& x) { insert(x, root); }

    int maxLevelSum() {
        if (root == nullptr) return 0;

        Node<T>* queue[64];
        int head = 0, tail = 0;
        queue[tail++] = root;

        int bestSum = root->item.key;

        while (head < tail) {
            int levelSize = tail - head;
            int levelSum = 0;
            for (int i = 0; i < levelSize; i++) {
                Node<T>* cur = queue[head++];
                levelSum += cur->item.key;
                if (cur->left)  queue[tail++] = cur->left;
                if (cur->right) queue[tail++] = cur->right;
            }
            if (levelSum > bestSum)
                bestSum = levelSum;
        }
        return bestSum;
    }
};

int main() {
    int n; std::cin >> n;
    BST<int> t;
    for (int i = 0; i < n; i++) {
        Item<int> x;
        std::cin >> x.key;
        t.insert(x);
    }
    std::cout << t.maxLevelSum() << "\n";
    return 0;
}