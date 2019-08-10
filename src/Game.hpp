#pragma once
#include "World.hpp"
#include "Hero.hpp"
#include "Event.hpp"
#include <map>
#include <fstream>
#include <sstream>

/**
 * Game class is responsible for starting and running the game. It contains the instance of world and just about everything else, this is the main class that ties it all together
 */
class Game
{
  public:
    /**
     * Is responsible for the whole process, plants seed for chanceGenerator
     */
    void StartGame();
    /**
     * Quits the game, either by your decision or when you died.
     */
    void Quit ();
    /**
     * Creates a hero by taking user input
     * @return a constructed hero
     */
    Hero CreateHero();
    /**
     * Creates a hero with already known attributes
     * @param name hero's name
     * @param health hero's health points
     * @param damage hero's damage
     * @param defense hero's defense
     * @return a constructed hero
     */
    Hero CreateHero ( const std::string & name, const int & health,
                      const int & damage, const int & defense );
    /**
     * Outputs input options for the player
     */
    void Help() const;
    /**
     * Handles player movement
     * @param ss stringstream to be later examined for the direction of movement
     * @return true if room was changed, false otherwise
     */
    bool Go ( std::stringstream & ss );
    /**
     * Handles any user input
     * @return true if getting the command was successfull, false otherwise
     */
    bool GetCommand ();
    /**
     * Gets an int from the user
     * @return an integer
     */
    int VerifyNumber();
    /**
     * Gets a positive int from the user
     * @return a positive integer
     */
    int VerifyPositiveNumber();
    /**
     * Gets a string from the user
     * @return a string
     */
    std::string VerifyString();
    /**
     * Gets a whole line of text from the user
     * @return stringstream containing the line
     */
    std::stringstream VerifyLine();
    /**
   * Verifies the data given by the file, skips a line that doesn't match the criteria,
   *  creates and "initializes" the game itself
   * @param fileName name of the file to be imported
   * @return true if import was successfull, false otherwise
   */
    bool Import ( const char * fileName );
    /**
     * Moves the player
     * @param from starting position
     * @param to wanted position
     * @return true if possible, false otherwise
     */
    bool ChangeRoom( const Coordinates & from, const Coordinates & to );
    /**
     * Creates rooms
     * @param in ifstream full of formatted input
     */
    void VerifyWorld ( std::ifstream & in );
    /**
     * Creates hero
     * @param in ifstream full of formatted input
     */
    void VerifyHero ( std::ifstream & in );
    /**
     * Creates items
     * @param in ifstream full of formatted input
     */
    void VerifyItems ( std::ifstream & in );
    /**
     * Creates mobs
     * @param in ifstream full of formatted input
     */
    void VerifyMobs ( std::ifstream & in );
    /**
     * Creates dialogues
     * @param in ifstream full of formatted input
     */
    void VerifyDialogues ( std::ifstream & in );
    /**
     * Checks if string contains another STATE
     * @param input string that maybe contains a STATE
     * @return true if contains, false otherwise
     */
    bool ContainsState ( const std::string & input );
     /**
     * writes the Tilde and newgame-boolean
     * @param out ofstream to write into
     */
    void WriteTildeBool ( std::ofstream & out ) const;
    /**
     * writes rooms into the exported file
     * @param out ofstream to write into
     */
    void WriteWorld ( std::ofstream & out ) const;
    /**
     * writes hero into the exported file
     * @param out ofstream to write into
     */
    void WriteHero ( std::ofstream & out ) const;
    /**
     * writes items into the exported file
     * @param out ofstream to write into
     */
    void WriteItems ( std::ofstream & out ) const;
    /**
     * writes mobs into the exported file
     * @param out ofstream to write into
     */
    void WriteMobs ( std::ofstream & out ) const;
    /**
     * writes dialogues into the exported file
     * @param out ofstream to write into
     */
    void WriteDialogues ( std::ofstream & out ) const;
    /**
     * Handles the whole game export
     * @return true if it was successfull, false otherwise
     */
    bool Export ();
    /**
     * Gets the name of a save file to be loaded
     */
    void GetSave ();
  private:
  /**
   * Finite state machine for input
   */
    enum states {
      WORLD, /**< handles rooms */
      HERO, /**< creates hero */
      ITEMS, /**< handles items */
      MOBS, /**< creates mobs */
      DIALOGUES }; /**< creates dialogues */
    enum states STATE; /**< instance of the FSM */
    bool newGame = true; /**< new-game-boolean. New game = true, else false */
    bool quit = false; /**< if quit is true, the game is terminated */
    Hero hero; /**< instance of Hero */
    World world; /**< instance of World */
    int saveCnt = 0; /**< number of savefiles */
    Event event; /**< instance of event */
};