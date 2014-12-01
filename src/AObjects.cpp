//
// AObjects.cpp for bomberman in /home/caille_l//Documents/cpp/caille_l
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Thu May  2 13:05:26 2013 louis cailleux
// Last update Mon May 27 22:30:02 2013 florent cerfon
//

#include "AObjects.hh"

AObjects::AObjects(void)
{
  this->_position = Vector3f(0.0f, 0.0f, 0.0f);
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  this->_type = AObjects::Unknown;
  this->existence = true;
}

AObjects::AObjects(AObjects const& other)
{
  this->_name = other.getName();
  this->_score = other.getScore();
  this->_position.x = other.getVecX();
  this->_position.y = other.getVecY();
  this->_position.z = other.getVecZ();
  this->_type = other.getType();
  this->existence = true;
}

AObjects& AObjects::operator=(AObjects const &other)
{
  if (this != &other)
    {
      this->_name = other.getName();
      this->_score = other.getScore();
      this->_position.x = other.getVecX();
      this->_position.y = other.getVecY();
      this->_position.z = other.getVecZ();
      this->_type = other.getType();
      this->existence = other.doesExist();
    }
  return (*this);
}

AObjects::~AObjects()
{}

bool	AObjects::doesExist() const
{
  return (this->existence);
}

void	AObjects::setExistence(bool value)
{
  this->existence = value;
}

const std::string &	AObjects::getName() const
{
  return (this->_name);
}

void	AObjects::setName(const std::string &name)
{
  this->_name = name;
}
