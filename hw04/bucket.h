//
// Created by Jan Horvath on 16-Dec-16.
//

#ifndef HW04_BUCKET_H
#define HW04_BUCKET_H

#include <memory>

enum State { empty, zombie, occupied };

template <typename T>
struct Bucket {
 private:
  std::unique_ptr<T> m_value;
  State m_state;

 public:
  Bucket() : m_state(State::empty) {}
  Bucket(const T& data) : m_state(State::occupied) {
    m_value = std::make_unique<T>(data);
  }
  Bucket(const Bucket<T>& other) : m_state(other.m_state) {
    if (occupied()) {
      m_value = std::make_unique<T>(*other.m_value);
    }
  }
  Bucket& operator=(const Bucket& other) {
    if (occupied()) {
      m_value.reset(nullptr);
    }
    if (other.occupied()) {
      m_value = std::make_unique<T>(*other.m_value);
    }
    m_state = other.m_state;
    return *this;
  }
  Bucket& operator=(const T& data) {
    if (occupied()) {
      m_value.reset(nullptr);
    }
    m_state = State::occupied;
    m_value = std::make_unique<T>(data);
    return *this;
  }
  bool empty() const { return (m_state == State::empty); }
  bool zombie() const { return (m_state == State::zombie); }
  bool occupied() const { return (m_state == State::occupied); }
  void zombify() {
    if (occupied()) {
      m_value.reset(nullptr);
    }
    m_state = State::zombie;
  }
  T& operator*() {
    if (!occupied())
      throw std::logic_error("Bucket has no value stored!");
    return *m_value;
  }
  const T& operator*() const {
    if (!occupied())
      throw std::logic_error("Bucket has no value stored!");
    return *m_value;
  }
  T* operator->() {
    if (!occupied())
      return nullptr;
    return m_value.get();
  }
  const T* operator->() const {
    if (!occupied())
      return nullptr;
    return m_value.get();
  }
};

#endif  // HW04_BUCKET_H
