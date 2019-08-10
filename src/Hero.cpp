#include "Hero.hpp"
#include <memory>
#include <iostream>

using namespace std;

const string brightBlue = "\033[96m";
const string defaultColor = "\033[0m";
const string brightBoldRed = "\033[1;91m";
const string brightBoldGreen = "\033[1;92m";


void Hero::PrintGold() const
{
  cout << "Your account balance is " << gold << " gold, keep collecting more!" << endl;
}

void Hero::Print () const
{
  cout << endl << brightBlue << "Your name is: " << name << "," << endl <<  "you have: " << health << " health, you have an outstanding damage of: "
  << damage << ", you are " << gold << " golds rich" << endl << "and your inventory looks as follows:" << endl;



  PrintInventory();
  cout << defaultColor << endl;
}

void Hero::PrintInventory () const
{
  for ( auto it : inventory )
  {
    it->Print();
  }
}

/**
 * Fight returns true if the Hero defeated the mob, returns false if Hero lost or ran away
 */
bool Hero::Fight ( Mob & mob )
{
  int heroAttack = this->damage;
  int heroHealth = this->health;
  int ranAway = 0;

  for ( auto it : inventory )
  {
    heroHealth += it->Defense();
    heroAttack += it->Attack(); 
  } 
  int mobHealth = mob.Health();
  int mobAttack  = mob.Damage();
  while ( heroHealth > 0 && mobHealth > 0 )
  {
    if ( heroHealth <= 5 )
    {
      do
      {
        cout << "You have a chance to run away and save your life!" << endl <<
        "Enter 1 to flee and enter 0 to keep fighting." << endl;
      } while ( !(cin >> ranAway && ( ranAway == 0 || ranAway == 1)) );
      if ( ranAway == 1 )
        break;
    }
    mobHealth -= heroAttack;
    cout << "You swing at the enemy, causing " << heroAttack << " damage. The mob has "
    << mobHealth << " health points left." << endl;
    if ( mobHealth <= 0 )
      break;

    heroHealth -= mobAttack;
    cout << "The mob attacks you, hitting you for " << mobAttack << " damage. You have "
    << heroHealth << " health left." << endl;
  }
  if ( heroHealth <= 0 )
  {
    cout << brightBoldRed << "You are dead. Better luck next time!" << defaultColor << endl;
    health = 0;
    return false;
  }
  else if ( ranAway == 1 )
  {
    cout << "Cowards get second chances!" << endl;
    return false;
  }

  cout << brightBoldGreen << "You won, congrats Kibo! Must have been a tough fight." << defaultColor << endl;
  unsigned int invPos =  std::rand() % inventory.size();
  inventory.at( invPos )->SpecialEffect();
  cout << "Your item:" << endl;
  inventory.at( invPos )->Print();
  cout << " has received a buff. You just got stronger!" << endl;

  AddGold( mob.DropGold() );
  return true;
}


Hero & Hero::ChangeHealth ( const int & delta )
{
  this->health -= delta;
  return *this;
}

void Hero::AddWeapon ( const string & name, const int & attack )
{
  inventory.emplace_back( shared_ptr< Item > ( new Weapon ( name, attack ) ) );
}

void Hero::AddArmor ( const string & name, const int & defense )
{
  inventory.emplace_back( shared_ptr< Item > ( new Armor ( name, defense ) ) );
}

Hero & Hero::ChangePosition ( const Coordinates & newPosition )
{
  position.xCoor = newPosition.xCoor;
  position.yCoor = newPosition.yCoor;
  return *this;
}

const int superheroCoefficient = 99999;

void Hero::Superhero ()
{
  health = superheroCoefficient;
  damage = superheroCoefficient;
  defense = superheroCoefficient;
  gold = superheroCoefficient;
  for ( auto it : inventory )
  {
    it->SuperItem();
  }
}
