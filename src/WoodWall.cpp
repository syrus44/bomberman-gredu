//
// Floor.cpp for  in /home/petit_p//projets/bomberman-gredu/branches/sparw
// 
// Made by pierre petit
// Login   <petit_p@epitech.net>
// 
// Started on  Mon May 13 12:46:13 2013 pierre petit
// Last update Fri Jun  7 22:52:03 2013 louis cailleux
//

#include "WoodWall.hh"

WoodWall::WoodWall(int x, int y)
{
  this->_name = "Dest ";
  this->_score = 0;
  this->_range = 0;
  this->_position = Vector3f(0.0f, 0.0f, 0.0f);
  this->_rotation = Vector3f(0.0, 0.0f, 0.0f);
  this->_type = AObjects::WallDestr;
  this->_x = x;
  this->_y = y;
}

WoodWall::WoodWall(const WoodWall & other) : AObjects(other)
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

WoodWall &	WoodWall::operator=(const WoodWall & other)
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

WoodWall::~WoodWall()
{}


void WoodWall::initialize(void)
{}

void WoodWall::update(gdl::GameClock const __attribute__((unused)) & gameClock, gdl::Input __attribute__((unused)) & input)
{}

float	WoodWall::getVecX(void) const
{
  return (this->_position.x);
}

float	WoodWall::getVecY(void) const
{
  return (this->_position.y);
}

float	WoodWall::getVecZ(void) const
{
  return (this->_position.z);
}

void	WoodWall::setVecX(float x)
{
  this->_position.x = x;
}

void	WoodWall::setVecY(float y)
{
  this->_position.y = y;
}

void	WoodWall::setVecZ(float z)
{
  this->_position.z = z;
}

void    WoodWall::setTexture(int id)
{
  switch (id)
    {
    case 1:
      this->_texture = gdl::Image::load("img/mine/WoodWall.png");
      break;
    case 2:
      this->_texture = gdl::Image::load("img/desert/WoodWall.png");
      break;
    case 3:
      this->_texture = gdl::Image::load("img/forest/WoodWall.png");
      break;
    case 4:
      this->_texture = gdl::Image::load("img/snow/WoodWall.png");
      break;
    default:
      break;
    }
}

void WoodWall::draw(void)
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
          if (x->second->getType() == AObjects::WallDestr)
            {
              glTranslatef(this->_position.x + (y->first * WALL_WIDTH_SIZE * 2)\
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
              glTranslatef(this->_position.x - (y->first * WALL_WIDTH_SIZE * 2)\
			   , 0, this->_position.z + (x->first * WALL_WIDTH_SIZE * 2));
            }
        }
    }
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

void	WoodWall::setScore(int s)
{
  this->_score = s;
}

int	WoodWall::getScore() const
{
  return (this->_score);
}

void	WoodWall::destroyObject()
{}

int	WoodWall::getRange() const
{
  return (this->_range);
}

AObjects::typeObject WoodWall::getType() const
{
  return (this->_type);
}

void	WoodWall::setPosX(int x)
{
  this->_x = x;
}

void	WoodWall::setPosY(int y)
{
  this->_y = y;
}

int	WoodWall::getPosX() const
{
  return (this->_x);
}

int	WoodWall::getPosY() const
{
  return (this->_y);
}

void	WoodWall::randomBonus(AObjects *o)
{o = o;}

void    WoodWall::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  this->_map = m;
}
