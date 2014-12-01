//
// Map.cpp for  in /home/dugast_a//CPP/Bomberman/bomberman-gredu/trunk/Ant
// 
// Made by antoine dugast
// Login   <dugast_a@epitech.net>
// 
// Started on  Thu May  2 15:04:00 2013 antoine dugast
// Last update Sun Jun  9 11:13:14 2013 jordan bettin
//

#include	"Map.hh"
#include	"Bomb.hh"
#include	"Computer.hh"
#include	"Bonus.hh"
#include	"Human.hh"
#include	"Ashes.hh"
#include	"Explosion.hh"
#include	"Air.hh"
#include	"Menu.hh"

Map::Map()
{
  this->mapSizeX = 0;
  this->mapSizeY = 0;
  this->t = 0;
  this->t2 = 0;
  this->_menu = new Menu(this);
  this->mapAir = new Air(0, 0);
  this->isAlone = false;
}

Map::~Map()
{
  delete (this->mapAir);
}

void	Map::lock()
{
  this->_mutex.lock();
}

void	Map::unlock()
{
  this->_mutex.unlock();  
}

void	Map::mapFile()
{
  ReadFile	rd(this->_filename);
  std::vector<std::string>	mp;
  int	x = 0;
  int	y = 0;

  rd.openRead();
  rd.checkMap();
  mp = rd.getMap();
  this->_players = 0;
  this->map.erase(this->map.begin(), this->map.end());
  for (std::vector<std::string>::iterator it = mp.begin(); it != mp.end(); ++it)
    {
      std::map<int, AObjects *> obj;
      for (std::string::iterator jt = it->begin(); jt != it->end(); ++jt)
	{
	  obj.insert(std::make_pair(y, this->createObj(*(jt), x, y)));
	  ++y;
	}
      y = 0;
      this->map.insert(std::make_pair(x, obj));
      this->mapSizeY = obj.size();
      ++x;
    }
  this->mapSizeX = this->map.size();
  this->mapFloor = new Floor(0, 0, this->mapSizeX, this->mapSizeY);
  this->mapWall->setMap(this->map);
  this->destWall->setMap(this->map);
}

void    Map::pushBomb(Vector3f const &position, std::pair<int, int> const & p, int range, APlayers *pl)
{
  if (p.first >= 0 && p.first < this->mapSizeY && p.second >= 0 && p.second < this->mapSizeX)
    {
      if (getObj(p.first, p.second)->getType() == AObjects::Air)
        {
          Bomb *b = new Bomb(this, position, p, pl);
          b->setRange(range);
          this->addObj(p.first, p.second, b);
          b->initialize();
          b->draw();
        }
    }
}

AObjects	*Map::createObj(char c, int x, int y)
{
  AObjects	*obj;

  switch (c)
    {
    case 'W':
      obj = this->mapWall;
      break;
    case 'D':
      obj = this->destWall;
      break;
    case 'T':
      obj = new Bomb(this, Vector3f(y * FLOOR_WIDTH_SIZE * 2, FLOOR_WIDTH_SIZE, x * FLOOR_WIDTH_SIZE * 2), std::make_pair(y, x), NULL);
      break;
    case 'A':
      obj = this->mapAir;
      break;
    case '1':
      this->_players++;
      obj = new Human(this, this->mapSizeX, this->mapSizeY, x, y, 1);
      this->player = obj;
      break;
    case '2':
      this->_players++;
      obj = new Human(this, this->mapSizeX, this->mapSizeY, x, y, 2);
      this->player2 = obj;
      break;
    case 'C':
      this->_AI++;
      obj = new Computer(this, this->mapSizeX, this->mapSizeY, x, y);
      break;
    case 'B':
      obj = new Bonus(x, y);
      break;
    default: obj = this->mapAir;
    }
  this->initCoord(obj, x, y);
  obj->setVecX(x * 300);
  obj->setVecZ(y * 300);
  return (obj);
}

void	Map::initMap()
{
  int   x;
  int   y;
  
  this->map.erase(this->map.begin(), this->map.end());
  for (x = 0; x < this->mapSizeX; ++x)
    {
      std::map<int, AObjects *> mp;
      for (y = 0; y < this->mapSizeY; ++y)
        mp.insert(std::make_pair(y, this->mapAir));
      this->map.insert(std::make_pair(x, mp));
    }
  this->fillRandom();
  this->putBonus();
  this->putAI();
  AObjects* player1 = new Human(this, this->mapSizeX, this->mapSizeY, 2, 2, 1);
  this->initCoord(player1, 2, 2);
  this->addObj(2, 2, player1);
  if (this->_players == 2)
    {
      AObjects* player2 = new Human(this, this->mapSizeX, this->mapSizeY, 1, 1, 2);
      this->initCoord(player2, 1, 1);
      this->addObj(1, 1, player2);
    }
  this->mapFloor = new Floor(0, 0, this->mapSizeX, this->mapSizeY);
  this->mapWall->setMap(this->map);
  this->destWall->setMap(this->map);
}

void	Map::addObj(int px, int py, AObjects *obj)
{
  for (this->yt = this->map.begin(); this->yt != this->map.end(); ++this->yt)
    {
      for (this->xt = this->yt->second.begin(); this->xt != this->yt->second.end(); ++this->xt)
	if (this->xt->first == px && this->yt->first == py)
	  this->xt->second = obj;
    }
}

void	Map::fillRandom()
{
  for (this->yt = this->map.begin(); this->yt != this->map.end(); ++this->yt)
    {
      for (this->xt = this->yt->second.begin(); this->xt != this->yt->second.end(); ++this->xt)
	if ((this->xt->first + this->yt->first + random() % 2) % 2 == 0)
	  {
	    this->randomObject();
	    this->initCoord(this->xt->second, -1, -1);
	  }
    }
}

void    Map::initCoord(AObjects *obj, int x, int y)
{
  if (x == -1 && y == -1)
    {
      obj->setVecX(this->yt->first * 300);
      obj->setVecZ(this->xt->first * 300);
    }
  else
    {
      obj->setVecX(y * 300);
      obj->setVecZ(x * 300);
    }
  obj->setVecY(200);
  obj->setTexture(this->_texture);
  obj->initialize();
}

void	Map::blow(int x, int y, int range)
{
  // On considère que meme si cela ne se produira surement jamais,
  // un objet qui a une range de 0 peut quand meme s exploser lui meme

  ScopedLock(&(this->_mutex));
  if (range > -1)		  
    this->Deflagration(x, y, range);
}

void	Map::Deflagration(int x, int y, int range)
{
  // Destruction des objets sur l'axe Y (coord 2D)

  this->mapExpl = new Explosion(this, 0, 0);
  this->_sound.playBombe();
  this->addObj(x, y, this->mapExpl);
  for (int tmp = y ; tmp <= y + range ; ++tmp)
    {
      if (tmp > -1 && tmp < this->map.end()->first)
        {
          if (this->map[tmp][x]->getType() > AObjects::Destructible && this->map[tmp][x]->getType() < AObjects::Through)
            {
	      this->player->setScore(this->player->getScore() + 10);
              this->rmObj(x, tmp);
              this->addObj(x, tmp, this->mapExpl);
              if (tmp != y)
                break;
            }
          else if (this->map[tmp][x]->getType() == AObjects::Air || this->map[tmp][x]->getType() > AObjects::Through || this->map[tmp][x]->getType() == AObjects::Explosion)
	    {
	      if (this->map[tmp][x]->getType() < AObjects::Through && this->map[tmp][x]->getType() != AObjects::Explosion)
		this->addObj(x, tmp, this->mapExpl);
	      else
		{
		  if (this->map[tmp][x]->getType() != AObjects::Explosion)
		    this->player->setScore(this->player->getScore() + 100);
                  this->rmObj(x, tmp);
                  this->addObj(x, tmp, this->mapExpl);
                }
	    }
	  else
	    break;
        }
    }

  for (int tmp = y - 1; tmp >= y - range ; --tmp)
    {
      if (tmp > -1 && tmp < this->map.end()->first)
        {
          if (this->map[tmp][x]->getType() > AObjects::Destructible && this->map[tmp][x]->getType() < AObjects::Through)
            {
	      this->player->setScore(this->player->getScore() + 10);
              this->rmObj(x, tmp);
              this->addObj(x, tmp, this->mapExpl);
              break;
            }
          else if (this->map[tmp][x]->getType() == AObjects::Air || this->map[tmp][x]->getType() > AObjects::Through || this->map[tmp][x]->getType() == AObjects::Explosion)
	    {
	      if (this->map[tmp][x]->getType() < AObjects::Through && this->map[tmp][x]->getType() != AObjects::Explosion)
		this->addObj(x, tmp, this->mapExpl);
	      else
		{
		  if (this->map[tmp][x]->getType() != AObjects::Explosion)
		    this->player->setScore(this->player->getScore() + 100);
		  this->rmObj(x, tmp);
		  this->addObj(x, tmp, this->mapExpl);
		}
	    }
	  else
	    break;
        }
    }

  // Destruction des objets sur l'axe X (coord 2D)

  for (int tmp = x + 1; tmp <= x + range ; ++tmp)
    {
      if (tmp > -1 && tmp < this->map[0].end()->first)
        {
          if (this->map[y][tmp]->getType() > AObjects::Destructible && this->map[y][tmp]->getType() < AObjects::Through)
	    {
	      this->player->setScore(this->player->getScore() + 10);
              this->rmObj(tmp, y);
              this->addObj(tmp, y, this->mapExpl);
              break;
            }
	  else if (this->map[y][tmp]->getType() == AObjects::Air || this->map[y][tmp]->getType() > AObjects::Through || this->map[y][tmp]->getType() == AObjects::Explosion)
	    {
	      if (this->map[y][tmp]->getType() < AObjects::Through && this->map[y][tmp]->getType() != AObjects::Explosion)
		this->addObj(tmp, y, this->mapExpl);
	      else		  
		{
		  if (this->map[y][tmp]->getType() != AObjects::Explosion)
		    this->player->setScore(this->player->getScore() + 100);
		  this->rmObj(tmp, y);
		  this->addObj(tmp, y, this->mapExpl);
		}
	    }
	  else
	    break;
        }
    }

  for (int tmp = x - 1; tmp >= x - range ; --tmp)
    {
      if (tmp > -1 && tmp < this->map[0].end()->first)
        {
          if (this->map[y][tmp]->getType() > AObjects::Destructible && this->map[y][tmp]->getType() < AObjects::Through)
            {
	      this->player->setScore(this->player->getScore() + 10);
              this->rmObj(tmp, y);
              this->addObj(tmp, y, this->mapExpl);
              break;
            }
          else if (this->map[y][tmp]->getType() == AObjects::Air || this->map[y][tmp]->getType() > AObjects::Through || this->map[y][tmp]->getType() == AObjects::Explosion)
	    {
	      if (this->map[y][tmp]->getType() < AObjects::Through && this->map[y][tmp]->getType() != AObjects::Explosion)
		this->addObj(tmp, y, this->mapExpl);
	      else
		{
		  if (this->map[y][tmp]->getType() != AObjects::Explosion)
		    this->player->setScore(this->player->getScore() + 100);
		  this->rmObj(tmp, y);
		  this->addObj(tmp, y, this->mapExpl);
		}
	    }
          else
            break;
        }
    }
  this->mapExpl->setMap(this->map);
}

void	Map::rmExpl()
{
  std::map<int, std::map<int, AObjects *> >::iterator   y;
  std::map<int, AObjects *>::iterator                   x;

  for (y = this->map.begin(); y != this->map.end(); ++y)
    {
      for (x = y->second.begin(); x != y->second.end(); ++x)
        {
          if (x->second->getType() == AObjects::Explosion)
	    x->second = this->mapAir;
	}
    }
}

void	Map::rmObj(int px, int py)
{
  std::map<int, std::map<int, AObjects *> >::iterator	y;
  std::map<int, AObjects *>::iterator			x;
  AObjects						*old;

  for (y = this->map.begin(); y != this->map.end(); ++y)
    {
      for (x = y->second.begin(); x != y->second.end(); ++x)
	{
	  if (x->first == px && y->first == py)
	    {
	      old = x->second;
              if (x->second->getType() == AObjects::Human)
		{
		  if (this->_players != 1) 
		    this->_players--;
		  x->second = new Ashes(this, px, py);
		}
	      else
                {
                  if (x->second->getType() == AObjects::Computer)
		    this->_AI--;
		  x->second = this->mapAir;
                }
	      old->destroyObject();
	    }
	}
    }
}

void	Map::freeMap()
{
  for (this->yt = this->map.begin(); this->yt != this->map.end(); ++this->yt)
    {
      for (this->xt = this->yt->second.begin(); this->xt != this->yt->second.end(); ++this->xt)
	if (this->xt->second && this->xt->second->getType() != AObjects::Air &&
            this->xt->second->getType() != AObjects::Wall && this->xt->second->getType() != AObjects::WallDestr && this->xt->second->getType() != AObjects::Explosion)
	  delete (this->xt->second);
    }
}

void	Map::randomObject()
{
  unsigned int	n;

  switch ((n = random() % 3))
    {
    case 0:
      this->xt->second = this->mapWall;
      break;
    case 1:
      this->xt->second = this->destWall;
      break;
    default: this->xt->second = this->mapAir;
    }
}

void	Map::affMap()
{
  for (this->yt = this->map.begin(); this->yt != this->map.end(); ++this->yt)
    {
      for (this->xt = this->yt->second.begin(); this->xt != this->yt->second.end(); ++this->xt)
	std::cout << this->xt->second->getName();
      std::cout << std::endl;
    }
  std::cout << std::endl;
}

AObjects	*Map::getObj(int px, int py)
{
  std::map<int, AObjects *>::iterator x;
  std::map<int, std::map<int, AObjects *> >::iterator y;

  for (y = this->map.begin(); y != this->map.end(); ++y)
    {
      for (x = y->second.begin(); x != y->second.end(); ++x)
	{
	  if (x->first == px && y->first == py)
	    return (x->second);
	}
    }
  return (NULL);
}

void	Map::setObj(int px, int py, AObjects *obj)
{
  std::map<int, AObjects *>::iterator x;
  std::map<int, std::map<int, AObjects *> >::iterator y;

  for (y = this->map.begin(); y != this->map.end(); ++y)
    {
      for (x = y->second.begin(); x != y->second.end(); ++x)
	if (x->first == px && y->first == py)
	  x->second = obj;
    }
}

int	Map::getMapSizeX() const
{
  return (this->mapSizeX);
}

int	Map::getMapSizeY() const
{
  return (this->mapSizeY);
}

std::map<int, std::map<int, AObjects *> > const & Map::getMap() const
{
  return (this->map);
}

AObjects	*Map::getHuman(int player)
{
  std::map<int, AObjects *>::iterator x;
  std::map<int, std::map<int, AObjects *> >::iterator y;

  for (y = this->map.begin(); y != this->map.end(); ++y)
    {
      for (x = y->second.begin(); x != y->second.end(); ++x)
	{
	  if (x->second && x->second->getType() == AObjects::Human)
	    {
	      if (player == 1)
		return (x->second);
	      player++;
	    }
	}
    }
  return (NULL);
}

std::pair<int, int> const 	Map::get2Dcoord(float x, float z) const
{
  std::map<int, AObjects *>::const_iterator xt;
  std::map<int, std::map<int, AObjects *> >::const_iterator yt;
  
  return (std::pair<int, int>(std::make_pair((z + FLOOR_WIDTH_SIZE) / (FLOOR_WIDTH_SIZE * 2), (x + FLOOR_WIDTH_SIZE) / (FLOOR_WIDTH_SIZE * 2))));
}

bool    Map::MovePlayer(int oldpx, int oldpy, int px, int py)
{
  std::map<int, std::map<int, AObjects *> >::iterator y;
  std::map<int, AObjects *>::iterator x;

  for (y = this->map.begin(); y != this->map.end(); ++y)
    {
      for (x = y->second.begin(); x != y->second.end(); ++x)
        {
          if (x->first == oldpx && y->first == oldpy)
            {
              AObjects *t = this->getObj(px, py);
              if (t->getType() == AObjects::Air || t->getType() == AObjects::Bonus)
                {
		  this->_sound.playFootStep();
                  AObjects *tmp = this->getObj(oldpx, oldpy);
                  if (t->getType() == AObjects::Bonus)
		    {
		      t->randomBonus(tmp);
		      this->_sound.playBonus();
		      this->player->setScore(this->player->getScore() + 5);
		    }
                  x->second = this->mapAir;
                  this->setObj(px, py, tmp);
                  return (true);
                }
	      if (t->getType() == AObjects::Explosion)
		this->rmObj(oldpx, oldpy);
              return (false);
            }
        }
    }
  return (false);
}

int	Map::getPlayers() const
{
  return (this->_players);
}

void    Map::setSave(bool b)
{
  this->tosave = b;
}

void	Map::putAI()
{
  for (unsigned int AI = this->_menu->getAI(); AI != 0; --AI)
    {
      size_t rx = random() % (this->mapSizeX - 1);
      size_t ry = random() % (this->mapSizeY - 1);
      AObjects *o = new Computer(this, this->mapSizeX, this->mapSizeY, ry, rx);
      o->initialize();
      this->addObj(rx, ry, o);
      this->_AI++;
    }
}

void	Map::putBonus()
{
  for (unsigned int BN = this->mapSizeX; BN != 0; --BN)
    {
      size_t rx = random() % (this->mapSizeX - 1);
      size_t ry = random() % (this->mapSizeY - 1);
      AObjects *o = new Bonus(rx, ry);
      initCoord(o, rx, ry);
      this->addObj(rx, ry, o);
    }
}

int	Map::countAI()
{
  int AI = 0;

  for (this->yt = this->map.begin(); this->yt != this->map.end(); ++this->yt)
    {
      for (this->xt = this->yt->second.begin(); this->xt != this->yt->second.end(); ++this->xt)
	if (this->xt->second->getType() == AObjects::Computer)
	  AI++;
    }
  return (AI);
}
