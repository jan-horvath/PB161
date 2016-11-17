#ifndef SPECIES_HPP
#define SPECIES_HPP
class Pokemon;

class Species {
 public:
  virtual unsigned int attack_power(unsigned int level) const = 0;
  virtual unsigned int defense_power(unsigned int level) const = 0;
};

#endif  // SPECIES_HPP
