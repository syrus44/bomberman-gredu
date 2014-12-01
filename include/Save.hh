//
// Save.hh for bomberman in /home/caille_l//Documents/merge_map_objects
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Tue May 14 15:05:44 2013 louis cailleux
// Last update Sun Jun  9 11:15:34 2013 jordan bettin
//

#include <iostream>
#include <ctime>
#include <map>
#include "AObjects.hh"
#include "Map.hh"

class	Save
{
  std::string	_date;
  std::string	_map;
  std::map<int, std::map<int, AObjects *> >::const_iterator yt;
  std::map<int, AObjects *>::const_iterator xt;
  
public:
  Save();
  Save(Save const &);
  ~Save();
  Save &operator=(Save const &);
  void setDate(std::string const &);
  std::string const & getDate() const;
  void actualDate();
  void replace_spaces();
  void saveMap(Map *);
  void serialize(AObjects::typeObject, AObjects *);
};
