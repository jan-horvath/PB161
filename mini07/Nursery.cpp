#include <stdexcept>

#include "Pokemon.hpp"
#include "Species.hpp"

#include "Nursery.hpp"

using namespace std;

Charmander Nursery::charmander;
Charmeleon Nursery::charmeleon;
Charizard Nursery::charizard;

unique_ptr<Pokemon> Nursery::yield(string const& species) const {
  if (species == "charmeleon") {
    return unique_ptr<Pokemon>(new Pokemon(charmeleon));
  }
  if (species == "charmander") {
    return unique_ptr<Pokemon>(new Pokemon(charmander));
  }
  if (species == "charizard") {
    return unique_ptr<Pokemon>(new Pokemon(charizard));
  }
  throw logic_error("Unknown pokemon, can't hatch!");
}
