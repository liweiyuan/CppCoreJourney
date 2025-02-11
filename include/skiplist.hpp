#pragma
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <limits> // Required for numeric_limits
#include <vector>

template <typename T> class SkipList {
  private:
    struct Node {
        T key;
        std::vector<Node *> next;

        Node(const T &key, int level) : key(key), next(level, nullptr) {}
    };

    Node *head;
    int level;
    double p;

    int randomLevel() {
        int l = 1;
        while (static_cast<double>(rand()) / RAND_MAX < p && l < level) {
            l++;
        }
        return l;
    }

  public:
    SkipList(int maxLevel = 16, double probability = 0.5)
        : level(maxLevel), p(probability) {
        head = new Node(std::numeric_limits<T>::min(),
                        level); // 使用最小可能值作为头节点键值
    }

    ~SkipList() {
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->next[0];
            delete current;
            current = next;
        }
    }

    void insert(const T &key) {
        std::vector<Node *> update(level);
        Node *current = head;

        for (int i = level - 1; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->key < key) {
                current = current->next[i];
            }
            update[i] = current;
        }

        int l = randomLevel();

        if (l > level) { // 正确处理层数增加的情况
            for (int i = level; i < l; ++i) {
                update[i] = head;
            }
            level = l;
        }

        Node *newNode = new Node(key, l);

        for (int i = 0; i < l; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }

    bool search(const T &key) const { // const correctness
        Node *current = head;

        for (int i = level - 1; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->key < key) {
                current = current->next[i];
            }
            if (current->next[i] != nullptr && current->next[i]->key == key) {
                return true;
            }
        }

        return false;
    }

    void print() const { // const correctness
        for (int i = level - 1; i >= 0; i--) {
            std::cout << "Level " << i << ": ";
            Node *current = head->next[i];
            while (current != nullptr) {
                std::cout << current->key << " ";
                current = current->next[i];
            }
            std::cout << std::endl;
        }
    }
};
