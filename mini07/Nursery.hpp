#ifndef NURSERY_HPP
#define NURSERY_HPP

#include <memory>  // std::unique_ptr
#include <string>  // std::string
#include "Species.cpp"

class Pokemon;

class Nursery {
  static Charmander charmander;
  static Charmeleon charmeleon;
  static Charizard charizard;

 public:
  std::unique_ptr<Pokemon> yield(std::string const& species) const;
};

#endif  // NURSERY_HPP
