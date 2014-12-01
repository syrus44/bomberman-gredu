//
// Air.cpp for Air in /home/bettin_j//SVN/bomberman-gredu/trunk/Bomberman/src
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Wed May 15 17:24:29 2013 jordan bettin
// Last update Sun Jun  9 10:39:02 2013 jordan bettin
//

#include "Air.hh"

Air::Air(int x, int y)
{
  this->_name = "Air! ";
  this->_score = 0;
  this->_range = 0;
  this->_x = x;
  this->_y = y;
  this->_position = Vector3f(0.0f, 0.0f, 0.0f);
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  this->_type = AObjects::Air;
}

Air::Air(const Air & other) : AObjects(other)
{
  this->_name = other.getName();
  this->_score = other.getScore();
  this->_range = other.getRange();
  this->_position.x = other.getVecX();
  this->_position.y = other.getVecY();
  this->_position.z = other.getVecZ();
  this->_type = other.getType();
  this->_x = other.getPosX();
  this->_y = other.getPosY();
}

Air &	Air::operator=(const Air & other)
{
  if (&other != this)
    {
      this->_name = other.getName();
      this->_score = other.getScore();
      this->_range = other.getRange();
      this->_position.x = other.getVecX();
      this->_position.y = other.getVecY();
      this->_position.z = other.getVecZ();
      this->_type = other.getType();
      this->_x = other.getPosX();
      this->_y = other.getPosY();
    }
  return (*this);
}

Air::~Air()
{}

float	Air::getVecX() const
{
  return (this->_position.x);
}

float	Air::getVecY() const
{
  return (this->_position.y);
}

float	Air::getVecZ() const
{
  return (this->_position.z);
}

int	Air::getScore() const
{
  return (this->_score);
}

void	Air::destroyObject()
{}

int	Air::getRange() const
{
  return (this->_range);
}

AObjects::typeObject	Air::getType() const
{
  return (this->_type);
}

void	Air::setScore(int s)
{
  this->_score = s;
}

void	Air::setVecX(float x)
{
  this->_position.x = x;
}

void	Air::setVecY(float y)
{
  this->_position.y = y;
}

void	Air::setVecZ(float z)
{
  this->_position.z = z;
}

void	Air::update(gdl::GameClock const __attribute__((unused)) & clock, gdl::Input __attribute__((unused)) & input)
{}

void    Air::setTexture(int id)
{
  id--;
}

void	Air::initialize()
{}

void	Air::draw()
{}

void	Air::setPosX(int x)
{
  this->_x = x;
}

void	Air::setPosY(int y)
{
  this->_y = y;
}

int	Air::getPosX() const
{
  return (this->_x);
}

int	Air::getPosY() const
{
  return (this->_y);
}

void	Air::randomBonus(AObjects *o)
{o = o;}

void    Air::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  std::cout << m.size() << std::endl;
}
