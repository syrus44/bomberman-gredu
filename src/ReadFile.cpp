//
// ReadFile.cpp for bomberman in /home/caille_l//Documents/merge_map_objects/src
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Tue May  7 18:47:06 2013 louis cailleux
// Last update Sun Jun  9 11:13:44 2013 jordan bettin
//

#include "ReadFile.hh"

ReadFile::ReadFile(std::string const &file)
  : _file (file)
{}

ReadFile::ReadFile(ReadFile const &other)
{
  this->_file = other.getFileName();
}

ReadFile&	ReadFile::operator=(ReadFile const &other)
{
  if (&other != this)
    this->_file = other.getFileName();
  return (*this);
}

std::string const &	ReadFile::getFileName() const
{
  return (this->_file);
}

void	ReadFile::setFileName(std::string const &str)
{
  this->_file = str;
}

void	ReadFile::openRead()
{
  std::ifstream file(this->_file.c_str(), std::ios::in);
  if (file)
    {
      std::string line;
      while (getline(file, line))
	this->_content.push_back(line);
      file.close();
    }
  else
    throw Exception("Map can't be loaded");
}

void	ReadFile::openWrite(std::string const &str)
{
  std::ofstream file(this->_file.c_str(), std::ios::out | std::ios::trunc);
  if (file)
    {
      file << str;
      file.close();
    }
  else
    throw Exception("Map can't be created");
}

void	ReadFile::checkMap() const
{
  unsigned int n = 0, p = 0, a = 0, b = 0;
  unsigned int size = this->_content.front().size();

  if (this->_content.size() < 2)
    throw Exception("Map height is to small");
  
  for (std::vector<std::string>::const_iterator it = this->_content.begin(); it != this->_content.end(); ++it)
    {
      unsigned int count = count_if(it->begin(), it->end(), isElem);
      if (count != it->size() || it->size() != size)
	throw Exception("Invalid map file");
      n += count_if(it->begin(), it->end(), player1);
      p += count_if(it->begin(), it->end(), player2);
      a += count_if(it->begin(), it->end(), isWood);
      b += count_if(it->begin(), it->end(), isWall);
      if (it->size() < 2)
	throw Exception("Map width is too small");
    }
  if (n != 1)
    throw Exception("No player or multiple instances of the same player were declared");
  if (p != 0 && p != 1)
    throw Exception("No player or multiple instances of the same player were declared");
  if (a < 1 || b < 1)
    throw Exception("There must be at least one destructible wall and one wall");
}

std::vector<std::string> const &	ReadFile::getMap() const
{
  return (this->_content);
}

ReadFile::~ReadFile()
{}

bool	isElem(char c)
{
  std::string	pattern("WDAB1CT2");
  return (pattern.find(c) != std::string::npos);
}

bool	player1(char c)
{
  std::string pattern("1");
  return (pattern.find(c) != std::string::npos);
}

bool	player2(char c)
{
  std::string pattern("2");
  return (pattern.find(c) != std::string::npos);
}

bool	isWood(char c)
{
  std::string pattern("D");
  return (pattern.find(c) != std::string::npos);
}

bool	isWall(char c)
{
  std::string pattern("W");
  return (pattern.find(c) != std::string::npos);
}
