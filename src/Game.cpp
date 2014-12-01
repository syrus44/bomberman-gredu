//
// Game.cpp for Game in /home/cerfon_f//taff/branches/cerfoninou
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Mon May  6 17:29:04 2013 florent cerfon
// Last update Fri Jun  7 20:10:38 2013 louis cailleux
//

#include "Thread.hpp"
#include "Game.hh"

void	Game::OpenFile(std::fstream &file, const std::string &fileName)
{
  file.open(fileName.c_str(), std::ios::in | std::ios::out);
  if (file.fail() && errno == 2)
    file.open(fileName.c_str(), std::ios::in | std::ios::out | std::ios::trunc);
}

void	Game::InitClass(const std::string &scoreFile, const std::string &savedGame, const std::string &map)
{
  this->OpenFile(this->_scoreFile, scoreFile);
  this->OpenFile(this->_savedGame, savedGame);
  this->OpenFile(this->_map, map);  
}

Game::Game()
{}

Game::Game(const std::string &scoreFile, const std::string &savedGame, const std::string &map)
{}

Game::~Game()
{
  this->_scoreFile.close();
  this->_savedMap.close();
  this->_map.close();
}
