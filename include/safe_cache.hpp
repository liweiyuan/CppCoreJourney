#ifndef __SAFE_CACHE_HPP__
#define __SAFE_CACHE_HPP__

//线程安全的LRU缓存实现
#include <list>
#include <unordered_map>
#include <mutex>
#include <optional>
// SafeLRUCache 是一个线程安全的LRU（最近最少使用）缓存实现。
// 它使用了一个双向链表（std::list）来维护缓存项的访问顺序，
// 并使用一个哈希表（std::unordered_map）来快速查找缓存项。
// 通过互斥锁（std::mutex）来保证线程安全。
template <typename Key, typename Value>
class SafeLRUCache {
public:
    // 构造函数，初始化缓存容量
    // @param capacity: 缓存的最大容量
    explicit SafeLRUCache(size_t capacity) : capacity_(capacity) {}

    // 获取缓存项的值
    // @param key: 要查找的键
    // @return: 如果找到对应的值，则返回std::optional<Value>，否则返回std::nullopt
    std::optional<Value> get(const Key& key) {
        std::lock_guard<std::mutex> lock(mutex_); // 加锁，保证线程安全
        auto it = cache_map_.find(key); // 在哈希表中查找键
        if (it == cache_map_.end()) {
            return std::nullopt;// 如果未找到，返回空值
        }
        // 将找到的缓存项移动到链表的最前面，表示最近使用
        cache_list_.splice(cache_list_.begin(), cache_list_, it->second);
        return it->second->second;// 返回找到的值
    }

    // 插入或更新缓存项
    // @param key: 要插入或更新的键
    // @param value: 要插入或更新的值
    void put(const Key& key, const Value& value) {
        std::lock_guard<std::mutex> lock(mutex_);  // 加锁，保证线程安全
        auto it = cache_map_.find(key);  // 在哈希表中查找键
        if (it != cache_map_.end()) {
            // 如果键已存在，更新其值并将其移动到链表的最前面
            cache_list_.splice(cache_list_.begin(), cache_list_, it->second);
            it->second->second = value;
            return;
        }
        // 如果缓存已满，移除链表末尾的缓存项（最近最少使用的项）
        if (cache_list_.size() == capacity_) {
            auto last = cache_list_.back();
            cache_map_.erase(last.first);  // 从哈希表中移除
            cache_list_.pop_back();  // 从链表中移除
        }
        // 将新的缓存项插入到链表的最前面，并在哈希表中记录其位置
        cache_list_.emplace_front(key, value);
        cache_map_[key] = cache_list_.begin();
    }

    // 根据Key移除缓存项
    // @param key: 要移除的键
    // @return: 如果找到并移除成功，返回true，否则返回false
    bool remove(const Key& key) {
        std::lock_guard<std::mutex> lock(mutex_);  // 加锁，保证线程安全
        auto it = cache_map_.find(key);  // 在哈希表中查找键
        if (it == cache_map_.end()) {
            return false;  // 如果未找到，返回false
        }
        // 从链表中移除对应的缓存项
        cache_list_.erase(it->second);
        cache_map_.erase(it);  // 从哈希表中移除
        return true;  // 返回true表示移除成功
    }

private:
    size_t capacity_;
    std::list<std::pair<Key, Value>> cache_list_;
    std::unordered_map<Key, typename std::list<std::pair<Key, Value>>::iterator> cache_map_;
    std::mutex mutex_;
};
#endif
