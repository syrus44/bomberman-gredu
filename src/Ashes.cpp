//
// Ashes.cpp for Asheserman in /home/caille_l//Documents/sparw
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Wed May 22 13:58:17 2013 louis cailleux
// Last update Sat Jun  8 12:21:59 2013 louis cailleux
//

#include "Ashes.hh"

void	farewell(void *object)
{
  Ashes *ash = static_cast<Ashes *>(object);
  int x = ash->getPosX();
  int y = ash->getPosY();
  ash->getMap()->rmObj(x, y);
  ash->endGame();
}

Ashes::Ashes(Map *mp, int x, int y)
{
  this->_name = "Ash  ";
  this->_score = 0;
  this->_range = 2;
  this->_map = mp;
  this->_x = x;
  this->_y = y;
  this->_position = Vector3f(x * 2 * FLOOR_WIDTH_SIZE, 200, y * 2 * FLOOR_WIDTH_SIZE);
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  this->_type = AObjects::Unknown;
  this->setTimer();
}

void    Ashes::endGame()
{
  if (this->_map->getShown() == false)
    this->_map->affScores();
}

void	Ashes::setTimer()
{
  Timer<Ashes>(3000000, &farewell, this);
}

Ashes::Ashes(const Ashes & other) : AObjects(other)
{
  this->_name = other.getName();
  this->_score = other.getScore();
  this->_range = other.getRange();
  this->_map = other.getMap();
  this->_position.x = other.getVecX();
  this->_position.y = other.getVecY();
  this->_position.z = other.getVecZ();
  this->_x = other.getPosX();
  this->_y = other.getPosY();
  this->_type = other.getType();
  this->setTimer();
}

Ashes &	Ashes::operator=(const Ashes & other)
{
  if (&other != this)
    {
      this->_name = other.getName();
      this->_score = other.getScore();
      this->_range = other.getRange();
      this->_map = other.getMap();
      this->_position.x = other.getVecX();
      this->_position.y = other.getVecY();
      this->_position.z = other.getVecZ();
      this->_x = other.getPosX();
      this->_y = other.getPosY();
      this->_type = other.getType();
    }
  return (*this);
}

Ashes::~Ashes()
{}

int	Ashes::getScore() const
{
  return (this->_score);
}

void	Ashes::setScore(int s)
{
  this->_score = s;
}

void	Ashes::destroyObject()
{}

int	Ashes::getRange() const
{
  return (this->_range);
}

void	Ashes::setMap(Map *mp)
{
  this->_map = mp;
}

Map*	Ashes::getMap() const
{
  return (this->_map);
}

void	Ashes::setVecX(float x)
{
  this->_position.x = x;
}

void	Ashes::setVecY(float y)
{
  this->_position.y = y;
}

void	Ashes::setVecZ(float z)
{
  this->_position.z = z;
}

float	Ashes::getVecX() const
{
  return (this->_position.x);
}

float	Ashes::getVecY() const
{
  return (this->_position.y);
}

float	Ashes::getVecZ() const
{
  return (this->_position.z);
}

void	Ashes::setTexture(int id)
{
  id--;
}

void	Ashes::initialize()
{}

void	Ashes::update(gdl::GameClock const __attribute__((unused)) & clock, gdl::Input  __attribute__((unused)) & input)
{
  int rot = this->_rotation.y;
  this->_rotation.y = (rot + 1) % 360;
}

void	Ashes::draw()
{
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glTranslatef(this->_position.z, this->_position.y, -this->_position.x);

  glBegin(GL_TRIANGLES);
  glColor3f(1.0f, 1.0f, 1.0f);
  glVertex3f(0.0f, -150.0f, -150.0f);
  glVertex3f(-150.0f, -150.0f, 150.0f);
  glVertex3f(150.0f, -150.0f, 150.0f);
  glColor3f(1.0f, 0.0f, 0.0f);
  glVertex3f(0.0f, 150.0f, 0.0f);
  glVertex3f(-150.0f, -150.0f, 150.0f);
  glVertex3f(150.0f, -150.0f, 150.0f);
  glColor3f(0.0f, 1.0f, 0.0f);
  glVertex3f(0.0f, 150.0f, 0.0f);
  glVertex3f(0.0f, -150.0f, -150.0f);
  glVertex3f(-150.0f, -150.0f, 150.0f);
  glColor3f(0.0f, 0.0f, 1.0f);
  glVertex3f(0.0f, 150.0f, 0.0f);
  glVertex3f(150.0f, -150.0f, 150.0f);

  glVertex3f(0.0f, -150.0f, -150.0f);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

AObjects::typeObject Ashes::getType() const
{
  return (this->_type);
}

void	Ashes::setPosX(int x)
{
  this->_x = x;
}

void	Ashes::setPosY(int y)
{
  this->_y = y;
}

int	Ashes::getPosX() const
{
  return (this->_x);
}

int	Ashes::getPosY() const
{
  return (this->_y);
}

void	Ashes::randomBonus(AObjects *o)
{o = o;}

void    Ashes::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  std::cout << m.size() << std::endl;
}
