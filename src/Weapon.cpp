#include "Weapon.hpp"
#include <iostream>

using namespace std;

void Weapon::Print () const
{
  cout << "Weapon: " << name << ", inflicting: " << attack << " damage." << endl;
}

void Weapon::SpecialEffect ()
{
  this->attack++;
}

void Weapon::SuperItem ()
{
  name = "Warglaives of Azzinoth";
  attack = 420;
}