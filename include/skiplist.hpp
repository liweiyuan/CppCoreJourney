#pragma
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>

template <typename T> class SkipList {
  private:
    struct Node {
        T key;
        Node *next;                // 后继指针
        Node *down;                // 下降指针
        std::vector<Node *> nexts; // 指向不同层级的下一个节点

        Node(const T &data, int level)
            : key(data), next(nullptr), down(nullptr), nexts(level, nullptr) {}
    };

    Node *head;
    int level; // 层数
    double p;  // 概率因子

    int randomLevel() {
        int l = 1;
        while (rand() / double(RAND_MAX) < p && l < level) {
            l++;
        }
        return l;
    }

  public:
    SkipList(int level = 16, double p = 0.5) : level(level), p(p) {
        head = new Node(T(), level); // 创建头节点，键值为空
    }

    ~SkipList() {
        // 释放内存
        Node *current = head;
        while (current != nullptr) {
            Node *next = current->nexts[0];
            delete current;
            current = next;
        }
    }

    // 插入键值对
    void insert(T key) {
        std::vector<Node *> update(level); // 用于存储每层需要更新的节点
        Node *current = head;

        // 找到每层需要更新的节点
        for (int i = level - 1; i >= 0; i--) {
            while (current->nexts[i] != nullptr &&
                   current->nexts[i]->key < key) {
                current = current->nexts[i];
            }
            update[i] = current;
        }

        // 生成随机层数
        int l = randomLevel();

        // 创建新节点
        Node *newNode = new Node(key, l);

        // 更新每层的指针
        for (int i = 0; i < l; i++) {
            newNode->nexts[i] = update[i]->nexts[i];
            update[i]->nexts[i] = newNode;
            if (i > 0) {
                newNode->nexts[i - 1]->down = newNode;
            }
        }
    }

    // 查找键
    bool search(T key) {
        Node *current = head;

        for (int i = level - 1; i >= 0; i--) {
            while (current->nexts[i] != nullptr &&
                   current->nexts[i]->key < key) {
                current = current->nexts[i];
            }
            if (current->nexts[i] != nullptr && current->nexts[i]->key == key) {
                return true;
            }
        }

        return false;
    }

    // 打印 skiplist
    void print() {
        for (int i = level - 1; i >= 0; i--) {
            std::cout << "Level " << i << ": ";
            Node *current = head->nexts[i];
            while (current != nullptr) {
                std::cout << current->key << " ";
                current = current->nexts[i];
            }
            std::cout << std::endl;
        }
    }
};
