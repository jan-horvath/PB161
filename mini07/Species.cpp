#include "Species.hpp"

class Charmander : public Species {
  virtual unsigned int attack_power(unsigned int) const override { return 1; }
  virtual unsigned int defense_power(unsigned int) const override { return 2; };
};

class Charmeleon : public Species {
  virtual unsigned int attack_power(unsigned int level) const override {
    return 1 + level;
  }
  virtual unsigned int defense_power(unsigned int level) const override {
    return 2 + level;
  }
};

class Charizard : public Species {
  virtual unsigned int attack_power(unsigned int) const override { return 7; }
  virtual unsigned int defense_power(unsigned int level) const override {
    return 10 * level;
  }
};
