#include "Event.hpp"
#include <iostream>

using namespace std;

bool Event::Ambush ( Hero & hero, Mob & mob )
{
  if ( rand() % 100 <= ambushChance )
  {
    cout << "You have been ambushed by " << mob.Name() << "." << endl;
    hero.Fight( mob );
    return true;
  }
  return false;
}

bool Event::Accident ( Hero & hero )
{
  int chance = std::rand();
  if ( chance % 100 <= accidentChance )
  {
    cout << "You tripped and lost " << (chance % 10)
     << " health points. Be more careful next time!" << endl;
    hero.ChangeHealth ( chance % 10 );
    return true;
  }
  return false;
}

bool Event::RollTheDice ( Hero & hero, Mob & mob )
{
  if ( Accident( hero ) )
    return true;
  if ( Ambush( hero, mob ) )
    return true;
  
  return false;
}