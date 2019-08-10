#pragma once
#include <string>
//#include "Room.hpp"
#include "Coordinates.hpp"

/**
 * Basic abstract class which stores the common attributes of Mob and Hero and also Print
 */
class Sprite
{
  public:
    /**
     * Default constructor
     */
    Sprite () {};
    /**
     * Constructor
     * @param name name
     * @param health health
     * @param damage damage
     */
    Sprite ( const std::string & name, const int & health, const int & damage )
        : name ( name ), health ( health ), damage ( damage ) {};
    /**
     * Pure virtual print, implemented in its children
     */
    virtual void Print () const = 0;
  protected:
    std::string name; /**< name */
    int health; /**< health */
    int damage; /**< damage */
    
};