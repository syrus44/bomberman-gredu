//
// APlayers.cpp for APlayers in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 14:56:54 2013 jordan bettin
// Last update Sat Jun  8 04:35:42 2013 florent cerfon
//

#include "APlayers.hh"
#include "Map.hh"

APlayers::APlayers() 
{
  this->_isAlive = true;
}

APlayers::APlayers(const APlayers & other) : AObjects(other)
{
  this->_isAlive = other.isAlive();
}

APlayers &	APlayers::operator=(const APlayers & other)
{
  if (&other != this)
    this->_isAlive = other.isAlive();
  return (*this);
}

bool	APlayers::isAlive() const
{
  return (this->_isAlive);
}

int	APlayers::getSpeed() const
{
  return (this->_speed);
}

APlayers::~APlayers()
{}
