#pragma once
#include "Sprite.hpp"
#include "Mob.hpp"
#include "Armor.hpp"
#include "Weapon.hpp"
#include <memory>
#include <vector>
#include <string>
#include <iostream>

// shared_ptr?

/**
 * Hero class stores an inventory in addition to the things inherited from Sprite, has a method for turn-based fighting
 */
class Hero : public Sprite
{
  public:
    /**
     * Default constructor
     */
    Hero () {};
    /**
     * Constructor
     * @param name name
     * @param health health
     * @param damage damage
     * @param defense defense
     */
    Hero ( const std::string & name, const int & health, const int & damage, const int & defense )
        : Sprite ( name, health, damage ), defense ( defense ) {};
    /**
     * Handles turn-based fighting, hero can run away
     * @param mob mob attacking you
     * @return true if hero won, false if hero ran away or lost
     */
    bool Fight ( Mob & mob );
    /**
    * Prints hero
    */
    void Print () const;
    /**
    * Subtracts the given amount of health points
    * @param delta amount to be substracted
    * @return Hero & with the new health amount
    */
    Hero & ChangeHealth ( const int & delta );
    /**
    * Moves hero to another position
    * @param newPosition new position
    */
    Hero & ChangePosition ( const Coordinates & newPosition );
    /**
    * Adds armor to inventory
    * @param name name of the item
    * @param defense item's defense
    * @return this - updated hero
    */
    void AddArmor ( const std::string & name, const int & defense );
    /**
    * Adds weapon to inventory
    * @param name name of the item
    * @param attack item's attack
    */
    void AddWeapon ( const std::string & name, const int & attack );
    /**
     * Coordinates getter
     * @return coordinates
     */
    Coordinates Position () const { return position; }
    /**
     * Prints hero's inventory
     */
    void PrintInventory () const;
    /**
     * Name getter
     * @return name
     */
    std::string Name () const { return name; };
    /**
     * Health getter
     * @return health
     */
    int Health () const { return health; };
    /**
     * Damage getter
     * @return damage
     */  
    int Damage () const { return damage; };
    /**
     * Defense getter
     * @return defense
     */
    int Defense () const { return defense; };
    /**
     * Gold getter
     * @return gold
     */
    int Gold () const { return gold; };
    /**
     * Changes hero's money
     * @param newGold new final amount
     */
    void ChangeGold ( const int & newGold ) { gold = newGold; };
    /**
     * Adds money
     * @param loot amount to be incremented
     */
    void AddGold ( const int & loot ) { gold += loot; };
    /**
     * Inventory getter
     * @return inventory
     */
    auto Inventory () const { return inventory; };
    /**
     * Handles the 'whereami' command
     */
    void WhereAmI() const { std::cout << "You are in room: [" << position.xCoor <<
    ", " << position.yCoor << "]." << std::endl; }
    /**
     * Handles gold command
     */
    void PrintGold() const;
    /**
     * Secret method obtainable only by the 'whoisyourdaddy' cheat
     */
    void Superhero();
  private:
    int defense; /**< defense */
    std::vector< std::shared_ptr < Item > > inventory; /**< hero's inventory */
    Coordinates position;  /**< position */
    int gold = 0; /**< gold that hero owns */
};