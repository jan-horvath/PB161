//
// Created by Jan Horvath on 16-Dec-16.
//

#ifndef HW04_HASH_TABLE_H
#define HW04_HASH_TABLE_H

#include <functional>
#include <vector>
#include <cassert>
#include "bucket.h"

template <typename Key, typename Value>
struct HashTableEntry {
 private:
  Bucket<Value> entryValue;
  Key entryKey;

 public:
  HashTableEntry() : entryValue(), entryKey() {}
  HashTableEntry(const Key& key) : entryValue(), entryKey(key) {}
  HashTableEntry(const Key& key, const Value& value)
      : entryValue(value), entryKey(key) {}
  const Value& getEntryValue() const { return *entryValue; }
  Value& getEntryValue() { return *entryValue; }
  void setEntryvalue(const Value& newValue) { entryValue = newValue; }
  void zombify() { entryValue.zombify(); }
  HashTableEntry<Key, Value>& operator=(
      const HashTableEntry<Key, Value> other) {
    entryValue = other.entryValue;
    entryKey = other.getEntryKey();
    return *this;
  };
  bool isEmpty() const { return (entryValue.empty()); }
  bool isZombie() const { return entryValue.zombie(); }
  const Key& getEntryKey() const { return entryKey; }
};

template <typename Key,
          typename Value,
          typename KeyHash = std::hash<Key>,
          typename KeyEqual = std::equal_to<Key>>
struct HashTable {
 private:
  std::vector<HashTableEntry<Key, Value>> entries;
  size_t entriesCount;
  size_t zombieCount;
  float maxLoadFactor;
  float maxZombieFactor;
  KeyHash keyHasher;
  KeyEqual keyComparator;

  // returns nullptr if not found and saves first empty position found into
  // "from"
  // if no empty position was found, saves count() into "from"
  HashTableEntry<Key, Value>* searchKeyInTable(unsigned& from, const Key& key) {
    unsigned begin = from;
    unsigned position = from;
    while (position != count() && !entries.at(position).isEmpty()) {
      from = position;
      if (keyComparator(entries.at(position).getEntryKey(), key))
        return &(entries.at(position));
      position++;
    }
    if (position == count()) {  // reached the end of array
      position = 0;
      while (position != begin && !entries.at(position).isEmpty()) {
        from = position;
        if (entries.at(position).getEntryKey() == key)
          return &(entries.at(position));
        position++;
      }
      if (position != begin) {
        from = position;
        return nullptr;
      }
    } else {  // found empty
      from = position;
      return nullptr;
    }
    from = count();  // if the value nor an empty slot was found
    return nullptr;
  }

  const HashTableEntry<Key, Value>* searchKeyInTable(unsigned& from,
                                                     const Key& key) const {
    unsigned begin = from;
    unsigned position = from;
    while (position != count() && !entries.at(position).isEmpty()) {
      from = position;
      if (keyComparator(entries.at(position).getEntryKey(), key))
        return &(entries.at(position));
      position++;
    }
    if (position == count()) {
      position = 0;
      while (position != from && !entries.at(position).isEmpty()) {
        from = position;
        if (entries.at(position).getEntryKey() == key)
          return &(entries.at(position));
        position++;
      }
      if (position != begin) {
        from = position;
        return nullptr;
      }
    } else {  // found empty
      from = position;
      return nullptr;
    }
    from = count();  // if the value nor an empty slot was found
    return nullptr;
  }

  // returns index of first zombie slot between from and to
  // if not found, returns to
  unsigned searchForZombies(unsigned from, unsigned to) {
    unsigned positionTo;
    if (to < from)
      positionTo = count();
    else
      positionTo = to;
    for (unsigned i = from; i < positionTo; ++i) {
      if (entries.at(i).isZombie())
        return i;
    }
    if (positionTo == count())
      positionTo = to;
    else
      return to;
    for (unsigned i = 0; i < to; ++i) {
      if (entries.at(i).isZombie())
        return i;
    }
    return to;
  };

 public:
  HashTable()
      : entries(5),
        entriesCount(0),
        zombieCount(0),
        maxLoadFactor(static_cast<float>(2) / 3),
        maxZombieFactor(static_cast<float>(1) / 4),
        keyHasher(),
        keyComparator() {}

  HashTable(const HashTable& other)
      : entries(other.entries),
        entriesCount(other.entriesCount),
        zombieCount(other.zombieCount),
        maxLoadFactor(other.maxLoadFactor),
        maxZombieFactor(other.maxZombieFactor),
        keyHasher(),
        keyComparator() {}

  void swap(HashTable& other) {
    auto tmp = *this;
    *this = other;
    other = tmp;
  }
  Value& operator[](const Key& key) {
    unsigned entryPosition = keyHasher(key) % count();
    HashTableEntry<Key, Value>* entryPtr = searchKeyInTable(entryPosition, key);
    if (entryPtr == nullptr) {
      insert(key, Value());
      entryPosition = keyHasher(key) % count();
      return searchKeyInTable(entryPosition, key)->getEntryValue();
    }
    return entryPtr->getEntryValue();
  };
  Value& at(const Key& key) {
    unsigned entryPosition = keyHasher(key) % count();
    HashTableEntry<Key, Value>* entryPtr = searchKeyInTable(entryPosition, key);
    if (entryPtr == nullptr) {
      throw std::out_of_range("Key not found in table!");
    }
    return entryPtr->getEntryValue();
  }

  const Value& at(const Key& key) const {
    unsigned entryPosition = keyHasher(key) % count();
    const HashTableEntry<Key, Value>* entryPtr =
        searchKeyInTable(entryPosition, key);
    if (entryPtr == nullptr) {
      throw std::out_of_range("Key not found in table!");
    }
    return entryPtr->getEntryValue();
  }

  bool insert(const Key& key, const Value& value) {
    if (load_factor() + static_cast<float>(1) / count() > maxLoadFactor)
      rehash(count() * 2);
    unsigned entryPosition = keyHasher(key) % count();
    if (searchKeyInTable(entryPosition, key) == nullptr) {  // key not found
      if (entryPosition != count()) {  // entryPosition = nearest empty slot
        unsigned saveAt =
            searchForZombies(keyHasher(key) % count(), entryPosition);
        entries[saveAt] = HashTableEntry<Key, Value>(key, value);
        if (saveAt != entryPosition)
          --zombieCount;
      } else {  // empty slot not found, only zombies and occupied are present
                // in table
        entries.at(searchForZombies(keyHasher(key) % count(),
                                    keyHasher(key) % count() - 1)) =
            HashTableEntry<Key, Value>(key, value);
        --zombieCount;
      }
      ++entriesCount;
      return true;
    }  // key found
    return false;
  }

  bool contains(const Key& key) const {
    unsigned entryPosition = keyHasher(key) % count();
    return searchKeyInTable(entryPosition, key) != nullptr;
  }

  bool remove(const Key& key) {
    if (zombie_factor() > maxZombieFactor)
      rehash();
    unsigned entryPosition = keyHasher(key) % count();
    if (searchKeyInTable(entryPosition, key) == nullptr)
      return false;
    // entry position is the index where key was found
    entries.at(entryPosition) = HashTableEntry<Key, Value>();
    entries.at(entryPosition).zombify();
    --entriesCount;
    ++zombieCount;
    return true;
  }

  void rehash(std::size_t count) {
    if (static_cast<float>(entriesCount) / count >= maxLoadFactor) {
      rehash(static_cast<float>(size()) / maxLoadFactor + 0.5);  // round up
      return;
    }
    std::vector<HashTableEntry<Key, Value>> rehashedEntries(count);
    for (unsigned i = 0; i < this->count();
         ++i) {                        // go through all old entries
      if (!entries.at(i).isEmpty()) {  // if contains any value, rehash it
        unsigned newEntryPosition =
            keyHasher(entries.at(i).getEntryKey()) % count;
        // this position may be taken, so we need to find nearest empty slot
        // key should never appear in the table when rehashing, since the old
        // table had no duplicates
        // assert(searchKeyInTable(newEntryPosition, .at(i).getEntryKey()) ==
        // nullptr);
        rehashedEntries[newEntryPosition] = entries.at(i);
      }
    }
    entries = rehashedEntries;
    zombieCount = 0;
  }

  void rehash() { rehash(count()); }

  size_t count() const { return entries.size(); }

  size_t size() const { return entriesCount; }

  bool empty() const { return entriesCount == 0; }

  float load_factor() const {
    return static_cast<float>(entriesCount) / count();
  }

  float max_load_factor() const { return maxLoadFactor; }

  void max_load_factor(float value) {
    maxLoadFactor = value;
    if (load_factor() > maxLoadFactor) {
      rehash(size() / value);
    }
  }

  float zombie_factor() const {
    return static_cast<float>(zombieCount) / count();
  }

  float max_zombie_factor() const { return maxZombieFactor; }

  void zombie_factor(float value) {
    maxZombieFactor = value;
    if (zombie_factor() > maxZombieFactor) {
      rehash();
    }
  }

  const std::vector<HashTableEntry<Key, Value>>& getEntries() const {
    return entries;
  }
};

#endif  // HW04_HASH_TABLE_H
