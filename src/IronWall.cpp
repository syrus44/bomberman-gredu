//
// Floor.cpp for  in /home/petit_p//projets/bomberman-gredu/branches/sparw
// 
// Made by pierre petit
// Login   <petit_p@epitech.net>
// 
// Started on  Mon May 13 12:46:13 2013 pierre petit
// Last update Thu May 30 20:25:58 2013 louis cailleux
//

#include "IronWall.hh"

IronWall::IronWall(int x, int y)
{
  this->_name = "Wall ";
  this->_score = 0;
  this->_range = 0;
  this->_position = Vector3f(0.0f, 0.0f, 0.0f);
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  this->_x = x;
  this->_y = y;
  this->_type = AObjects::Wall;
}

IronWall::IronWall(const IronWall & other) : AObjects(other)
{
  this->_position.x = other.getVecX();
  this->_position.y = other.getVecY();
  this->_position.z = other.getVecZ();
  this->_name = other.getName();
  this->_score = other.getScore();
  this->_range = other.getRange();
  this->_x = other.getPosX();
  this->_y = other.getPosY();
  this->_type = other.getType();
}

IronWall &	IronWall::operator=(const IronWall & other)
{
  if (&other != this)
    {
      this->_position.x = other.getVecX();
      this->_position.y = other.getVecY();
      this->_position.z = other.getVecZ();
      this->_name = other.getName();
      this->_score = other.getScore();
      this->_range = other.getRange();
      this->_type = other.getType();
      this->_x = other.getPosX();
      this->_y = other.getPosY();
    }
  return (*this);
}

IronWall::~IronWall()
{
}

void    IronWall::setTexture(int id)
{
  switch (id)
    {
    case 1:
      this->_texture = gdl::Image::load("img/mine/IronWall.png");
      break;
    case 2:
      this->_texture = gdl::Image::load("img/desert/IronWall.png");
      break;
    case 3:
      this->_texture = gdl::Image::load("img/forest/IronWall.png");
      break;
    case 4:
      this->_texture = gdl::Image::load("img/snow/IronWall.png");
      break;
    default:
      break;
    }
}

void IronWall::initialize(void)
{}

void IronWall::update(gdl::GameClock const __attribute__((unused)) & gameClock, gdl::Input __attribute__((unused)) & input)
{}

float	IronWall::getVecX() const
{
  return (this->_position.x);
}

float	IronWall::getVecY() const
{
  return (this->_position.y);
}

float	IronWall::getVecZ() const
{
  return (this->_position.z);
}

void	IronWall::setVecX(float x)
{
  this->_position.x = x;
}

void	IronWall::setVecY(float y)
{
  this->_position.y = y;
}

void	IronWall::setVecZ(float z)
{
  this->_position.z = z;
}

void IronWall::draw(void)
{
  this->_texture.bind();
  glEnable(GL_TEXTURE_2D);
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
	  if (x->second->getType() == AObjects::Wall)
	    {
	      glTranslatef(this->_position.x + (y->first * WALL_WIDTH_SIZE * 2)	\
			   , 0, this->_position.z - (x->first * WALL_WIDTH_SIZE * 2));
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
	      glTranslatef(this->_position.x - (y->first * WALL_WIDTH_SIZE * 2)	\
			   , 0, this->_position.z + (x->first * WALL_WIDTH_SIZE * 2));
	    }
	}
    }
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void	IronWall::setScore(int s)
{
  this->_score = s;
}

int	IronWall::getScore() const
{
  return (this->_score);
}

void	IronWall::destroyObject()
{
  this->~IronWall();
}

int	IronWall::getRange() const
{
  return (this->_range);
}

AObjects::typeObject IronWall::getType() const
{
  return (this->_type);
}

void	IronWall::setPosX(int x)
{
  this->_x = x;
}

void	IronWall::setPosY(int y)
{
  this->_y = y;
}

int	IronWall::getPosX() const
{
  return (this->_x);
}

int	IronWall::getPosY() const
{
  return (this->_y);
}

void	IronWall::randomBonus(AObjects *o)
{o = o;}

void    IronWall::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  this->_map = m;
}
