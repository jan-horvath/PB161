#ifndef COMPUTER_H
#define COMPUTER_H

#include "ComponentLabel.h"
#include "DiskDrive.h"
#include "GraphicsCard.h"
#include "Memory.h"
#include "Processor.h"
#include <iostream>

class PersonalComputer {
private:
  const ComponentLabel m_label;
  const DiskDrive m_root;
  const DiskDrive m_home;
  const GraphicsCard m_graphicsCard;
  const Memory m_memory;
  const Processor m_processor;
  const std::string m_brand;

public:
  PersonalComputer()
      : m_root(), m_home(), m_graphicsCard(), m_memory(), m_processor(),
        m_brand("GenericPC") {
    using namespace std;
    cout << "PersonalComputer #" << m_label.id << " \"GenericPC\"" << endl;
    cout << "    (default parameters)" << endl;
  }

  PersonalComputer(const Memory &memory, const GraphicsCard &gpu,
                   const DiskDrive &home_drive, const DiskDrive &root_drive,
                   const Processor &processor, const std::string &name)
      : m_root(root_drive), m_home(home_drive), m_graphicsCard(gpu),
        m_memory(memory), m_processor(processor) {
    using namespace std;
    cout << "PersonalComputer #" << m_label.id << " \"" << name << "\"" << endl;
    cout << "    (custom components)" << endl;
  }

  PersonalComputer(const PersonalComputer &other)
      : m_root(other.m_root), m_home(other.m_home),
        m_graphicsCard(other.m_graphicsCard), m_memory(other.m_memory),
        m_processor(other.m_processor), m_brand(other.m_brand) {
    using namespace std;
    cout << "PersonalComputer #" << m_label.id << " \"" << m_brand << "\""
         << endl;
    cout << "    (cloned from PersonalComputer #" << other.m_label.id << ")"
         << endl;
  }

  ~PersonalComputer() {
    std::cout << "~PersonalComputer #" << m_label.id << std::endl;
  }

  unsigned long id() const { return m_label.id; }

  const std::string &brand() const { return m_brand; }

  const Memory &memory() const { return m_memory; }

  const DiskDrive &root() const { return m_root; }

  const DiskDrive &home() const { return m_home; }

  const GraphicsCard &graphicsCard() const { return m_graphicsCard; }

  const Processor &processor() const { return m_processor; }
};

#endif // COMPUTER_H
