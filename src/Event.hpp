#pragma once
#include "Hero.hpp"
#include "Mob.hpp"

/**
 * Event realizes possible ambush by a mob or an accident happening somewhere in the world
 */
class Event
{
  public:
    /**
     * Determines whether you got ambushed by a random Mob, if so, calls hero.Fight()
     * @param hero hero
     * @param mob attacking mob
     */
    bool Ambush ( Hero & hero, Mob & mob );
    /**
     * Determines whether you tripped, losing a random amount of health;
     * @param hero hero
     */
    bool Accident ( Hero & hero );
    /**
     * First calls Accident, then Ambush if Accident didn't occur
     * @param hero hero
     * @param mob attacking mob
     */
    bool RollTheDice ( Hero & hero, Mob & mob );
    const int & DropChance () const { return dropChance; };
  private:
    const int ambushChance = 5; /**< chance to get ambushed */
    const int accidentChance = 5; /**< chance to have an accident */
    const int dropChance = 5; /**< chance to drop an item */
};