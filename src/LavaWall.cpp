//
// Floor.cpp for  in /home/petit_p//projets/bomberman-gredu/branches/sparw
// 
// Made by pierre petit
// Login   <petit_p@epitech.net>
// 
// Started on  Mon May 13 12:46:13 2013 pierre petit
// Last update Sat Jun  8 17:18:43 2013 jordan bettin
//

#include "LavaWall.hh"

LavaWall::LavaWall(int x, int y, int mapx, int mapy)
{
  this->_name = "Wall ";
  this->_score = 0;
  this->_range = 0;
  this->_position = Vector3f(0.0f, 0.0f, 0.0f);
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  this->_x = x;
  this->_y = y;
  this->_mapx = mapx;
  this->_mapy = mapy;
  this->_type = AObjects::Wall;
}

LavaWall::LavaWall(const LavaWall & other) : AObjects(other)
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

LavaWall &	LavaWall::operator=(const LavaWall & other)
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

LavaWall::~LavaWall()
{}

void    LavaWall::setTexture(int id)
{
  switch (id)
    {
    case 1:
      this->_texture = gdl::Image::load("img/mine/LavaWall.png");
      break;
    case 2:
      this->_texture = gdl::Image::load("img/desert/LavaWall.png");
      break;
    case 3:
      this->_texture = gdl::Image::load("img/forest/LavaWall.png");
      break;
    case 4:
      this->_texture = gdl::Image::load("img/snow/LavaWall.png");
      break;
    default:
      break;
    }
}

void	LavaWall::initialize(void)
{}

void LavaWall::update(gdl::GameClock const __attribute__((unused)) & gameClock, gdl::Input __attribute__((unused)) & input)
{}

float	LavaWall::getVecX() const
{
  return (this->_position.x);
}

float	LavaWall::getVecY() const
{
  return (this->_position.y);
}

float	LavaWall::getVecZ() const
{
  return (this->_position.z);
}

void	LavaWall::setVecX(float x)
{
  this->_position.x = x;
}

void	LavaWall::setVecY(float y)
{
  this->_position.y = y;
}

void	LavaWall::setVecZ(float z)
{
  this->_position.z = z;
}

void    LavaWall::draw(void)
{
  this->_texture.bind();
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  this->_position.x = 0;
  this->_position.z = 0;

  glTranslatef(this->_position.x - WALL_WIDTH_SIZE * 2, this->_position.y, this->_position.z + WALL_WIDTH_SIZE * 2);
  for (int x = -1; x != (this->_mapx + 1); x++)
    {
      for (int y = -1; y != (this->_mapy + 1); y++)
        {
	  glBegin(GL_QUADS);
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
	  //}                                                                                                         
          glTranslatef(this->_position.x, this->_position.y, this->_position.z - WALL_WIDTH_SIZE * 2);
        }
      glTranslatef(this->_position.x + WALL_WIDTH_SIZE * 2, this->_position.y, this->_position.z + WALL_WIDTH_SIZE * 2 * (this->_mapy + 2));
    }
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}


void	LavaWall::setScore(int s)
{
  this->_score = s;
}

int	LavaWall::getScore() const
{
  return (this->_score);
}

void	LavaWall::destroyObject()
{
  this->~LavaWall();
}

int	LavaWall::getRange() const
{
  return (this->_range);
}

AObjects::typeObject LavaWall::getType() const
{
  return (this->_type);
}

void	LavaWall::setPosX(int x)
{
  this->_x = x;
}

void	LavaWall::setPosY(int y)
{
  this->_y = y;
}

int	LavaWall::getPosX() const
{
  return (this->_x);
}

int	LavaWall::getPosY() const
{
  return (this->_y);
}

void	LavaWall::randomBonus(AObjects *o)
{o = o;}

void    LavaWall::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  std::cout << m.size() << std::endl;
}
