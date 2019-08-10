#pragma once
/**
 * Coordinates play a crucial part in the implementation, almost any part of the game can be location-based 
 */
struct Coordinates
{
  /**
   * Default constructor
   */
  Coordinates () {};
  /**
   * Constructor
   * @param xCoor x coordinate
   * @param yCoor y coordinate
   */
  Coordinates ( int xCoor, int yCoor ) : xCoor ( xCoor ), yCoor ( yCoor ) {};
  int xCoor;  /**< x */
  int yCoor; /**< y */
};