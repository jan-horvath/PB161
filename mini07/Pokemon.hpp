#ifndef POKEMON_HPP
#define POKEMON_HPP

class Species;

class Pokemon {
  friend class Nursery;

 private:
  const Species& m_species;
  unsigned int m_hp;
  unsigned int m_level;

  Pokemon(const Species& species) : m_species(species), m_hp(100), m_level(0) {}

 public:
  Pokemon() = delete;
  const Species& species() const;
  unsigned int hp() const;
  unsigned int level() const;

  friend void attack(Pokemon& attacker, Pokemon& victim);
};

#endif  // POKEMON_HPP
