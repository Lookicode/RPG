#pragma once
#include "Item.hpp"
#include <string>

/**
 * Weapon class derived from Item, every instance has a name and attack
 */
class Weapon : public Item
{
  public:
    /**
     * constructor
     * @param name name
     * @param attack attack
     */
    Weapon ( const std::string & name, const int & attack )
        : Item ( name ), attack ( attack ) {};
    /**
     * Derived Print method with its own implementation
     */
    void Print () const;
    /**
     * Attack getter
     * @return int attack
     */
    int Attack () const { return attack; };
    /**
     * Defense getter
     * @return int defense
     */
    int Defense () const { return 0; };
    /**
     * Name getter
     * @return string Name
     */
    std::string Name () const { return name; };
    /**
     * When applied on weapon, increments its attack by 1
     */
    void SpecialEffect();
    /**
     * Virtual destructor
     */
    virtual ~Weapon () {};
    /**
     * polymorphic method to turn all items into legendary WoW items
     */
    void SuperItem ();
  private:
    int attack; /**< attack */
};