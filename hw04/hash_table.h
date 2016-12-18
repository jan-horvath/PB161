//
// Created by Jan Horvath on 16-Dec-16.
//

#ifndef HW04_HASH_TABLE_H
#define HW04_HASH_TABLE_H

#include <functional>
#include <vector>
#include <cassert>
#include "bucket.h"

template <typename Key, typename Value> struct HashTableEntry {
private:
    Bucket<Value> entryValue;
public:
    const Key entryKey;

    HashTableEntry() : entryValue(), entryKey() {}
    HashTableEntry(const Key &key) : entryValue(), entryKey(key) {}
    HashTableEntry(const Key &key, const Value &value) : entryKey(key), entryValue(value) {}
    const Value& getEntryValue() const {return *entryValue;}
    void setEntryvalue(const Value& newValue) {entryValue = newValue;}
    void zombify() {
        entryValue.zombify();
    }
    bool isEmpty() const {return (entryValue.empty());}
};

template <typename Key, typename Value, typename KeyHash = std::hash<Key>, typename KeyEqual = std::equal_to<Key>>
struct HashTable {
private:
    std::vector<HashTableEntry<Key, Value>> entries;
    size_t entriesCount;
    size_t zombieCount;
    float maxLoadFactor;
    float maxZombieFactor;
    KeyHash keyHasher;
    KeyEqual keyComparator;

    //returns nullptr if not found and saves first empty position found into "from"
    HashTableEntry<Key, Value>* searchKeyInTable(unsigned &from, const Key &key) {
        unsigned position = from;
        while (position != entries.size() && !entries.at(position).isEmpty()) {
            if (keyComparator(entries.at(position).entryKey,key)) return &(entries.at(position));
            position++;
        }
        if (position == entries.size()) {
            position = 0;
            while (position != from && !entries.at(position).isEmpty()) {
                if (entries.at(position).entryKey == key) return &(entries.at(position));
                position++;
            }
        }
        from = position;
        return nullptr;
    }

    const HashTableEntry<Key, Value>* searchKeyInTable(unsigned &from, const Key &key) const {
        unsigned position = from;
        while (position != entries.size() && !entries.at(position).isEmpty()) {
            if (keyComparator(entries.at(position).entryKey,key)) return &(entries.at(position));
            position++;
        }
        if (position == entries.size()) {
            position = 0;
            while (position != from && !entries.at(position).isEmpty()) {
                if (entries.at(position).entryKey == key) return &(entries.at(position));
                position++;
            }
        }
        from = position;
        return nullptr;
    }

public:
    HashTable() : entries(10), entriesCount(0), zombieCount(0), maxLoadFactor(0.666),
                  maxZombieFactor(0.25) {}

    HashTable(const HashTable &other) : maxLoadFactor(other.maxLoadFactor), zombieCount(other.zombieCount),
                                        maxZombieFactor(other.maxZombieFactor), entries(other.entries) {}
    /*
    HashTable& operator=(const HashTable &other) {
        maxZombieFactor = other.maxZombieFactor;
        maxLoadFactor = other.maxLoadFactor;
        loadFactor = other.loadFactor;
        zombieFactor = other.zombieFactor;
        entries = other.entries;
        return *this;
    }
    */

    void swap(HashTable& other) {
        auto tmp = *this;
        *this = other;
        other = tmp;
    }
    Value& operator[](const Key& key) {
        unsigned entryPosition = keyHasher(key) % entries.size();
        HashTableEntry<Key, Value> *entryPtr = searchKeyInTable(entryPosition, key);
        if (entryPtr == nullptr) {
            insert(key, Value());
            return entries.at(entryPosition).getEntryValue();
        }
        return *entryPtr;
    };
    Value& at(const Key& key) {
        unsigned entryPosition = keyHasher(key) % entries.size();
        HashTableEntry<Key, Value> *entryPtr = searchKeyInTable(entryPosition, key);
        if (entryPtr == nullptr) {
            throw std::out_of_range("Key not found in table!");
        }
        return *entryPtr;
    }

    const Value& at(const Key& key) const {
        unsigned entryPosition = keyHasher(key) % entries.size();
        const HashTableEntry<Key, Value> *entryPtr = searchKeyInTable(entryPosition, key);
        if (entryPtr == nullptr) {
            throw std::out_of_range("Key not found in table!");
        }
        return *entryPtr;
    }

    bool insert(const Key& key, const Value& value) {
        unsigned entryPosition = keyHasher(key) % entries.size();
        if (searchKeyInTable(entryPosition, key) == nullptr) { //if key not present in entries
            entries.at(entryPosition) = HashTableEntry<Key, Value>(key, value);
            ++entriesCount;
            if (load_factor() > maxLoadFactor) rehash(entries.size()*2);
            return true;
        }
        return false;
    }

    bool contains(const Key &key) const {
        return searchKeyInTable(keyHasher(key) % entries.size(), key) != nullptr;
    }

    bool remove(const Key& key) {
        unsigned entryPosition = keyHasher(key) % entries.size();
        if (searchKeyInTable(entryPosition, key) == nullptr) return false;
        entries.at(entryPosition) = HashTableEntry<Key, Value>();
        entries.at(entryPosition).zombify();
        entriesCount--;
        zombieCount++;
        return true;
    }

    void rehash(std::size_t count) {
        if (entriesCount/count >= maxLoadFactor) rehash(entries.size()/maxLoadFactor);
        std::vector<HashTableEntry<Key, Value>> rehashedEntries(count);
        for (unsigned i; i < entries.size(); ++i) { //go through all old entries
            if (!entries.at(i).isEmpty()) { //if contains any value, rehash it
                unsigned newEntryPosition = keyHasher(entries.at(i).entryKey) % count;
                //this position may be taken, so we need to find nearest empty slot
                //key should never appear in the table when rehashing, since the old table had no duplicates
                assert(searchKeyInTable(newEntryPosition, entries.at(i).entryKey) == nullptr);
                rehashedEntries.at(newEntryPosition) = entries.at(i);
            }
        }
        entries = rehashedEntries;
    }

    void rehash() {rehash(entries.size());}

    size_t count() {return entries.size();}

    size_t size() { return entriesCount;}

    bool empty() const {return entriesCount == 0;}

    float load_factor() const { return entriesCount/entries.size();}

    void max_load_factor(float value) {
        maxLoadFactor = value;
        if (load_factor() > maxLoadFactor) {
            rehash(size()/value);
        }
    }

    float zombie_factor() const { return zombieCount/entries.size();}

    float max_zombie_factor() const { return maxZombieFactor;}

    void zombie_factor(float value) {
        maxZombieFactor = value;
        if (zombie_factor() > maxZombieFactor) {
            rehash();
        }
    }
};

#endif //HW04_HASH_TABLE_H
