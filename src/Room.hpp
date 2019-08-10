#pragma once
#include <vector>
#include <string>
#include "Mob.hpp"
#include "Coordinates.hpp"
#include <memory>

/**
 * Room class constructs a room with coordinates, directions, stores dialogues
 */ 
class Room
{
  public:
    /**
     * Constructor
     * @param x x coordinate
     * @param y y coordinate
     * @param directions possible directions
     */
    Room ( const int & x, const int & y, const std::string & directions )
      : directions ( directions )
      {
        coordinates.xCoor = x;
        coordinates.yCoor = y;
      };
    /**
     * Copy constructor
     * @param s Room pointer to create a deep copy
     */
    Room( const Room* s ) :
    coordinates( s->coordinates ),
    directions( s->directions ),
    startDialogues( s->startDialogues ),
    changeDialogues( s->changeDialogues ) {};
    /**
     * Adds to startDialogues - dialogues that you see when you enter the room
     * @param dialogue dialogue to be added
     * @return room with more dialogues
     */
    Room & AddStart ( const std::string & dialogue );
    /**
     * Adds to changeDialogues - dialogues that you see when you leave the room
     * @param dialogue dialogue to be added
     * @return room with more dialogues
     */
    Room & AddChange ( const std::string & dialogue );
    /**
     * Coordinates getter
     * @return coordinates of the room
     */
    Coordinates Coord () const { return coordinates; };
    /**
     * Directions getter
     * @return directions
     */
    std::string Directions() const { return directions; };
    /**
     * Outputs startDialogues into save file
     */
    void ExportStartDialogues ( std::ofstream & out ) const;
    /**
     * Outputs changeDialogues into save file
     */
    void ExportChangeDialogues ( std::ofstream & out ) const;
    /**
     * Typecast operator ( functor )
     */
    operator std::shared_ptr<Room>() { return std::make_shared<Room>(this);};
    /**
     * Clears startDialogues
     */
    void ClearStart () { startDialogues.clear(); };
    /**
     * Clears changeDialogues
     */
    void ClearChange () { changeDialogues.clear(); };
    /**
     * Prints startDialougues
     */
    void PrintStart () const;
    /**
     * Prints changeDialogues
     */
    void PrintChange () const;
  private:
    Coordinates coordinates; /**< coordinates */
    std::string directions; /**< directions */
    std::vector <std::string> startDialogues; /**< dialogues when you enter the room */
    std::vector <std::string> changeDialogues; /**< dialogues when you leave the room */
};