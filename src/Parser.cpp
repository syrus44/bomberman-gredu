//
// Parser.cpp for Bomberman in /home/caille_l//svn/cpp/bomberman/bomberman-gredu/trunk/Bomberman/src
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Wed May 15 18:59:15 2013 louis cailleux
// Last update Sat Jun  8 17:20:28 2013 jordan bettin
//

#include "Parser.hh"
#include "Exception.hh"

Parser::Parser(std::string const &str)
  : _str (str)
{
  this->checkString();
  this->limits();
}

Parser::~Parser()
{}

void	Parser::checkString()
{
  unsigned int	res = count_if(this->_str.begin(), this->_str.end(), isdigit);
  unsigned int i = this->_str.size();
  if (res != i)
    throw Exception("Argument must only contain digits and cannot be negative");
}

void	Parser::limits()
{
  int x;
  std::istringstream val(this->_str);
  
  val >> x;
  if (x >  std::numeric_limits<int>::max())
    throw Exception("Bigger than the size of an integer");
}

int	Parser::getNumber() const
{
  int x;
  std::istringstream val(this->_str);
  
  val >> x;
  return (x);
}
