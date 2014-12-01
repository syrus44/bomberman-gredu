//
// Human.cpp for Human in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 15:05:07 2013 jordan bettin
// Last update Sun Jun  9 10:52:43 2013 jordan bettin
//

#include "Human.hh"

void    hideSave(void *object)
{
  Human *h = static_cast<Human *>(object);
  h->getMap()->setSave(false);
}

Human::Human(Map *map, const int x, const int y, int posx, int posy, int nb)
{
  this->_map = map;
  this->_score = 0;
  this->_name = "Play ";
  this->_isAlive = true;
  this->_bombRange = 2;
  this->_bombStock = 1;
  this->_bombDropped = 0;
  this->_nbLives = 3;
  this->_range = 0;
  this->_type = AObjects::Human;
  this->_dir = APlayers::Left;
  if (x > y)
    this->_speed = x;
  else
    this->_speed = y;
  this->_x = posx;
  this->_y = posy;
  this->_nbplayer = nb;
  this->_position = Vector3f (posx * (FLOOR_WIDTH_SIZE * 2), FLOOR_DEEP_SIZE, posy * (FLOOR_WIDTH_SIZE * 2));
  this->setKeys();
}

Human::Human(const Human & other) : APlayers(other)
{
  this->_map = other.getMap();
  this->_score = other.getScore();
  this->_name = other.getName();
  this->_isAlive = other.isAlive();
  this->_haveBonus = other.haveBonus();
  this->_bombStock = other.getBombStock();
  this->_bombDropped = other.getBombDropped();
  this->_nbLives = other.getLives();
  this->_currentBonus = other.getCurrentBonus();
  this->_range = other.getRange();
  this->_type = other.getType();
  this->_dir = other.getDir();
  this->_x = other.getPosX();
  this->_y = other.getPosY();
  this->_nbplayer = other.getNbPlayer();
  this->setKeys();
}

Human &	Human::operator=(const Human & other)
{
  if (&other != this)
    {
      this->_map = other.getMap();
      this->_bombStock = other.getBombStock();
      this->_bombDropped = other.getBombDropped();
      this->_score = other.getScore();
      this->_name = other.getName();
      this->_isAlive = other.isAlive();
      this->_haveBonus = other.haveBonus();
      this->_nbLives = other.getLives();
      this->_currentBonus = other.getCurrentBonus();
      this->_range = other.getRange();
      this->_type = other.getType();
      this->_dir = other.getDir();
      this->_x = other.getPosX();
      this->_y = other.getPosY();
      this->_nbplayer = other.getNbPlayer();
    }
  return (*this);
}

Human::~Human()
{}

float	Human::getVecX() const
{
  return (this->_position.x);
}

float	Human::getVecY() const
{
  return (this->_position.y);
}

float	Human::getVecZ() const
{
  return (this->_position.z);
}

void	Human::setVecX(float x)
{
  this->_position.x = x;
}

void	Human::setVecY(float y)
{
  this->_position.y = y;
}

void	Human::setVecZ(float z)
{
  this->_position.z = z;
}

int	Human::getScore() const
{
  return (this->_score);
}

int	Human::getLives() const
{
  return (this->_nbLives);
}

const std::string &	Human::getCurrentBonus() const
{
  return (this->_currentBonus);
}

void	Human::setScore(int s)
{
  this->_score = s;
}

bool	Human::isAlive() const
{
  return (this->_isAlive);
}

bool	Human::haveBonus() const
{
  return (this->_haveBonus);
}

bool	Human::checkPos(int a, int b) const
{
  float x = this->_position.x, z = this->_position.z;
  float	mx = this->_map->getMapSizeX() - 1;
  float mz = this->_map->getMapSizeY() - 1;

  switch (this->_dir)
    {
    case APlayers::Up:
      x = (x - this->getSpeed()) / (2 * FLOOR_WIDTH_SIZE);
      z /= (2 * FLOOR_WIDTH_SIZE);
      a--;
      break;
    case APlayers::Down:
      x = (x + this->getSpeed()) / (2 * FLOOR_WIDTH_SIZE);
      z /= (2 * FLOOR_WIDTH_SIZE); 
      a++;
      break;
    case APlayers::Left:
      z = (z - this->getSpeed()) / (2 * FLOOR_WIDTH_SIZE);
      x /= (2 * FLOOR_WIDTH_SIZE); 
      b--;
      break;
    case APlayers::Right:
      z = (z + this->getSpeed()) / (2 * FLOOR_WIDTH_SIZE);
      x /= (2 * FLOOR_WIDTH_SIZE);
      b++;
      break;
    default: break;
    }
  if (x > mx || x < 0 || z > mz || z < 0)
    return (false);
  return (true);
}

bool	Human::changeDirection(gdl::Keys::Key key)
{
  std::pair<int, int> coord;

  switch (key)
    {
    case gdl::Keys::Right:
      this->_dir = APlayers::Right;
      if (this->checkPos(coord.first, coord.second) == true)
  	{
  	  this->_rotation.y = 180;
  	  this->_position.z += this->_speed;
  	  this->isRunning = true;
  	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
  	  if ((this->_y != coord.first || this->_x != coord.second) && this->isRunning)
  	    {
  	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
  		this->_y++;
  	      else
  		{
  		  this->_model.play("Stop");
  		  this->_position.z -= this->_speed;
  		  this->isRunning = false;
		  return (false);
		  break;
  		}
  	    }
  	  this->_model.play("Run");
  	}
      return (true);
      break;

    case gdl::Keys::D:
      this->_dir = APlayers::Right;
      if (this->checkPos(coord.first, coord.second) == true)
  	{
  	  this->_rotation.y = 180;
  	  this->_position.z += this->_speed;
  	  this->isRunning = true;
  	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
  	  if ((this->_y != coord.first || this->_x != coord.second) && this->isRunning)
  	    {
  	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
  		this->_y++;
  	      else
  		{
  		  this->_model.play("Stop");
  		  this->_position.z -= this->_speed;
  		  this->isRunning = false;
		  return (false);
		  break;
  		}
  	    }
  	  this->_model.play("Run");
  	}
      return (true);
      break;

    case gdl::Keys::Up:
      this->_dir = APlayers::Up;
      if (this->checkPos(coord.first, coord.second) == true)
	{
	  this->_rotation.y = -90;
	  this->_position.x -= this->_speed;
	  this->isRunning = true;
	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
	  if (this->_y != coord.first || this->_x != coord.second)
	    {
	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
		this->_x--;
	      else
  		{
  		  this->_model.play("Stop");
  		  this->_position.x += this->_speed;
  		  this->isRunning = false;
		  return (false);
		  break;
  		}
  	   }
  	 this->_model.play("Run");
       }
      return (true);
      break;

    case gdl::Keys::Z:
      this->_dir = APlayers::Up;
      if (this->checkPos(coord.first, coord.second) == true)
	{
	  this->_rotation.y = -90;
	  this->_position.x -= this->_speed;
	  this->isRunning = true;
	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
	  if (this->_y != coord.first || this->_x != coord.second)
	    {
	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
		this->_x--;
	      else
  		{
  		  this->_model.play("Stop");
  		  this->_position.x += this->_speed;
  		  this->isRunning = false;
		  return (false);
		  break;
  		}
  	   }
  	 this->_model.play("Run");
       }
      return (true);
      break;

    case gdl::Keys::Down:
      this->_dir = APlayers::Down;
      if (this->checkPos(coord.first, coord.second) == true)
  	{
  	  this->_rotation.y = 90;
  	  this->_position.x += this->_speed;
  	  this->isRunning = true;
  	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
  	  if (this->_y != coord.first || this->_x != coord.second)
  	    {
  	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
  		this->_x++;
  	      else
  		{
  		  this->_model.play("Stop");
  		  this->_position.x -= this->_speed;
  		  this->isRunning = false;
		  return (false);
  		}
  	    }
  	  this->_model.play("Run");
  	}
      return (true);
      break;

    case gdl::Keys::S:
      this->_dir = APlayers::Down;
      if (this->checkPos(coord.first, coord.second) == true)
  	{
  	  this->_rotation.y = 90;
  	  this->_position.x += this->_speed;
  	  this->isRunning = true;
  	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
  	  if (this->_y != coord.first || this->_x != coord.second)
  	    {
  	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
  		this->_x++;
  	      else
  		{
  		  this->_model.play("Stop");
  		  this->_position.x -= this->_speed;
  		  this->isRunning = false;
		  return (false);
  		}
  	    }
  	  this->_model.play("Run");
  	}
      return (true);
      break;

    case gdl::Keys::Left:
      this->_dir = APlayers::Left;
      if (this->checkPos(coord.first, coord.second) == true)
  	{
  	  this->_rotation.y = 0;
  	  this->_position.z -= this->_speed;
  	  this->isRunning = true;
  	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
  	  if (this->_y != coord.first || this->_x != coord.second)
  	    {
  	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
  		this->_y--;
  	      else
  		{
  		  this->_model.play("Stop");
  		  this->_position.z += this->_speed;
  		  this->isRunning = false;
		  return (false);
  		}
  	    }
  	  this->_model.play("Run");
  	}
      return (true);
      break;

   case gdl::Keys::Q:
      this->_dir = APlayers::Left;
      if (this->checkPos(coord.first, coord.second) == true)
  	{
  	  this->_rotation.y = 0;
  	  this->_position.z -= this->_speed;
  	  this->isRunning = true;
  	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
  	  if (this->_y != coord.first || this->_x != coord.second)
  	    {
  	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
  		this->_y--;
  	      else
  		{
  		  this->_model.play("Stop");
  		  this->_position.z += this->_speed;
  		  this->isRunning = false;
		  return (false);
  		}
  	    }
  	  this->_model.play("Run");
  	}
      return (true);
      break;

    default:
      return (false);
      break;
    };
}

void	Human::move(gdl::Input & input)
{
  bool	stat = false;

  for (std::vector<gdl::Keys::Key>::iterator it = this->_keys.begin() ; it != this->_keys.end() ; ++it)
    {
      if (stat == false && input.isKeyDown((*it)) == true)
	{
	  if ((*it) == gdl::Keys::F5)
	    this->saveTimer();
	  else if ((*it) == gdl::Keys::RShift || (*it) == gdl::Keys::Tab)
	    this->putBomb();	  
	  else
	    if ((stat = this->changeDirection((*it))) == true)
	      return ;
	}
    }
  this->isRunning = false;
  this->_model.play("Stop");
}

void	Human::destroyObject()
{}

int	Human::getRange() const
{
  return (this->_range);
}

void    Human::setTexture(int id)
{
  id--;
}

void	Human::initialize()
{
  this->isRunning = false;
  this->isBombed = false;
  this->_model = gdl::Model::load("./libgdl_gl-2012.4/assets/marvin.fbx");
  this->_model.cut_animation(this->_model, "Take 001", 0, 0, "Start");
  this->_model.cut_animation(this->_model, "Take 001", 36, 55, "Run");
  this->_model.cut_animation(this->_model, "Take 001", 80, 130, "Stop");
  if (this->_nbplayer == 1)
    {
      gdl::Color    ponpon(0, 255, 0);
      this->_model.set_default_model_color(ponpon);
    }
  else
    {
      gdl::Color    ponpon(0, 0, 255);
      this->_model.set_default_model_color(ponpon);
    }
}

void	Human::update(gdl::GameClock const & clock, gdl::Input & input)
{
  this->_model.update(clock);
  this->move(input);
}

void	Human::draw()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(this->_position.x, this->_position.y, -this->_position.z);
  glRotatef(this->_rotation.y, 0.0f, 1.0f, 0.0f);
  this->_model.draw();
  glPopMatrix();
}

AObjects::typeObject Human::getType() const
{
  return (this->_type);
}

void	Human::setMap(Map *mp)
{
  this->_map = mp;
}

Map* Human::getMap() const
{
  return (this->_map);
}

void	Human::putBomb()
{
  ScopedLock(&(this->_mutex));
  std::pair<int, int>coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);

  switch (this->_dir)
    {
    case APlayers::Up:
      coord.second--;
      break;
    case APlayers::Down:
      coord.second++;
      break;
    case APlayers::Left:
      coord.first--;
      break;
    case APlayers::Right:
      coord.first++;
      break;
    }
  float xBomb = coord.second * FLOOR_WIDTH_SIZE * 2;
  float zBomb = coord.first * FLOOR_WIDTH_SIZE * 2;
  Vector3f	bombPosition(xBomb, this->_position.y, zBomb);
  if (this->_bombDropped < this->_bombStock)
    this->_map->pushBomb(bombPosition, coord, this->_bombRange, this);
}

APlayers::Direction Human::getDir() const
{
  return (this->_dir);
}

void	Human::setPosX(int x)
{
  this->_x = x;
}

void	Human::setPosY(int y)
{
  this->_y = y;
}

int	Human::getPosX() const
{
  return (this->_x);
}

int	Human::getPosY() const
{
  return (this->_y);
}

void    Human::increaseSpeed()
{
  if (this->_speed < 200)
    this->_speed += 5;
}

void    Human::increaseBombRange()
{
  this->_bombRange += 1;
}

void    Human::setKeys()
{
  if (this->_nbplayer == 1)
    {
      this->_keys.push_back(gdl::Keys::Right);
      this->_keys.push_back(gdl::Keys::Up);
      this->_keys.push_back(gdl::Keys::Down);
      this->_keys.push_back(gdl::Keys::Left);
      this->_keys.push_back(gdl::Keys::RShift);
      this->_keys.push_back(gdl::Keys::F5);
    }
  else if (this->_nbplayer == 2)
    {
      this->_keys.push_back(gdl::Keys::D);
      this->_keys.push_back(gdl::Keys::Z);
      this->_keys.push_back(gdl::Keys::S);
      this->_keys.push_back(gdl::Keys::Q);
      this->_keys.push_back(gdl::Keys::Tab);
      this->_keys.push_back(gdl::Keys::F5);
    }
}

int     Human::getNbPlayer() const
{
  return (this->_nbplayer);
}

void	Human::randomBonus(AObjects *o)
{o = o;}

void    Human::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  std::cout << m.size() << std::endl;
}

void    Human::addBomb()
{
  this->_bombStock++;
}

void    Human::addDropped()
{
  this->_bombDropped++;
}

void    Human::rmDropped()
{
  ScopedLock(&(this->_mutex));
  this->_bombDropped--;
}

unsigned int Human::getBombStock() const
{
  return (this->_bombStock);
}

unsigned int Human::getBombDropped() const
{
  return (this->_bombDropped);
}

void    Human::saveTimer()
{
  this->_map->setSave(true);
  Save s;
  s.actualDate();
  s.saveMap(this->_map);
  Timer<Human>  _timer(2500000, &hideSave, this);
}
