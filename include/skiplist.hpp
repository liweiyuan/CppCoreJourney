#ifndef __SKIPLIST_HPP__
#define __SKIPLIST_HPP__
#pragma once
#include <ctime>
#include <iostream>
#include <limits> // Required for numeric_limits
#include <memory>
#include <mutex>
#include <random>       // 用于更好的随机数生成
#include <shared_mutex> // 用于线程安全
#include <vector>

// 定义一个泛型类 SkipList，用于存储类型 T 的元素。
template <typename T> class SkipList {
  private:
    struct Node {
        T key;
        std::vector<std::shared_ptr<Node>>
            next; // 指向不同层次的下一个节点的指针。

        Node(const T &key, int level) : key(key), next(level, nullptr) {}
    };

    std::shared_ptr<Node> head;
    int level;
    double p;
    std::mt19937 gen;                           // 随机数生成器
    std::uniform_real_distribution<double> dis; // 均匀分布
    mutable std::shared_mutex mtx;
    // 用于线程安全
    int randomLevel() {
        int l = 1;
        while (dis(gen) < p && l < level) {
            l++;
        }
        return l;
    }

  public:
    SkipList(int maxLevel = 16, double probability = 0.5)
        : level(maxLevel), p(probability), gen(std::random_device{}()),
          dis(0.0, 1.0) {
        head = std::make_shared<Node>(std::numeric_limits<T>::min(),
                                      level); // 使用最小可能值作为头节点键值
    }

    void insert(const T &key) {
        std::lock_guard<std::shared_mutex> lock(mtx); // 线程安全
        std::vector<std::shared_ptr<Node>> update(level);
        auto current = head;

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

        auto newNode = std::make_shared<Node>(key, l);

        for (int i = 0; i < l; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }
    }

    bool search(const T &key) const {                  // const correctness
        std::shared_lock<std::shared_mutex> lock(mtx); // 共享锁，用于读操作
        auto current = head;

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

    void remove(const T &key) {
        std::unique_lock<std::shared_mutex> lock(mtx); // 独占锁，用于写操作
        std::vector<std::shared_ptr<Node>> update(level);
        auto current = head;

        for (int i = level - 1; i >= 0; i--) {
            while (current->next[i] != nullptr && current->next[i]->key < key) {
                current = current->next[i];
            }
            update[i] = current;
        }

        current = current->next[0];
        if (current != nullptr && current->key == key) {
            for (int i = 0; i < level; i++) {
                if (update[i]->next[i] != current) {
                    break;
                }
                update[i]->next[i] = current->next[i];
            }
            // 调整最大层数
            while (level > 1 && head->next[level - 1] == nullptr) {
                level--;
            }
        }
    }

    void print() const { // const correctness
        for (int i = level - 1; i >= 0; i--) {
            std::cout << "Level " << i << ": ";
            auto current = head->next[i];
            while (current != nullptr) {
                std::cout << current->key << " ";
                current = current->next[i];
            }
            std::cout << std::endl;
        }
    }
};

#endif
