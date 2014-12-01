//
// Parser.hh for Bomberman in /home/caille_l//svn/cpp/bomberman/bomberman-gredu/trunk/Bomberman/src
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Wed May 15 19:00:56 2013 louis cailleux
// Last update Fri Jun  7 22:29:43 2013 louis cailleux
//

#ifndef	PARSER_HH_
# define PARSER_HH_

#include <iostream>
#include <algorithm>
#include <sstream>
#include <limits>

class	Parser
{
  std::string	_str;
public:
  Parser(std::string const &);
  ~Parser();
  void	checkString();
  void	limits();
  int getNumber() const;
};

#endif
