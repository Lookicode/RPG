//#pragma once
#include <iostream>
#include <cassert>
#include <vector>
#include <fstream> 
#include "Room.hpp"
#include <string>

using namespace std;

const string boldYellow = "\033[1;33m";
const string defaultColor = "\033[0m";

Room & Room::AddStart ( const std::string & dialogue )
{
  startDialogues.push_back( dialogue );
  return *this;
}

Room & Room::AddChange ( const std::string & dialogue )
{
  changeDialogues.emplace_back( dialogue );
  return *this;
}

void Room::ExportStartDialogues ( ofstream & out ) const
{
  for ( auto it : startDialogues )
  {
    out << coordinates.xCoor << " " << coordinates.yCoor << " 0 " << it << endl;
  } 
}

void Room::PrintStart () const
{
  for ( auto it : startDialogues )
  {
    cout << boldYellow << "[" << coordinates.xCoor << "," << coordinates.yCoor << "] " << it << defaultColor << endl;
  }
}

void Room::PrintChange () const
{
  for ( auto it : changeDialogues )
  {
    cout << boldYellow << "[" << coordinates.xCoor << "," << coordinates.yCoor << "] " << it << defaultColor << endl;
  }
}

void Room::ExportChangeDialogues ( ofstream & out ) const
{
  for ( auto it : changeDialogues )
  {
    out << coordinates.xCoor << " " << coordinates.yCoor << " 1 " << it << endl;
  } 
}