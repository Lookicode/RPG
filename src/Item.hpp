#pragma once
#include <string>

/**
 * Item is an abstract class with a pure virtual method Print that has no implementation, class has two children that inherit the print ( so that we can have a vector of Items owned by a hero )
 */
class Item
{
  public:
    /**
     * Constructor
     * @param name name
     */
    Item ( const std::string name ) 
        : name ( name ) {};
    /**
     * Pure virtual print
     */
    virtual void Print () const = 0;
    /**
     * Pure virtual speciallEffect, in its children enhances the item's stats
     */
    virtual void SpecialEffect() = 0;
    /**
     * Pure virtual attack getter
     */
    virtual int Attack () const = 0;
    /**
     * Pure virtual defense getter
     */
    virtual int Defense () const = 0;
    /**
     * Pure virtual name getter
     */
    virtual std::string Name () const = 0;
    /**
     * polymorphic method to turn all items into legendary WoW items
     */
    virtual void SuperItem () = 0;
  protected:
    std::string name; /**< item name */

};