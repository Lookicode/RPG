#pragma once
#include <string>
#include "Item.hpp"

/**
 * @brief Class Armor derived from Item
 * Every instance of Armor has a name and defense which is used for calculations in the Hero::Fight method
 */
class Armor : public Item
{
  public:
    /**
     * Constructor
     * @param name name
     * @param defense defense
     */
    Armor ( const std::string & name, const int & defense )
      : Item( name ), defense ( defense ) {};
    /**
     * Derived Print method with its own implementation, printing only "this";
     */
    void Print () const;
    /**
     * Defense getter
     * @return defense
     */
    int Defense () const { return defense; };
    /**
     * Attack getter
     * @return attack
     */
    int Attack () const { return 0; }
    /**
     * Name getter
     * @return name
     */
    std::string Name () const { return name; };
    /**
     * When applied on armor, increments its defense by 1
     */
    void SpecialEffect();
    /**
     * virtual destructor
     */
    virtual ~Armor () {};
    /**
     * polymorphic method to turn all items into legendary WoW items
     */
    void SuperItem ();
  private:
    int defense; /**< defense */
};