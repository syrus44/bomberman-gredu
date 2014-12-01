//
// ReadFile.hh for bomberman in /home/caille_l//Documents/merge_map_objects/src
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Tue May  7 18:48:05 2013 louis cailleux
// Last update Sun Jun  9 11:08:55 2013 jordan bettin
//

#ifndef	READFILE_HH_
# define READFILE_HH

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "Exception.hh"

class		ReadFile
{
  std::string	_file;
  std::string	_map;
  std::vector<std::string>	_content;
  unsigned int	_wall;
  unsigned int	_wood;
public:
  ReadFile(std::string const &);
  ReadFile(ReadFile const &);
  ~ReadFile();
  ReadFile&			operator=(ReadFile const &);
  std::string const &		getFileName() const;
  void				setFileName(std::string const &);
  void				openRead();
  void				openWrite(std::string const &);
  void				checkMap() const;
  unsigned int			getWood() const;
  unsigned int			getWall() const;
  std::vector<std::string> const & getMap() const;
};

bool	isElem(char);
bool	player1(char);
bool	player2(char);
bool	isWood(char);
bool	isWall(char);

#endif
