#ifndef GRAPHICSCARD_H
#define GRAPHICSCARD_H

#include "ComponentLabel.h"
#include "Memory.h"
#include <iostream>
#include <string>

class GraphicsCard {
private:
  const ComponentLabel m_label;
  const Memory m_memory;

public:
  GraphicsCard() : m_memory() {
    using namespace std;
    cout << "GraphicsCard #" << m_label.id << " 1 GB" << endl;
    cout << "    (default parameters)" << endl;
  }

  GraphicsCard(const unsigned int capacity) : m_memory(capacity) {
    using namespace std;
    cout << "GraphicsCard #" << m_label.id << " " << m_memory.capacity()
         << " GB" << endl;
  }

  GraphicsCard(const Memory &memory) : m_memory(memory) {
    using namespace std;
    cout << "GraphicsCard #" << m_label.id << " " << m_memory.capacity()
         << " GB" << endl;
    cout << "    (using Memory #" << memory.id() << ")" << endl;
  }

  GraphicsCard(const GraphicsCard &other) : m_memory(other.m_memory) {
    using namespace std;
    cout << "GraphicsCard #" << m_label.id << " " << m_memory.capacity()
         << " GB" << endl;
    cout << "    (cloned from GraphicsCard #" << other.m_label.id << ")"
         << endl;
  }

  ~GraphicsCard() { std::cout << "~GraphicsCard #" << m_label.id << std::endl; }

  unsigned long id() const { return m_label.id; }

  const Memory &memory() const { return m_memory; }
};

#endif // GRAPHICSCARD_H
