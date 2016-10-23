#ifndef PROCESSOR_H
#define PROCESSOR_H

#include "ComponentLabel.h"
#include <iostream>
#include <string>

class Processor {
private:
  const ComponentLabel m_label;
  const std::string m_brand;
  const unsigned int m_frequency;

public:
  Processor() : m_brand("Intel"), m_frequency(3000) {
    using namespace std;
    cout << "Processor #" << m_label.id << " \"Intel\" 3000 MHz" << endl;
    cout << "    (default parameters)" << endl;
  }

  Processor(const std::string &brand, const unsigned int frequency)
      : m_brand(brand), m_frequency(frequency) {
    std::cout << "Processor #" << m_label.id << " \"" << m_brand << "\" "
              << m_frequency << " MHz" << std::endl;
  }

  Processor(const Processor &other)
      : m_brand(other.m_brand), m_frequency(other.m_frequency) {
    using namespace std;
    cout << "Processor #" << m_label.id << " \"" << m_brand << "\" "
         << m_frequency << " MHz" << endl;
    cout << "    (cloned from Processor #" << other.m_label.id << ")" << endl;
  }

  ~Processor() { std::cout << "~Processor #" << m_label.id << std::endl; }

  unsigned long id() const { return m_label.id; }

  const std::string &brand() const { return m_brand; }

  unsigned int frequency() const { return m_frequency; }
};

#endif // PROCESSOR_H
