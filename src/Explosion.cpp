//
// Bomb.cpp for Bomb in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 14:33:48 2013 jordan bettin
// Last update Sat Jun  8 19:04:12 2013 florent cerfon
//

#include "Timer.hpp"
#include "Explosion.hh"

Explosion::Explosion(Map *map, int x, int y)
{
  this->_name = "Expl ";
  this->_score = 0;
  this->_range = 2;
  this->_x = x;
  this->_y = y;
  this->_mp = map;
  this->_position = Vector3f(x * 300, 200, y * 300);
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  this->_type = AObjects::Explosion;
  this->_clock.play();
  this->timeBeforeDetonation = 1.5000;
  this->initialize();
  this->running = true;
}

Explosion::Explosion(const Explosion & other) : AObjects(other)
{
  this->_name = other.getName();
  this->_score = other.getScore();
  this->_range = other.destroyObject();
  this->_position.x = other.getVecX();
  this->_position.y = other.getVecY();
  this->_position.z = other.getVecZ();
  this->_x = other.getPosX();
  this->_y = other.getPosY();
  this->_type = other.getType();
}

Explosion &	Explosion::operator=(const Explosion & other)
{
  if (&other != this)
    {
      this->_name = other.getName();
      this->_score = other.getScore();
      this->_range = other.destroyObject();
      this->_position.x = other.getVecX();
      this->_position.y = other.getVecY();
      this->_position.z = other.getVecZ();
      this->_x = other.getPosX();
      this->_y = other.getPosY();
      this->_type = other.getType();
    }
  return (*this);
}

Explosion::~Explosion()
{}

Map	*Explosion::getMap(void) const
{
  return (this->_mp);
}

int	Explosion::getScore() const
{
  return (this->_score);
}

void	Explosion::setScore(int s)
{
  this->_score = s;
}

int	Explosion::destroyObject() const
{
  return (this->_range);
}

void	Explosion::setVecX(float x)
{
  this->_position.x = x;
}

void	Explosion::setVecY(float y)
{
  this->_position.y = y;
}

void	Explosion::setVecZ(float z)
{
  this->_position.z = z;
}

float	Explosion::getVecX() const
{
  return (this->_position.x);
}

float	Explosion::getVecY() const
{
  return (this->_position.y);
}

float	Explosion::getVecZ() const
{
  return (this->_position.z);
}

void    Explosion::setMap(std::map<int, std::map<int, AObjects *> > const & mp)
{
  this->_map = mp;
}

void	Explosion::initialize()
{
  this->_texture = gdl::Image::load("img/lava.png");
}

void	Explosion::update(gdl::GameClock const __attribute__((unused)) & clock, gdl::Input  __attribute__((unused)) & input)
{
  this->_clock.update();
  if (this->_clock.getTotalElapsedTime() > this->timeBeforeDetonation)
    this->getMap()->rmExpl();
}

void	Explosion::pause()
{
  if (this->running != false)
    {
      this->timeBeforeDetonation -= this->_clock.getTotalElapsedTime();
      this->_clock.pause();
      this->running = false;
    }
}

void	Explosion::unpause()
{
  if (this->running != true)
    {
      this->_clock.play();
      this->running = true;
    }
}

void	Explosion::draw()
{
  glEnable(GL_TEXTURE_2D);
  this->_texture.bind();
  glPushMatrix();
  std::map<int, std::map<int, AObjects *> >::iterator y;
  std::map<int, AObjects *>::iterator x;
  this->_position.x = 0;
  this->_position.z = 0;
  glTranslatef(0, WALL_DEEP_SIZE * 2, 0);
  for (y = this->_map.begin(); y != this->_map.end(); ++y)
    {
      for (x = y->second.begin(); x != y->second.end(); ++x)
        {
          if (x->second->getType() == AObjects::Explosion)
            {
              glTranslatef(this->_position.x + (y->first * WALL_WIDTH_SIZE * 2), 0,
			   this->_position.z - (x->first * WALL_WIDTH_SIZE * 2));
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

	      glEnd();
              glTranslatef(this->_position.x - (y->first * WALL_WIDTH_SIZE * 2),
			   0, this->_position.z + (x->first * WALL_WIDTH_SIZE * 2));
	    }
	}
    }
  glPopMatrix();

}

AObjects::typeObject Explosion::getType() const
{
  return (this->_type);
}

void	Explosion::setPosX(int x)
{
  this->_x = x;
}

void	Explosion::setPosY(int y)
{
  this->_y = y;
}

int	Explosion::getPosX() const
{
  return (this->_x);
}

int	Explosion::getPosY() const
{
  return (this->_y);
}

void	Explosion::randomBonus(AObjects *o)
{o = o;}

void	Explosion::setTexture(int i)
{
  i--;
}

void	Explosion::destroyObject()
{}

int	Explosion::getRange() const
{
  return (0);
}
