//
// Computer.cpp for Computer in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 15:12:45 2013 jordan bettin
// Last update Sun Jun  9 11:31:44 2013 florent cerfon
//

#include "Computer.hh"
#include "Map.hh"

/* 
** Fonctionnement de l'IA : elle cherche d'abord à obtenir tous les bonus possibles.
** Si elle n'en trouve pas dans les 5 cases autour d'elle, elle détruit les objets (murs ou joueur)
** pour en trouver.
** 
** Elle ne pose qu'une seule bombe à la fois et va se cacher sauf quand elle est dans l'état "bloody"
** L'état "bloody" est un état qui peut survenir un peu n'importe quand, ou si elle ne trouve rien à
** détruire dans les 5 cases autour d'elle. Dans cet état, elle n'hésite pas à courir dans la zone
** d'explosion d'une bombe si nécessaire. Elle ne cible plus que les joueurs quelle que soit la
** distance qui la sépare de ceux-ci et détruira les murs pour la rejoindre si nécessaire.
**
** Dans l'état "bloody" elle posera également une suite de bombes disposées de telle façon qu'elles
** s'explosent mutuellements et que l'explosion prenne le plus de place possible. Elle ne cherchera
** jamais à cibler sa cible directement puisque celle ci est mouvante. L'IA est susceptible de se
** faire sauter elle-meme dans l'état bloody. Ce n'est pas un bug, c'est une feature.
*/

Computer::Computer(Map *m, const int x, const int y, int posx, int posy)
{
  this->_map = m;
  this->_score = 100;
  this->_name = "Comp ";
  this->_isAlive = true;
  this->_bombRange = 2;
  this->_bombStock = 1;
  this->_bombDropped = 0;
  this->_nbLives = 3;
  this->_range = 0;
  this->_type = AObjects::Computer;
  this->_dir = APlayers::Left;
  if (x > y)
    this->_speed = x * 2;
  else
    this->_speed = y * 2;
  this->_x = posx;
  this->_y = posy;
  this->_position = Vector3f(posx * (FLOOR_WIDTH_SIZE * 2), FLOOR_DEEP_SIZE, posy * (FLOOR_WIDTH_SIZE * 2));
  this->bloody = false;
  this->targetX = -1;
  this->playerTargetX = -1;
  this->needToMove = true;
  this->tick = 0;
}

Computer::Computer(const Computer & other) : APlayers(other)
{
  this->_map = other.getMap();
  this->_score = other.getScore();
  this->_name = other.getName();
  this->_bombStock = other.getBombStock();
  this->_bombDropped = other.getBombDropped();
  this->_isAlive = other.isAlive();
  this->_haveBonus = other.haveBonus();
  this->_nbLives = other.getLives();
  this->_currentBonus = other.getCurrentBonus();
  this->_range = other.getRange();
  this->_type = other.getType();
  this->_dir = other.getDir();
  this->_x = other.getPosX();
  this->_y = other.getPosY();
  this->bloody = other.bloody;
  this->targetX = other.targetX;
  this->needToMove = other.needToMove;
  this->tick = other.tick;
}

Computer &	Computer::operator=(const Computer & other)
{
  if (&other != this)
    {
      this->_map = other.getMap();
      this->_score = other.getScore();
      this->_name = other.getName();
      this->_isAlive = other.isAlive();
      this->_bombStock = other.getBombStock();
      this->_bombDropped = other.getBombDropped();
      this->_haveBonus = other.haveBonus();
      this->_nbLives = other.getLives();
      this->_currentBonus = other.getCurrentBonus();
      this->_range = other.getRange();
      this->_type = other.getType();
      this->_dir = other.getDir();
      this->_x = other.getPosX();
      this->_y = other.getPosY();
      this->bloody = other.bloody;
      this->targetX = other.targetX;
      this->needToMove = other.needToMove;
      this->tick = other.tick;
    }
  return (*this);
}

Computer::~Computer()
{}

float	Computer::getVecX() const
{
  return (this->_position.x);
}

float	Computer::getVecY() const
{
  return (this->_position.y);
}

float	Computer::getVecZ() const
{
  return (this->_position.z);
}

int	Computer::getScore() const
{
  return (this->_score);
}

int	Computer::getLives() const
{
  return (this->_nbLives);
}

const std::string &	Computer::getCurrentBonus() const
{
  return (this->_currentBonus);
}

void	Computer::setScore(int s)
{
  this->_score = s;
}

void	Computer::setVecX(float x)
{
  this->_position.x = x;
}

void	Computer::setVecY(float y)
{
  this->_position.y = y;
}

void	Computer::setVecZ(float z)
{
  this->_position.z = z;
}

bool	Computer::haveBonus() const
{
  return (this->_haveBonus);
}

bool	Computer::checkPos(int a, int b) const
{
  float	x = this->_position.x, z = this->_position.z;
  float	mx = this->_map->getMapSizeX() - 1;
  float	mz = this->_map->getMapSizeY() - 1;

  switch (this->_dir)
    {
    case APlayers::Up:
      x = (x - 5) / (2 * FLOOR_WIDTH_SIZE);
      z /= (2 * FLOOR_WIDTH_SIZE);
      a--;
      break;

    case APlayers::Down:
      x = (x + 5) / (2 * FLOOR_WIDTH_SIZE);
      z /= (2 * FLOOR_WIDTH_SIZE);
      a++;
      break;

    case APlayers::Left:
      z = (z - 5) / (2 * FLOOR_WIDTH_SIZE);
      x /= (2 * FLOOR_WIDTH_SIZE);
      b--;
      break;

    case APlayers::Right:
      z = (z + 5) / (2 * FLOOR_WIDTH_SIZE);
      x /= (2 * FLOOR_WIDTH_SIZE);
      b++;
      break;

    default: break;
    }
  if (x > mx || x <= 0 || z >= mz || z <= 0)
    return (false);
  return (true);
}

/*
** Fonction permettant d'expliciter le chemin choisit par l'IA pour détruire un bloc.
*/

void	Computer::readDestrToGo() const
{
  elmpath			tmp;
  int				i = 0;

  std::cout << std::endl << std::endl;
  for (std::list<elmpath>::const_iterator xt = this->blowPath.begin(); xt != this->blowPath.end(); ++xt)
    {
      tmp = *xt;
      i++;
      std::cout << "case number " << i << " : x = " << tmp.x << " y = " << tmp.y << std::endl;
    }  
  std::cout << std::endl << std::endl;
}

void	Computer::readEmergencyToGo() const
{
  elmpath			tmp;
  int				i = 0;

  std::cout << std::endl << std::endl;
  for (std::list<elmpath>::const_iterator xt = this->emergencyPath.begin(); xt != this->emergencyPath.end(); ++xt)
    {
      tmp = *xt;
      i++;
      std::cout << "case number " << i << " : x = " << tmp.x << " y = " << tmp.y << std::endl;
    }  
  std::cout << std::endl << std::endl;
}

/*
** Fonction transitaire de la récursivité de chooseDestrToGo.
** Vérifie que le segment n'a pas déjà été checké
*/

int	Computer::CheckIfAlreadyPathed(int x, int y, int i, std::map<int, std::map<int, AObjects *> > &mp, std::list<elmpath> &path)
{
  elmpath			tmp;

  if (!(y > -1 && x > -1 && x < this->_map->getMapSizeY() && y < this->_map->getMapSizeX()) || (mp[y][x]->getType() != AObjects::Air && mp[y][x]->getType() != AObjects::Bonus))
    return (0);
  for (std::list<elmpath>::iterator xt = path.begin(); xt != path.end(); ++xt)
    {
      tmp = *xt;
      if (tmp.x == x && tmp.y == y)
	return (0);
    }

  return (this->chooseDestrToGo(x, y, i, mp, path));
}

void	Computer::EmergencyAlreadyPathed(int x, int y, int i, std::map<int, std::map<int, AObjects *> > &mp, std::list<elmpath> &path)
{
  elmpath			tmp;

  if (!(y > -1 && x > -1 && x < this->_map->getMapSizeY() && y < this->_map->getMapSizeX()) || mp[y][x]->getType() != AObjects::Air)
    return;
  for (std::list<elmpath>::iterator xt = path.begin(); xt != path.end(); ++xt)
    {
      tmp = *xt;
      if (tmp.x == x && tmp.y == y)
	return;
    }

  this->getToCover(x, y, i, mp, path);
}

/*
** Algorithme de recherche d'objet destructible dans les 5 cases autour de l'IA. i étant le nombre
** de cases parcourues jusqu'ici.
*/

int	Computer::chooseDestrToGo(int x, int y, int i, std::map<int, std::map<int, AObjects *> >mp, std::list<elmpath> path)
{
  elmpath	block;
  block.x = x;
  block.y = y;

  path.push_back(block);

  if ((x > 0 && mp[y][x - 1]->getType() >= AObjects::WallDestr && (y != this->_x && x - 1 != this->_y)) ||
      (x + 1 < this->_map->getMapSizeY() && mp[y][x + 1]->getType() >= AObjects::WallDestr && (y != this->_x && x + 1 != this->_y)) ||
      (y + 1< this->_map->getMapSizeX() && mp[y + 1][x]->getType() >= AObjects::WallDestr && (y + 1 != this->_x && x != this->_y)) ||
      (y && mp[y - 1][x]->getType() >= AObjects::WallDestr && (y - 1 != this->_x && x != this->_y)))
    {

      if (this->blowPath.size() == 0 || this->blowPath.size() > path.size())
	{
	  this->targetX = x;
	  this->targetY = y;
	  this->blowPath = path;
	}
      return (1);
    }

  if (i < 5)
    {
      this->CheckIfAlreadyPathed(x + 1, y, i + 1, mp, path);
      this->CheckIfAlreadyPathed(x - 1, y, i + 1, mp, path);
      this->CheckIfAlreadyPathed(x, y + 1, i + 1, mp, path);
      this->CheckIfAlreadyPathed(x, y - 1, i + 1, mp, path);
    }

  return (0);
}

bool	Computer::isThisPlaceSafe(int x, int y, std::map<int, std::map<int, AObjects *> > &mp) const
{
  AObjects::typeObject	type;

  if (x < 0 || y < 0 || y >= this->_map->getMapSizeX() || x >= this->_map->getMapSizeY())
    return (false);

  for (int i = y  ; i < y + 4 && i < this->_map->getMapSizeX() ; ++i)
    {
      type = mp[i][x]->getType();
      if (type == AObjects::Bomb)
	return (false);
    }

  for (int i = y  ; i > y - 4 && i >= 0 ; --i)
    {
      type = mp[i][x]->getType();
      if (type == AObjects::Bomb)
	return (false); 
      if (type != AObjects::Air && type != AObjects::Explosion && !(type >= AObjects::Computer))
	break;
    }

  for (int i = x  ; i < x + 4 && i < this->_map->getMapSizeY() ; ++i)
    {
      type = mp[y][i]->getType();
      if (type == AObjects::Bomb)
	return (false);
      if (type != AObjects::Air && type != AObjects::Explosion && !(type >= AObjects::Computer))
	break;
    }

  for (int i = x  ; i > x - 4 && i >= 0 ; --i)
    {
      type = mp[y][i]->getType();
      if (type == AObjects::Bomb)
	return (false);
      if (type != AObjects::Air && type != AObjects::Explosion && !(type >= AObjects::Computer))
	break;
    }

  return (true);
}

void	Computer::getToCover(int x, int y, int i, std::map<int, std::map<int, AObjects *> > &mp, std::list<elmpath> path)
{
  elmpath	block;
  block.x = x;
  block.y = y;

  i++;
  path.push_back(block);

  if (this->isThisPlaceSafe(x, y, mp))
    {
      if (this->emergencyPath.size() == 0 || this->emergencyPath.size() > path.size())
	this->emergencyPath = path;
      return;
    }


  if (i < 6)
    {
      this->EmergencyAlreadyPathed(x + 1, y, i, mp, path);
      this->EmergencyAlreadyPathed(x - 1, y, i, mp, path);
      this->EmergencyAlreadyPathed(x, y + 1, i, mp, path);
      this->EmergencyAlreadyPathed(x, y - 1, i, mp, path);
    }
}

/* L'IA se dirige vers sa cible à détruire. Si elle n'en a pas, elle en cherche une */

void	Computer::chooseDirectionToGo()
{
  std::map<int, std::map<int, AObjects *> >	mp = this->_map->getMap();
  std::list<elmpath>				path;
  elmpath					tmp;

  this->tick = 0;
  this->needToMove = true;

  if (this->blowPath.size() == 0 && this->escapePath.size() == 0 && this->emergencyPath.size() == 0)
    {
      if (this->isThisPlaceSafe(this->_y, this->_x, mp))
	{
	  if (this->_bombDropped == this->_bombStock)
	    this->needToMove = false;
	  else
	    this->chooseDestrToGo(this->_y, this->_x, 0, mp, path);
	}
      else
	getToCover(this->_y, this->_x, 0, mp, path);
    }

  if (this->emergencyPath.size() != 0)
    {
      this->emergencyPath.pop_front();
      tmp = this->emergencyPath.front();
      if (this->emergencyPath.size() == 0)
	this->needToMove = false;
    }
  else if (this->blowPath.size() != 0)
    {
      this->blowPath.pop_front();
      tmp = this->blowPath.front();
    }
  else
    {
      this->needToMove = false;
      return;
    }

  if (tmp.x > -1 && tmp.x < this->_map->getMapSizeY() && tmp.y > -1 && tmp.y < this->_map->getMapSizeX() && mp[tmp.y][tmp.x]->getType() == AObjects::Explosion)
    {
      this->needToMove = false;
      return;
    }

  DIR(tmp.x, this->_y, tmp.y, this->_x);
  if (this->blowPath.size() == 1)
    {
      this->putBomb();
      this->blowPath.pop_front();
      mp = this->_map->getMap();
      if (this->_bombDropped < this->_bombStock)
	this->chooseDestrToGo(this->_y, this->_x, 0, mp, path);
      else
	this->getToCover(this->_y, this->_x, 0, mp, path);
    }
}

/* 
** L'IA réfléchit à propos de sa direction chaque fois qu'elle change de case ou tous les 
** 50 "ticks" d'inactivité
*/

void	Computer::move(gdl::Input __attribute__((unused)) & input)
{
  std::pair<int, int> coord;
  this->tick++;

  if (this->tick == TICK_DIFFICULTY)
    this->chooseDirectionToGo();

  if (!this->needToMove)
    return;

  switch (this->_dir)
    {
    case APlayers::Right:
      if (this->checkPos(coord.first, coord.second) == true)
	{
	  this->_rotation.y = 180;
	  this->_position.z += this->_speed;
	  this->isRunning = true;
	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
	  if ((this->_y != coord.first || this->_x != coord.second) && this->isRunning)
	    {
	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
		{
		  this->_y++;
		  this->chooseDirectionToGo();
		}
	      else
		{
		  this->_model.play("Stop");
		  this->_position.z -= this->_speed;
		  this->isRunning = false;
		  break;
		}
	    }
	  this->_model.play("Run");
	}
      break;

    case APlayers::Up:
      if (this->checkPos(coord.first, coord.second) == true)
	{
	  this->_rotation.y -= 90;
	  this->_position.x -= this->_speed;
	  this->isRunning = true;
	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
	  if (this->_y != coord.first || this->_x != coord.second)
	    {
	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
		{
		  this->_x--;
		  this->chooseDirectionToGo();
		}
	      else
		{
		  this->_model.play("Stop");
		  this->_position.x += this->_speed;
		  this->isRunning = false;
		  break;
		}
	    }
	  this->_model.play("Run");
	}
      break;

    case APlayers::Down:
      if (this->checkPos(coord.first, coord.second) == true)
	{
	  this->_rotation.y = 90;
	  this->_position.x += this->_speed;
	  this->isRunning = true;
	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
	  if (this->_y != coord.first || this->_x != coord.second)
	    {
	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
		{
		  this->_x++;
		  this->chooseDirectionToGo();
		}
	      else
		{
		  this->_model.play("Stop");
		  this->_position.x -= this->_speed;
		  this->isRunning = false;
		  break;
		}
	    }
	  this->_model.play("Run");
	}
      break;

    case APlayers::Left:
      if (this->checkPos(coord.first, coord.second) == true)
	{
	  this->_rotation.y = 0;
	  this->_position.z -= this->_speed;
	  this->isRunning = true;
	  coord = this->_map->get2Dcoord(this->_position.x, this->_position.z);
	  if (this->_y != coord.first || this->_x != coord.second)
	    {
	      if (this->_map->MovePlayer(this->_y, this->_x, coord.first, coord.second))
		{
		  this->_y--;
		  this->chooseDirectionToGo();
		}
	      else
		{
		  this->_position.z += this->_speed;
		  this->isRunning = false;
		  break;
		}
	    }
	  this->_model.play("Run");
	}
      break;

    default:
      this->isRunning = false;
      this->_model.play("Stop");
      break;
    };
}

void	Computer::destroyObject()
{
  if (this->_isAlive)
    {
      this->_isAlive = false;
    }
}

int	Computer::getRange() const
{
  return (this->_range);
}

void    Computer::setTexture(int id)
{
  id--;
}

void	Computer::initialize()
{
  this->isRunning = false;
  this->isBombed = false;
  this->_model = gdl::Model::load("./libgdl_gl-2012.4/assets/marvin.fbx");
  this->_model.cut_animation(this->_model, "Take 001", 0, 0, "Start");
  this->_model.cut_animation(this->_model, "Take 001", 36, 55, "Run");
  this->_model.cut_animation(this->_model, "Take 001", 80, 130, "Stop");
  gdl::Color	ponpon(255, 255, 0);
  this->_model.set_default_model_color(ponpon);
}

void	Computer::update(gdl::GameClock const & clock, gdl::Input & input)
{
  this->_model.update(clock);
  this->move(input);
}

void	Computer::draw()
{
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslatef(this->_position.x, this->_position.y, -this->_position.z);
  glRotatef(this->_rotation.y, 0.0f, 1.0f, 0.0f);
  this->_model.draw();
  glPopMatrix();
}

AObjects::typeObject Computer::getType() const
{
  return (this->_type);
}

void	Computer::setMap(Map *mp)
{
  this->_map = mp;
}

void	Computer::putBomb()
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
  Vector3f	bombPosition(xBomb, WALL_DEEP_SIZE * 2, zBomb);
  if (this->_bombDropped < this->_bombStock)
    this->_map->pushBomb(bombPosition, coord, this->_bombRange, this);
}

Map * Computer::getMap() const
{
  return (this->_map);
}

APlayers::Direction Computer::getDir() const
{
  return (this->_dir);
}

void	Computer::setPosX(int x)
{
  this->_x = x;
}

void	Computer::setPosY(int y)
{
  this->_y = y;
}

int	Computer::getPosX() const
{
  return (this->_x);
}

int	Computer::getPosY() const
{
  return (this->_y);
}

void    Computer::increaseSpeed()
{
  this->_speed += 5;
}

void    Computer::increaseBombRange()
{
  this->_bombRange += 1;
}

void	Computer::randomBonus(AObjects *o)
{o = o;}

void    Computer::setMap(std::map<int, std::map<int, AObjects *> > const & m)
{
  std::cout << m.size() << std::endl;
}

void    Computer::addBomb()
{
  this->_bombStock++;
}

void    Computer::addDropped()
{
  this->_bombDropped++;
}

void    Computer::rmDropped()
{
  this->_bombDropped--;
}

unsigned int Computer::getBombStock() const
{
  return (this->_bombStock);
}

unsigned int Computer::getBombDropped() const
{
  return (this->_bombDropped);
}
