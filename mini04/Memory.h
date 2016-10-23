#ifndef MEMORY_H
#define MEMORY_H

#include "ComponentLabel.h"
#include <iostream>
#include <string>

class Memory {
private:
  const ComponentLabel m_label;
  const unsigned int m_capacity;

public:
  Memory() : m_capacity(1) {
    using namespace std;
    cout << "Memory #" << m_label.id << " 1 GB" << endl;
    cout << "    (default parameters)" << endl;
  }

  Memory(const unsigned int capacity) : m_capacity(capacity) {
    std::cout << "Memory #" << m_label.id << " " << m_capacity << " GB"
              << std::endl;
  }

  Memory(const Memory &other) : m_capacity(other.m_capacity) {
    using namespace std;
    cout << "Memory #" << m_label.id << " " << m_capacity << " GB" << endl;
    cout << "    (cloned from Memory #" << other.m_label.id << ")" << endl;
  }

  ~Memory() { std::cout << "~Memory #" << m_label.id << std::endl; }

  unsigned long id() const { return m_label.id; }

  unsigned int capacity() const { return m_capacity; }
};

#endif // MEMORY_H
