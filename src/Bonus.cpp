//
// Bonus.cpp for Bonus in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 14:50:23 2013 jordan bettin
// Last update Sun Jun  9 11:11:24 2013 jordan bettin
//

#include "Bonus.hh"

Bonus::Bonus(int x, int y)
{
  this->_name = "Bonu ";
  this->_score = 20;
  this->_range = 0;
  this->_x = x;
  this->_y = y;
  this->_position = Vector3f(0.0f, 0.0f, 0.0f);
  this->_rotation = Vector3f(0.0f, 0.0f, 0.0f);
  this->_type = APlayers::Bonus;
  this->_bonusType = random() % 3;
}

Bonus::Bonus(const Bonus & other) : AObjects(other)
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
  this->_bonusType = other.getBonusType();
}

Bonus &	Bonus::operator=(const Bonus & other)
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
      this->_bonusType = other.getBonusType();
    }
  return (*this);
}

Bonus::~Bonus()
{}

void    Bonus::randomBonus(AObjects *player)
{
  std::map<unsigned int, fctType> fct;

  fct.insert(std::make_pair(0, &Bonus::addBomb));
  fct.insert(std::make_pair(1, &Bonus::incRange));
  fct.insert(std::make_pair(2, &Bonus::speedUp));
  (this->*fct[this->_bonusType])(dynamic_cast<APlayers *>(player));
}

void    Bonus::addBomb(APlayers *player)
{
  player->addBomb();
}

void    Bonus::incRange(APlayers *player)
{
  player->increaseBombRange();
}

void    Bonus::speedUp(APlayers *player)
{
  player->increaseSpeed();
}

float	Bonus::getVecX() const
{
  return (this->_position.x);
}

float	Bonus::getVecY() const
{
  return (this->_position.y);
}

float	Bonus::getVecZ() const
{
  return (this->_position.z);
}

int	Bonus::getScore() const
{
  return (this->_score);
}

void	Bonus::setScore(int s)
{
  this->_score = s;
}

void	Bonus::setVecX(float x)
{
  this->_position.x = x;
}

void	Bonus::setVecY(float y)
{
  this->_position.y = y;
}

void	Bonus::setVecZ(float z)
{
  this->_position.z = z;
}

void	Bonus::destroyObject()
{
  this->~Bonus();
}

int	Bonus::getRange() const
{
  return (this->_range);
}

void    Bonus::setTexture(int id)
{
  switch (id)
    {
    case 1:
      this->setBonusTexture("img/mine/");
      break;
    case 2:
      this->setBonusTexture("img/desert/");
      break;
    case 3:
      this->setBonusTexture("img/forest/");
      break;
    case 4:
      this->setBonusTexture("img/snow/");
      break;
    default:
      break;
    }
}

void    Bonus::setBonusTexture(std::string biome)
{
  switch (this->_bonusType)
    {
    case 0:
      biome += "bombe.png";
      break;
    case 1:
      biome += "Bonus.png";
      break;
    case 2:
      biome += "green.png";
      break;
    }
  this->_texture = gdl::Image::load(biome);
}

void	Bonus::initialize()
{}

void	Bonus::update(gdl::GameClock const __attribute__((unused)) & clock, gdl::Input  __attribute__((unused)) & input)
{}

void	Bonus::draw()
{
  this->_texture.bind();
  glEnable(GL_TEXTURE_2D);
  glPushMatrix();
  glTranslatef(this->_position.x, this->_position.y - 200, -this->_position.z);
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
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}

APlayers::typeObject Bonus::getType() const
{
  return (this->_type);
}

void	Bonus::setPosX(int x)
{
  this->_x = x;
}

void	Bonus::setPosY(int y)
{
  this->_y = y;
}

int	Bonus::getPosX() const
{
  return (this->_x);
}

int	Bonus::getPosY() const
{
  return (this->_y);
}

int     Bonus::getBonusType() const
{
  return (this->_bonusType);
}

void	Bonus::call(APlayers *player, void (Bonus::*fctType)(APlayers *))
{
  (this->*fctType)(player);
  player->setScore(player->getScore() + 5);
}

void    Bonus::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  std::cout << m.size() << std::endl;
}
