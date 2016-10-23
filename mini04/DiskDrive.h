#ifndef DISKDRIVE_H
#define DISKDRIVE_H

#include "ComponentLabel.h"
#include <iostream>
#include <string>

class DiskDrive {
private:
  const ComponentLabel m_label;
  const unsigned int m_capacity;
  const bool m_isSSD;

public:
  DiskDrive() : m_capacity(256), m_isSSD(true) {
    using namespace std;
    cout << "DiskDrive #" << m_label.id << " 256 GB, SSD" << endl;
    cout << "    (default parameters)" << endl;
  }

  DiskDrive(const unsigned int capacity, const bool isSSD)
      : m_capacity(capacity), m_isSSD(isSSD) {
    using namespace std;
    cout << "DiskDrive #" << m_label.id << " " << m_capacity << " GB";
    if (m_isSSD) {
      cout << ", SSD";
    }
    cout << endl;
  }

  DiskDrive(const DiskDrive &other)
      : m_capacity(other.m_capacity), m_isSSD(other.m_isSSD) {
    using namespace std;
    cout << "DiskDrive #" << m_label.id << " " << m_capacity << " GB";
    if (m_isSSD) {
      cout << ", SSD";
    }
    cout << endl;
    cout << "    (cloned from DiskDrive #" << other.m_label.id << ")" << endl;
  }

  ~DiskDrive() { std::cout << "~DiskDrive #" << m_label.id << std::endl; }

  unsigned long id() const { return m_label.id; }

  unsigned int capacity() const { return m_capacity; }

  bool isSSD() const { return m_isSSD; }
};

#endif // DISKDRIVE_H
