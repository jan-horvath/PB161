#include <stdexcept>

#include "Pokemon.hpp"
#include "Species.hpp"

using namespace std;

unsigned int Pokemon::hp() const {
  return m_hp;
}

unsigned int Pokemon::level() const {
  return m_level;
}

const Species& Pokemon::species() const {
  return m_species;
}

void attack(Pokemon& attacker, Pokemon& victim) {
  unsigned int attack_power = attacker.species().attack_power(attacker.level());
  unsigned int victim_power = victim.species().defense_power(victim.level());
  if (attack_power <= victim_power)
    return;
  if (victim.hp() <= attack_power - victim_power) {
    victim.m_hp = 0;
    attacker.m_level++;
    return;
  }
  victim.m_hp -= attack_power - victim_power;
}
