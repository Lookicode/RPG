#pragma once
#include "Room.hpp"
#include "Mob.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include <map>
#include <string>
#include <vector>
#include <memory>
#include <fstream>

/**
 * @brief World class stores a map of rooms and mobs that are identified by their coordinates, is responsible for changing rooms
 */
class World
{
  public:
    /**
     * Adds room into map of rooms
     * @param coordinates coordinates of the room, map key
     * @param directions possible directions in which hero can go
     */
    void AddRoom ( const Coordinates & coordinates, const std::string & directions );
    /**
     * Prints all the rooms stored in the "rooms" map
     * @param heroCoordinates hero's coordinates
     */
    void PrintRooms ( const Coordinates & heroCoordinates ) const;
    /**
     * Adds mob into a vector of available mobs
     * @param mob mob to be added
     */
    void AddMobPool ( const Mob & mob );
    /**
     * Prints all mobs from vector of mobs
     * @param out ofstream to print into
     */
    void PrintMobPool ( std::ofstream & out ) const;
    /**
     * Adds Armor into a vector of available items
     * @param name name
     * @param defense defense
     */
    void AddArmor ( const std::string & name, const int & defense );
    /**
     * Adds Weapon into a vector of available items
     * @param name name
     * @param attack attack
     */
    void AddWeapon ( const std::string & name, const int & attack );
    /**
     * Room map getter
     * @return &rooms
     */
    auto Rooms () const { return &rooms; }
    /**
     * ItemPool getter
     * @return itemPool vector of items
     */
    auto ItemPool () const { return itemPool; };
    /**
     * mobPool getter
     * @return mobPool vector of items
     */
    auto MobPool () const { return mobPool; };
    /**
     * Clears mobPool
     */
    void ClearMobPool () { mobPool.clear(); };
    /**
     * Clears rooms
     */
    void ClearRooms () { rooms.clear(); };
    /**
     * Clears itemPool
     */
    void ClearItemPool () { itemPool.clear(); };
    
  private:
    /**
     * Struct with a functor to compare Coordinates in a map
     */
    struct cmpCoord
    {
      /**
       * Functor to compare coordinates
       * @return true if a comes before b
       */
      bool operator() ( const Coordinates & a, const Coordinates & b ) const
      {
        if ( a.xCoor < b.xCoor )
          return true;
        else if ( a.xCoor == b.xCoor && a.yCoor < b.yCoor )
          return true;

        return false;
      }
    };
    std::map < Coordinates, std::shared_ptr < Room >, cmpCoord > rooms; /**< map of rooms */
    std::vector < std::shared_ptr < Item > > itemPool; /**< pool of available items */
    std::vector < Mob > mobPool; /**< pool of available mobs */
};
