//
// Game.hh for Game in /home/cerfon_f//taff/branches/cerfoninou
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Mon May  6 17:29:14 2013 florent cerfon
// Last update Sat Jun  8 17:10:49 2013 jordan bettin
//

#ifndef _GAME_
#define _GAME_

#include <iostream>
#include <fstream>
#include <cerrno>
#include <vector>

class	Game
{
private:
  std::fstream	_scoreFile;
  std::fstream	_savedMap;
  std::fstream	_map;
  void	InitClass(const std::string &, const std::string &, const std::string &);
  void	OpenFile(std::fstream &, const std::string &);

public:
  Game();
  Game(const std::string &, const std::string &, const std::string &);
  ~Game();
};

#endif /* _GAME_ */
