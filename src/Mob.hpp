#pragma once
#include "Sprite.hpp"

/**
 * Mob inherits from Sprite, drops gold upon death
 */
class Mob : public Sprite
{
  public:
    /**
     * Default constructor
     */
    Mob () {};
    /**
     * Constructor to assemble mob
     * @param name name
     * @param health health
     * @param damage damge
     * @param damage damage
     * @param goldValue goldValue
     */
    Mob ( const std::string & name, const int & health,
          const int & damage, const int & goldValue )
      : Sprite ( name, health, damage ), goldValue ( goldValue ) {};
    /**
     * Construtor with an already assembled Mob
     * @param mob already constructed mob to be created
     */
    Mob ( const Mob & mob ) : Sprite ( mob.Name(), mob.Health(), mob.Damage() )
        , goldValue ( mob.GoldValue() ) {};
    /**
     * Damage getter
     * @return damage
     */
    int Damage () const { return damage; };
    /**
     * Health getter
     * @return health
     */
    int Health () const { return health; };
    /**
     * Name getter
     * @return name
     */
    std::string Name () const { return name; };
    /**
     * Print inherited from Sprite with own implementation
     */
    void Print () const;
    /**
     * Drops money proportionate to the mob's strength
     * @return int amount dropped
     */
    int DropGold() const;
    /**
     * virtual destructor
     */
    virtual ~Mob () {};
    /**
     * goldValue getter
     * @return goldValue
     */
    int GoldValue () const { return goldValue; };

  private:
    int goldValue; /**< goldValue */
};