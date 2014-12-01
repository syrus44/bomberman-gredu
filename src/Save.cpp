//
// Save.cpp for bomberman in /home/caille_l//Documents/merge_map_objects
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Tue May 14 15:05:18 2013 louis cailleux
// Last update Sun Jun  9 11:15:29 2013 jordan bettin
//

#include "Human.hh"

Save::Save()
  : _date(""), _map("")
{}

Save::Save(Save const &other)
{
  this->_date = other.getDate();
}

Save::~Save()
{}

Save &	Save::operator=(Save const &other)
{
  if (&other != this)
    this->_date = other.getDate();
  return (*this);
}

void	Save::saveMap(Map *mp)
{
  std::string file = "./saves/map_"+this->_date;
  ReadFile wr(file);
  
  for (this->yt = mp->getMap().begin(); this->yt != mp->getMap().end(); ++this->yt)
    {
      for (this->xt = this->yt->second.begin(); this->xt != this->yt->second.end(); ++this->xt)
	this->serialize(this->xt->second->getType(), this->xt->second);
      this->_map += '\n';
    }
  this->_map.erase((this->_map.size() - 1), 1);
  wr.openWrite(this->_map);
}

void	Save::replace_spaces()
{
  for (size_t i = 0; i != this->_date.size(); ++i)
    {
      if (this->_date.at(i) == ' ')
	this->_date.replace(i, 1, "_");
    }
}

void	Save::serialize(AObjects::typeObject t, AObjects *o)
{
  switch (t)
    {
    case AObjects::Air:
      this->_map += 'A';
      break;
    case AObjects::Wall:
      this->_map += 'W';
      break;
    case AObjects::WallDestr:
      this->_map += 'D';
	break;
    case AObjects::Bonus:
      this->_map += 'B';
	break;
    case AObjects::Computer:
      this->_map += 'C';
      break;
    case AObjects::Human:
      if (reinterpret_cast<Human *>(o)->getNbPlayer() == 1)
        this->_map += '1';
      else
        this->_map += '2';
      break;
    case AObjects::Bomb:
      this->_map += 'T';
      break;
    default : break; 
    }
}

void	Save::actualDate()
{
  char	*date;
  time_t sec;
  struct tm* instant;

  time(&sec);
  instant = localtime(&sec);
  date = asctime(instant);
  this->_date = date;
  this->_date.erase(this->_date.size() - 1, 1);
  this->replace_spaces();
}

void	Save::setDate(std::string const &str)
{
  this->_date = str;
}

std::string const & Save::getDate() const
{
  return (this->_date);
}
