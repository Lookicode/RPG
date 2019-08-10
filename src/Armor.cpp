#include <string>
#include "Armor.hpp"
#include <iostream>

using namespace std;

void Armor::Print () const
{
  cout << "Piece of armor, called: " << name
  << ", protecting you from "  << defense << " damage." << endl;
}

void Armor::SpecialEffect ()
{
  this->defense++;
}

void Armor::SuperItem ()
{
  name = "Mannoroth's Bloodletting Manacles";
  defense = 420;
}