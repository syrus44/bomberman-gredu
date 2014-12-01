//
// Floor.cpp for Bomberman in /home/caille_l//Documents/merge_map_objects
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Mon May  6 10:31:03 2013 louis cailleux
// Last update Wed Jun  5 13:22:38 2013 pierre petit
//

#include "Floor.hh"

Floor::Floor(int x, int y, int mx, int my)
{
  this->_name = "Floo ";
  this->_score = 0;
  this->_range = 0;
  this->_mapx = mx;
  this->_mapy = my;
  this->_x = x;
  this->_y = y;
  this->_position = Vector3f(0.0f, 0.0f, 0.0f);
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
}

Floor::Floor(Floor const & other) : AObjects(other)
{
  this->_name = other.getName();
  this->_score = other.getScore();
  this->_range = other.getRange();
  this->_position.x = other.getVecX();
  this->_position.y = other.getVecY();
  this->_position.z = other.getVecZ();
  this->_type = other.getType();
}

Floor::~Floor()
{}

Floor&	Floor::operator=(Floor const &other)
{
  if (this != &other)
    {
      this->_name = other.getName();
      this->_score = other.getScore();
      this->_range = other.getRange();
      this->_position.x = other.getVecX();
      this->_position.y = other.getVecY();
      this->_position.z = other.getVecZ();
      this->_type = other.getType();
    }
  return (*this);
}

float	Floor::getVecX() const
{
  return (this->_position.x);
}

float	Floor::getVecY() const
{
  return (this->_position.y);
}

float	Floor::getVecZ() const
{
  return (this->_position.z);
}

int	Floor::getScore() const
{
  return (this->_score);
}

void	Floor::setScore(int s)
{
  this->_score = s;
}

void	Floor::setVecX(float x)
{
  this->_position.x = x;
}

void	Floor::setVecY(float y)
{
  this->_position.y = y;
}

void	Floor::setVecZ(float z)
{
  this->_position.z = z;
}

void	Floor::destroyObject()
{
  this->~Floor();
}

int	Floor::getRange() const
{
  return (this->_range);
}

void	Floor::setTexture(int id)
{
  switch (id)
    {
    case 1:
      this->_texture = gdl::Image::load("img/mine/floor.png");
      break;
    case 2:
      this->_texture = gdl::Image::load("img/desert/floor.png");
      break;
    case 3:
      this->_texture = gdl::Image::load("img/forest/floor.png");
      break;
    case 4:
      this->_texture = gdl::Image::load("img/snow/floor.png");
      break;
    default:
      break;
    }
}

void	Floor::initialize()
{}

void	Floor::update(gdl::GameClock const __attribute__((unused)) & clock, gdl::Input __attribute__((unused)) & input)
{}

void    Floor::draw()
{
  this->_texture.bind();
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  this->_position.x = 0;
  this->_position.z = 0;
  for (int x = 0; x < this->_mapx; x++)
    {
      for (int y = 0; y < this->_mapy; y++)
        {
          glBegin(GL_QUADS);

          //////////////dessus                                                                                            
          glTexCoord2f(0.0f, 0.0f);
          /// Vertex superieur gauche                                                                                     
          glVertex3f(-FLOOR_WIDTH_SIZE, FLOOR_DEEP_SIZE, -FLOOR_WIDTH_SIZE);
          glTexCoord2f(0.0f, 1.0f);
          /// Vertex inferieur gauche                                                                                     
          glVertex3f(-FLOOR_WIDTH_SIZE, FLOOR_DEEP_SIZE, FLOOR_WIDTH_SIZE);
          glTexCoord2f(1.0f, 1.0f);
          /// Vertex inferieur droit                                                                                      
          glVertex3f(FLOOR_WIDTH_SIZE, FLOOR_DEEP_SIZE, FLOOR_WIDTH_SIZE);
          glTexCoord2f(1.0f, 0.0f);
          /// Vertex superieur droit                                                                                      
          glVertex3f(FLOOR_WIDTH_SIZE, FLOOR_DEEP_SIZE, -FLOOR_WIDTH_SIZE);
          /// Vertex superieur droit                                                                                      
          glVertex3f(-FLOOR_WIDTH_SIZE, -FLOOR_DEEP_SIZE, FLOOR_WIDTH_SIZE);
          glEnd();
          glTranslatef(this->_position.x, this->_position.y, this->_position.z - FLOOR_WIDTH_SIZE * 2);
        }
      glTranslatef(this->_position.x + FLOOR_WIDTH_SIZE * 2, this->_position.y, this->_position.z + FLOOR_WIDTH_SIZE * 2 * this->_mapy);
    }
  glPopMatrix();
}


AObjects::typeObject Floor::getType() const
{
  return (this->_type);
}

void	Floor::setPosX(int x)
{
  this->_x = x;
}

void	Floor::setPosY(int y)
{
  this->_y = y;
}

int	Floor::getPosX() const
{
  return (this->_x);
}

int	Floor::getPosY() const
{
  return (this->_y);
}

void	Floor::randomBonus(AObjects *o)
{o = o;}

void    Floor::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  std::cout << m.size() << std::endl;
}
