#ifndef NETWORKATTACHEDSTORAGE_H
#define NETWORKATTACHEDSTORAGE_H

#include "ComponentLabel.h"
#include "DiskDrive.h"
#include "Memory.h"
#include "Processor.h"
#include <iostream>
#include <vector>

class NetworkAttachedStorage {
private:
  const ComponentLabel m_label;
  const std::vector<DiskDrive> m_diskDrives;
  const Memory m_memory;
  const Processor m_processor;
  const std::string m_brand;

public:
  NetworkAttachedStorage()
      : m_diskDrives(10, DiskDrive()), m_memory(), m_processor(),
        m_brand("GenericNAS") {
    using namespace std;
    cout << "NetworkAttachedStorage #" << m_label.id << " \"GenericNAS\""
         << endl;
    cout << "    (default parameters)" << endl;
  }

  NetworkAttachedStorage(const Processor &processor, const Memory &memory,
                         const DiskDrive &diskDrive, const int num,
                         const std::string &brand)
      : m_diskDrives(num, diskDrive), m_memory(memory), m_processor(processor),
        m_brand(brand) {
    using namespace std;
    cout << "NetworkAttachedStorage #" << m_label.id << " \"" << m_brand << "\""
         << endl;
    cout << "    (custom components)" << endl;
  }

  NetworkAttachedStorage(const NetworkAttachedStorage &other)
      : m_diskDrives(other.m_diskDrives), m_memory(other.m_memory),
        m_processor(other.m_processor), m_brand(other.m_brand) {
    using namespace std;
    cout << "NetworkAttachedStorage #" << m_label.id << " \"" << m_brand << "\""
         << endl;
    cout << "    (cloned from NetworkAttachedStorage #" << other.m_label.id
         << ")" << endl;
  }

  ~NetworkAttachedStorage() {
    std::cout << "NetworkAttachedStorage #" << m_label.id << std::endl;
  }

  unsigned long id() const { return m_label.id; }

  const std::string &brand() const { return m_brand; }

  const Processor &processor() const { return m_processor; };

  const Memory &memory() const { return m_memory; }

  const std::vector<DiskDrive> &drives() const { return m_diskDrives; }
};

#endif // NETWORKATTACHEDSTORAGE_H
