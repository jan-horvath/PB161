#include "Species.hpp"

class Charmander : public Species {
  unsigned int attack_power(unsigned int) const override { return 1; }
  unsigned int defense_power(unsigned int) const override { return 2; };
};

class Charmeleon : public Species {
  unsigned int attack_power(unsigned int level) const override {
    return 1 + level;
  }
  unsigned int defense_power(unsigned int level) const override {
    return 2 + level;
  }
};

class Charizard : public Species {
  unsigned int attack_power(unsigned int) const override { return 7; }
  unsigned int defense_power(unsigned int level) const override {
    return 10 * level;
  }
};
