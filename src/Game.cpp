#include "Game.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <typeinfo>
#include <sstream>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;
using namespace std;

const int LineLength = 200;

const string brightBlue = "\033[96m";
const string defaultColor = "\033[0m";
const string brightBoldPink = "\033[1;95m";
const string brightBoldRed = "\033[1;91m";
const string boldYellow = "\033[1;33m";
//const string indigo = "#4B0082";

stringstream Game::VerifyLine()
{
  string tmp;
  getline( cin, tmp );
  stringstream ss;
  ss << tmp;
  return ss;
}

void Game::Help () const
{
  cout << brightBoldPink << "You have the following options:" << endl;
  cout << "go north/west/east/south - go to another room in the direction" << endl;
  cout << "save - saves the game" << endl;
  cout << "load - load another file, you will be asked to enter the filename" << endl;
  cout << "quit - quits the game without saving, be sure to save your progress!" << endl;
  cout << "gold - shows the current amount of gold" << endl;
  cout << "inventory - print the current contents of your inventory" << endl;
  cout << "whereami - tells you where you are, pretty straightforward if you ask me 4Head" << endl;
  cout << "wherecanigo - possible rooms to visit" << endl;
  cout << "whoami - prints your stats and inventory" << defaultColor << endl;
}

bool Game::Go( stringstream & ss )
{
  Coordinates coord( hero.Position().xCoor, hero.Position().yCoor );
  string second;
  if ( !(ss >> second) )
  {
    return false;
  }
  // if second is neither of: north, west, east, south
  if (second != "north" && second != "west" && second != "east" && second != "south" )
  {
    cout << "Unknown option, type 'help' to list possible options." << endl;
    return false;
  }

  if ( second == "north" )
  {
    coord.yCoor += 1;
  }
  else if ( second == "west" )
  {
    coord.xCoor -= 1;
  }
  else if ( second == "east" )
  {
    coord.xCoor += 1;
  }
  else if ( second == "south" )
  {
    coord.yCoor -= 1;
  }
  return ChangeRoom( hero.Position(), coord );
}

bool Game::GetCommand()
{
  cout << "[Your input]> ";
  stringstream ss = VerifyLine();
  string first;
  if ( ss >> first )
  {
    if ( first == "go" )
    {
      if ( Go( ss ) )
      {
        unsigned int mobPoolIdx = rand() % world.MobPool().size();
        Mob mob( world.MobPool().at( mobPoolIdx ) );
        int goldBefore = hero.Gold();
        if ( event.RollTheDice( hero, mob ) && hero.Health() > 0 )
          cout << "It is a good thing you survived that, mate." << endl;
        
        if ( goldBefore != hero.Gold() )
        { // if you won the fight, there is a chance you will also get an item
          if ( rand() % 100 <= event.DropChance() )
          {
            unsigned int itemPoolIdx = rand() % world.ItemPool().size();
            auto tmp = world.ItemPool().at( itemPoolIdx );
            if ( tmp->Attack() == 0 )
            {
              hero.AddArmor( tmp->Name(), tmp->Defense() );
            }
            else
            {
              hero.AddWeapon( tmp->Name(), tmp->Attack() );
            }
            cout << "You just received:" << endl;
            tmp->Print();
            
          }
        }
        if ( hero.Health() <= 0 )
        {
          Quit();
          return true;
        }
        cout << boldYellow << "You just arrived at Room [" << hero.Position().xCoor << "," <<
        hero.Position().yCoor << "]." << defaultColor << endl;
      }
    }
    else if ( first == "help" )
      Help();
    else if ( first == "save" )
    {
      Export();
    }
    else if ( first == "load" )
    {
      cout << "Just so you know, saves are called RPG_Save_x and are stored in the 'examples' folder," << endl <<
      "so you can ask to load something like: 'examples/RPG_Save_0'." << endl;
      do
      {
        cout << "Enter the name of the file to be loaded." << endl;
        first = VerifyString();
      } while ( !Import( first.c_str() ) );
      
    }
    else if ( first == "quit" )
      Quit();
    else if ( first == "whereami" )
      hero.WhereAmI();
    else if ( first == "gold" )
      hero.PrintGold();
    else if ( first == "inventory" )
      hero.PrintInventory();
    else if ( first == "wherecanigo" )
      world.PrintRooms( hero.Position() );
    else if ( first == "whoami" )
      hero.Print();
    else if ( first == "whoisyourdaddy" )
      {
        cout << "You just went super saiyan!" << endl;
        hero.Superhero();
      }

    else 
    {
      cout << "Unknown option, type 'help' to list possible options." << endl;
      return false;
    }
  return true;
  ss.clear();
  }

  return false;
}

bool Game::ContainsState( const string & input )
{
  if ( input.find( "WORLD" ) != string::npos )
  {
    STATE = WORLD;
    return true;
  }
  else if ( input.find( "HERO" ) != string::npos )
  {
    STATE = HERO;
    return true;
  }
  else if ( input.find( "ITEMS" ) != string::npos )
  {
    STATE = ITEMS;
    return true;
  }
  else if ( input.find( "MOBS" ) != string::npos )
  {
    STATE = MOBS;
    return true;
  }
  else if ( input.find( "DIALOGUES" ) != string::npos )
  {
    STATE = DIALOGUES;
    return true;
  }
  return false;
}

void Game::VerifyWorld ( ifstream & in )
{
  int x, y;
  string line;
  getline( in, line );
  stringstream ss;
  ss << line;
  if ( ContainsState( line ) )
  {
    cout << "World definition is done." << endl;
    return;
  }
  string directions;
  if ( ss >> directions >> x >> y )
  {
    world.AddRoom( Coordinates( x, y ), directions );
  }
}

void Game::VerifyItems( ifstream & in )
{
  string line;
  getline( in, line );
  stringstream ss;
  ss << line;
  if ( ContainsState( line ) )
    return;
  string name, owned;
  int at, def;
  if ( ss >> name >> at >> def >> owned )
  {
    if ( at != 0 && def == 0 && owned == "true" )
      hero.AddWeapon( name, at );
    else if ( at != 0 && def == 0 )
      world.AddWeapon( name, at );

    else if ( at == 0 && def != 0 && owned == "true" )
      hero.AddArmor( name, def );
    else if ( at == 0 && def != 0 )
      world.AddArmor( name, def );
  }

}

void Game::VerifyHero ( ifstream & in )
{
  string tmp;
  getline ( in, tmp );
  stringstream ss;
  ss << tmp;
  if ( ContainsState( tmp ) )
    return;
  string name;
  int hp, dmg, def, gold;
  Coordinates coord;
  int x, y;
  if ( newGame == false )
  {
    if ( ss >> name >> hp >> dmg >> def >> gold )
    {
      hero = CreateHero( name, hp, dmg, def );
      hero.ChangeGold( gold );
    }
    else
    {
      cout << "False, ale nepovedlo se" << endl;
      hero = CreateHero();
      hero.ChangeGold( 0 );
    }
  }
  else 
  {
    cout << "newgame true" << endl;
    hero = CreateHero();
  }

  getline( in, tmp );
  ss.clear();
  ss << tmp;
  if ( ss >> x >> y )
  {
    hero.ChangePosition ( Coordinates( x, y ) );
  } 
  else
  {
    do 
    {
      cout << 
      "We were unable to load your first/previous hero's position, please enter x manually."
      << endl;
      coord.xCoor = VerifyNumber();
      cout << "And now the y coordinate." << endl;
      coord.yCoor = VerifyNumber();
    } while ( world.Rooms()->find( coord ) == world.Rooms()->end() );
      hero.ChangePosition ( coord );
  }

  string state;
  do
  {
    getline( in, state );
  }
  while ( !ContainsState( state ) );

}

void Game::VerifyMobs ( ifstream & in )
{
  string line;
  getline( in, line );
  stringstream ss;
  ss << line;
  if ( ContainsState( line ) )
  {
    return;
  }
  string name;
  int attack, health;
  Coordinates coord;
  if ( ss >> name >> health >> attack )
  {
      world.AddMobPool( Mob( name, health, attack, health + attack ) );
  }

}

void Game::VerifyDialogues ( ifstream & in )
{
  int type;
  Coordinates coord;
  if ( in >> coord.xCoor >> coord.yCoor >> type )
  {
    string tmp;
    getline ( in, tmp );
    if ( tmp.empty() )
      tmp = "";
    auto rooms = world.Rooms();
    auto it = rooms->find( coord );
    if ( it == rooms->end() )
      return;
    if ( type == 0 )
    {
      rooms->find( coord )->second->AddStart( tmp );
    }
    else if ( type == 1 )
    {
      rooms->find( coord )->second->AddChange( tmp );
    }
  }
}

bool Game::Import ( const char * fileName )
{
  ifstream in ( fileName, ios_base::in );
  if ( !(in.good()) )
  {
    cout << "Input file error!" << endl;
    return false; 
  }

  in.seekg(0, ios::beg);
  
  world.ClearRooms();
  world.ClearMobPool();
  world.ClearItemPool();
  

  string firstLine;
  do
  {
    getline(in, firstLine);
  }
  while (firstLine.find("~") == string::npos);
  
  string nGame;
  do
  {
    getline(in, nGame);
  }
  while ( nGame.find( "true" ) == string::npos && nGame.find( "false" ) == string::npos);

  /*if ( nGame.find( "true" ) != string::npos )
    newGame = true;
  else */if ( nGame.find( "false" ) != string::npos )
    newGame = false;
  else newGame = true;

  string state;
  do
  {
    getline(in, state);
  }
  while (!ContainsState(state));

  while ( !in.eof() )
  {
    switch (STATE)
    {
      case WORLD:
      {
        VerifyWorld( in );
        break;
      }
      case HERO:
      {
        VerifyHero( in );
        break;
      }
      case ITEMS:
      {
        VerifyItems( in );
        break;
      }
      case MOBS:
      {
        VerifyMobs( in );
        break;
      }
      case DIALOGUES:
      {
        VerifyDialogues( in );
        break;
      }
    }
  }

  in.close();
  return true;
}

void Game::WriteTildeBool ( ofstream & out ) const
{
  out << "~" << endl;
  out << "false" << endl << endl;
}

void Game::WriteWorld( ofstream & out ) const
{
  out << "WORLD" << endl;
  auto rooms = world.Rooms();
  auto roomsBegin = rooms->begin();
  auto roomsEnd = rooms->end();
  for ( auto it = roomsBegin; it != roomsEnd; it++ )
  {
    out << it->second->Directions() << " " << to_string(it->first.xCoor) << " " << to_string(it->first.yCoor) << endl;
  }
  
  out << endl;
}

void Game::WriteHero( ofstream & out ) const
{
  out << "HERO" << endl;
  out << hero.Name() << " " << hero.Health() << " " << hero.Damage()
   << " " << hero.Defense() << " " << hero.Gold() << endl;
  out << hero.Position().xCoor << " " << hero.Position().yCoor << endl;
  out << endl;
}

void Game::WriteItems( ofstream & out ) const
{
  out << "ITEMS" << endl;
  for ( auto it : hero.Inventory() )
  {
    out << it->Name() << " " << it->Attack() << " " <<  it->Defense() << " true" << endl;
  }

  for ( auto it : world.ItemPool() )
  {
    out << it->Name() << " " << it->Attack() << " " <<  it->Defense() << " false" << endl;
  }

  out << endl;
}

void Game::WriteMobs( ofstream & out ) const
{
  out << "MOBS" << endl;
  world.PrintMobPool( out );
  out << endl;
}

void Game::WriteDialogues( ofstream & out ) const
{
  out << "DIALOGUES" << endl;
  for ( auto it : *(world.Rooms()) )
  {
    it.second->ExportStartDialogues( out );
    it.second->ExportChangeDialogues( out );
  }
}

bool Game::Export ()
{
  //string saveName = "RPG_Save_" + to_string(saveCnt);
  cout << "Please enter desired name of the save file:" << endl;
  string userInput = VerifyString();
  string saveName = "savefiles/" + userInput;
  ofstream out ( saveName );
  if ( !out.is_open() )
  {
    cout << "Not possible to open export file." << endl;
    return false;
  }

  WriteTildeBool ( out );
  WriteWorld ( out );
  WriteHero ( out );
  WriteItems ( out );
  WriteMobs ( out );
  WriteDialogues ( out );

  out.close();
  cout << "Save file called '" << userInput << "' has been successfully created!" << endl; 
  //saveCnt++;
  return true;
}
void Game::StartGame ()
{
  srand( time(0) );
  GetSave();
  do
  {
    GetCommand();
  } while ( !(quit == true) );
  
  
}

void Game::GetSave()
{
  string first = "savefiles/";
  cout << "Existing save files:" << endl;
  string xpath = "./savefiles";
  for ( const auto & entry : fs::directory_iterator( xpath ) )
  {
    cout << entry.path() << endl;
  }
  do
  {
    cout << "Enter the name of the file to be loaded." << endl;
    first += VerifyString();
  } while ( !Import( first.c_str() ) );
}

bool Game::ChangeRoom( const Coordinates & from, const Coordinates & to )
{
  if ( world.Rooms()->find( to ) == world.Rooms()->end() )
  {
    cout << "Destination room doesn't exist." << endl;
    return false;
  }

  if ( from.xCoor - to.xCoor == 1 && from.yCoor == to.yCoor )
  { //west
    if ( world.Rooms()->find( from )->second->Directions().find( "w" ) || 
        world.Rooms()->find( to )->second->Directions().find( "e" ))
    {
      hero.ChangePosition( to );
    }
  }
  else if ( from.xCoor - to.xCoor == -1 && from.yCoor == to.yCoor )
  { //east
    if ( world.Rooms()->find( from )->second->Directions().find( "e" ) ||
        world.Rooms()->find( to )->second->Directions().find( "w" ))
    {
      hero.ChangePosition( to );
    }
  }
  else if ( from.yCoor - to.yCoor == 1 && from.xCoor == to.xCoor )
  { //south
    if ( world.Rooms()->find( from )->second->Directions().find( "s" ) ||
        world.Rooms()->find( to )->second->Directions().find( "n" ))
    {
      hero.ChangePosition( to );
    }
  }
  else if ( from.yCoor - to.yCoor == -1 && from.xCoor == to.xCoor )
  { //north
    if ( world.Rooms()->find( from )->second->Directions().find( "n" ) ||
        world.Rooms()->find( to )->second->Directions().find( "s" ))
    {
      hero.ChangePosition( to );
    }
  }
  else return false;

  world.Rooms()->find( from )->second->PrintChange();
  world.Rooms()->find( to )->second->PrintStart();

  return true;
}

string Game::VerifyString ()
{
  string tmp;
  int i = 0;
  do
  {
    if ( i != 0 )
    {
      cin.clear();
      cin.ignore( __INT_MAX__, '\n' );
      cout << "Wrong input, please try again." << endl;
    }
    i++;
  }
  while ( !(cin >> tmp) );
  cin.clear();
  cin.ignore( __INT_MAX__, '\n' );
  return tmp;
}

int Game::VerifyNumber ()
{
  int tmp;
  int i = 0;
  do
  {
    if ( i != 0 )
    {
      cin.clear();
      cin.ignore( __INT_MAX__, '\n' );
      cout << "Wrong input, please try again." << endl;
    }
    i++;
  }
  while ( !(cin >> tmp) );
  cin.clear();
  cin.ignore( __INT_MAX__, '\n' );
  return tmp;
}

int Game::VerifyPositiveNumber ()
{
  int tmp;
  int i = 0;
  do
  {
    if ( i != 0 )
    {
      cin.clear();
      cin.ignore( __INT_MAX__, '\n' );
      cout << "Wrong input, please try again." << endl;
    }
    i++;
  }
  while ( !(cin >> tmp) || tmp <= 0 );
  cin.clear();
  cin.ignore( __INT_MAX__, '\n' );
  return tmp;
}

Hero Game::CreateHero ( const string & name, const int & health,
                        const int & damage, const int & defense )
{
  Hero hero( name, health, damage, defense );
  return hero;
}

Hero Game::CreateHero ()
{
  string name;
  int health;
  int damage;
  int defense;
  cout << "Hi, nice to meet you. Before we start, you need to create your hero. What is his/her name?" << endl;
  name = VerifyString();
  cout << "Wow, what a cool name, " << name << endl;
  cout << "Now, how much health does " << name << " have?" << endl;
  health = VerifyPositiveNumber();
  cout << "Okay, you chose to have " << health << " health points. Now what about your default damage without any weapons equipped?" << endl;
  damage = VerifyPositiveNumber();
  cout << "And your default defense without any armor on?" << endl;
  defense = VerifyPositiveNumber();
  cout << "Nice! So your hero is" << endl << endl
  << name << endl
  << "HP: " << health << endl
  << "DMG: " << damage << endl
  << "DEF: " << defense << endl << endl;
  Hero hero( name, health, damage, defense );
  return hero;
}

void Game::Quit ()
{
  quit = true;
  cout << brightBoldRed << "Game over, friend. Come back soon!" << defaultColor << endl;
}

int main ( void )
{
  Game game;
  game.StartGame();
  
  return 0;
}