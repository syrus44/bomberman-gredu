//
// Bomb.cpp for Bomb in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 14:33:48 2013 jordan bettin
// Last update Sat Jun  8 18:57:37 2013 florent cerfon
//

#include "Timer.hpp"
#include "Bomb.hh"

Bomb::Bomb(Map *mp, Vector3f const &position, std::pair<int, int> const &p, APlayers *pl)
{
  this->_name = "Bomb ";
  this->_score = 0;
  this->_range = 1;
  this->_map = mp;
  this->_bomber = pl;
  this->_x = p.first;
  this->_y = p.second;
  this->_position = position;
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  this->_type = AObjects::Bomb;
  if (pl)
    this->_bomber->addDropped();
  this->_clock.play();
  this->timeBeforeDetonation = 2.5000;
  this->running = true;
}

Bomb::Bomb(const Bomb & other) : AObjects(other)
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

Bomb &	Bomb::operator=(const Bomb & other)
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

Bomb::~Bomb()
{}

int	Bomb::getScore() const
{
  return (this->_score);
}

void	Bomb::setScore(int s)
{
  this->_score = s;
}

void	Bomb::destroyObject()
{
  if (this->doesExist())
    {
      this->setExistence(false);
      this->_map->blow(this->_x, this->_y, this->_range);
      if (this->getBomber())
	this->getBomber()->rmDropped();
    }
}

int	Bomb::getRange() const
{
  return (this->_range);
}

void	Bomb::setMap(Map *mp)
{
  this->_map = mp;
}

Map*	Bomb::getMap() const
{
  return (this->_map);
}

APlayers* Bomb::getBomber() const
{
  return (this->_bomber);
}

void	Bomb::setVecX(float x)
{
  this->_position.x = x;
}

void	Bomb::setVecY(float y)
{
  this->_position.y = y;
}

void	Bomb::setVecZ(float z)
{
  this->_position.z = z;
}

float	Bomb::getVecX() const
{
  return (this->_position.x);
}

float	Bomb::getVecY() const
{
  return (this->_position.y);
}

float	Bomb::getVecZ() const
{
  return (this->_position.z);
}

void	Bomb::initialize()
{
  this->_texture = gdl::Image::load("img/tnt.png");
}

void    Bomb::setTexture(int id)
{
  id--;
}

void	Bomb::update(gdl::GameClock const __attribute__((unused)) & clock, gdl::Input  __attribute__((unused)) & input)
{
  this->_clock.update();
  if (this->_clock.getTotalElapsedTime() > this->timeBeforeDetonation)
    {
      this->getMap()->blow(this->getPosX(), this->getPosY(), this->getRange());
      if (this->getBomber())
	this->getBomber()->rmDropped();
    }
}

void	Bomb::pause()
{
  if (this->running != false)
    {
      this->timeBeforeDetonation -= this->_clock.getTotalElapsedTime();
      this->_clock.pause();
      this->running = false;
    }
}

void	Bomb::unpause()
{
  if (this->running != true)
    {
      this->_clock.play();
      this->running = true;
    }
}

void	Bomb::draw()
{
  this->_texture.bind();
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glTranslatef(this->_position.x, this->_position.y, -this->_position.z);
  glBegin(GL_QUADS);

  ///////////////devant                                                                                                 
  glTexCoord2f(0.0f, 0.0f);
  /// Vertex superieur gauche                                                                                           
  glVertex3f(-WALL_WIDTH_SIZE, WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(0.0f, 1.0f);
  /// Vertex inferieur gauche                                                                                           
  glVertex3f(-WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 1.0f);
  /// Vertex inferieur droit                                                                                            
  glVertex3f(WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 0.0f);
  /// Vertex superieur droit                                                                                            
  glVertex3f(WALL_WIDTH_SIZE, WALL_DEEP_SIZE, WALL_WIDTH_SIZE);

  //////////////coté gauche                                                                                             
  glTexCoord2f(0.0f, 0.0f);
  /// Vertex superieur gauche                                                                                           
  glVertex3f(-WALL_WIDTH_SIZE, WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(0.0f, 1.0f);
  /// Vertex inferieur gauche                                                                                           
  glVertex3f(-WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 1.0f);
  /// Vertex inferieur droit                                                                                            
  glVertex3f(-WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 0.0f);
  /// Vertex superieur droit                                                                                            
  glVertex3f(-WALL_WIDTH_SIZE, WALL_DEEP_SIZE, WALL_WIDTH_SIZE);

  ////////////////derrière                                                                                              
  glTexCoord2f(0.0f, 0.0f);
  /// Vertex superieur gauche                                                                                           
  glVertex3f(WALL_WIDTH_SIZE, WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(0.0f, 1.0f);
  /// Vertex inferieur gauche                                                                                           
  glVertex3f(WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 1.0f);
  /// Vertex inferieur droit                                                                                            
  glVertex3f(-WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 0.0f);
  /// Vertex superieur droit                                                                                            
  glVertex3f(-WALL_WIDTH_SIZE, WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);

  //////////////coté droit                                                                                              
  glTexCoord2f(0.0f, 0.0f);
  /// Vertex superieur gauche                                                                                           
  glVertex3f(WALL_WIDTH_SIZE, WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(0.0f, 1.0f);
  /// Vertex inferieur gauche                                                                                           
  glVertex3f(WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 1.0f);
  /// Vertex inferieur droit                                                                                            
  glVertex3f(WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 0.0f);
  /// Vertex superieur droit                                                                                            
  glVertex3f(WALL_WIDTH_SIZE, WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);

  //////////////dessus                                                                                                  
  glTexCoord2f(0.0f, 0.0f);
  /// Vertex superieur gauche                                                                                           
  glVertex3f(-WALL_WIDTH_SIZE, WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(0.0f, 1.0f);
  /// Vertex inferieur gauche                                                                                           
  glVertex3f(-WALL_WIDTH_SIZE, WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 1.0f);
  /// Vertex inferieur droit                                                                                            
  glVertex3f(WALL_WIDTH_SIZE, WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 0.0f);
  /// Vertex superieur droit                                                                                            
  glVertex3f(WALL_WIDTH_SIZE, WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);

  //////////////dessous                                                                                                 
  glTexCoord2f(0.0f, 0.0f);
  /// Vertex superieur gauche                                                                                           
  glVertex3f(WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, WALL_WIDTH_SIZE);
  glTexCoord2f(0.0f, 1.0f);
  /// Vertex inferieur gauche                                                                                           
  glVertex3f(WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 1.0f);
  /// Vertex inferieur droit                                                                                            
  glVertex3f(-WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, -WALL_WIDTH_SIZE);
  glTexCoord2f(1.0f, 0.0f);
  // Vertex superieur droit                                                                              
  glVertex3f(-WALL_WIDTH_SIZE, -WALL_DEEP_SIZE, WALL_WIDTH_SIZE);

  glEnd();
  glPopMatrix();

}

AObjects::typeObject Bomb::getType() const
{
  return (this->_type);
}

void	Bomb::setPosX(int x)
{
  this->_x = x;
}

void	Bomb::setPosY(int y)
{
  this->_y = y;
}

int	Bomb::getPosX() const
{
  return (this->_x);
}

int	Bomb::getPosY() const
{
  return (this->_y);
}

void    Bomb::setRange(int range)
{
  this->_range = range;
}

void	Bomb::randomBonus(AObjects *o)
{o = o;}

void    Bomb::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  std::cout << m.size() << std::endl;
}
