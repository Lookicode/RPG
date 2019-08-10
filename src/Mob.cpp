#include "Mob.hpp"
#include <iostream>

using namespace std;

void Mob::Print () const
{
  cout << name << " with outstanding stats such as: "
  << health << "HP and causes " << damage << " damage." << endl;
}

int Mob::DropGold () const
{
  return health + damage;
}