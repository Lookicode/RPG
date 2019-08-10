#include "World.hpp"
#include <map>
#include <memory>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

const string brightBlue = "\033[96m";
const string defaultColor = "\033[0m";

void World::AddRoom ( const Coordinates & coordinates, const string & directions )
{
  rooms.emplace( coordinates, Room( coordinates.xCoor, coordinates.yCoor, directions ) );
}

void World::PrintRooms ( const Coordinates & heroCoordinates ) const
{
  for ( auto it : rooms )
  {
    cout << "[" << rooms.at( it.first )->Coord().xCoor << "," << rooms.at( it.first )->Coord().yCoor << "]";
    if ( rooms.at( it.first )->Coord().xCoor == heroCoordinates.xCoor &&
         rooms.at( it.first )->Coord().yCoor == heroCoordinates.yCoor )
    {
      cout << brightBlue << "<-- You are here" << defaultColor;
    }
    cout << endl;
  }
}

void World::PrintMobPool ( ofstream & out ) const
{
  for ( auto it : mobPool )
  {
    out << it.Name() << " " << it.Damage() << " " << it.Health() << endl;
  }
}

void World::AddMobPool ( const Mob & mob )
{
  mobPool.emplace_back( mob );
}

void World::AddWeapon ( const string & name, const int & attack )
{
  itemPool.emplace_back( shared_ptr< Item > ( new Weapon ( name, attack ) ) );
}

void World::AddArmor ( const string & name, const int & defense )
{
  itemPool.emplace_back( shared_ptr< Item > ( new Armor ( name, defense ) ) );
}