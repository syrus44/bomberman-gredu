//
// Human.hh for Human in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 15:05:22 2013 jordan bettin
// Last update Sat Jun  8 21:09:41 2013 jordan bettin
//

#ifndef HUMAN_HH
#define HUMAN_HH

#include "APlayers.hh"
#include "Save.hh"
#include "Timer.hpp"
#include "Map.hh"

class	Human : public APlayers
{
  bool	_isAlive;
  bool	_haveBonus;
  int	_nbLives;
  std::string _currentBonus;
  bool	isRunning;
  bool	isBombed;
  int   _nbplayer;
  std::vector<gdl::Keys::Key> _keys;
  gdl::Model	_model;
  Map		*_map;
  Mutex		_mutex;

public:
  Human(Map *, const int, const int, int, int, int);
  Human(const Human &);
  Human & operator=(const Human &);
  ~Human();
  virtual void	putBomb();
  virtual int getScore() const;
  virtual int getLives() const;
  virtual const std::string & getCurrentBonus() const;
  virtual void setScore(int);
  virtual bool isAlive() const;
  virtual bool haveBonus() const;
  virtual void	destroyObject();
  virtual void	initialize(void);
  virtual void	update(gdl::GameClock const &, gdl::Input &);
  virtual void	draw(void);
  virtual void	move(gdl::Input &);
  virtual bool  checkPos(int, int) const;
  virtual void	setVecX(float);
  virtual void	setVecY(float);
  virtual void	setVecZ(float);
  virtual float	getVecX() const;
  virtual float	getVecY() const;
  virtual float	getVecZ() const;
  virtual int   getPosX() const;
  virtual int	getPosY() const;
  virtual int	getRange() const;
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual Map* getMap() const;
  virtual AObjects::typeObject  getType() const;
  virtual void	setMap(Map *);
  virtual void  setTexture(int);
  virtual void  increaseSpeed();
  virtual void  increaseBombRange();
  virtual APlayers::Direction getDir() const;
  virtual void  setKeys();
  virtual int  getNbPlayer() const;
  virtual void  randomBonus(AObjects *);
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
  virtual void  addBomb();
  virtual void  addDropped();
  virtual void  rmDropped();
  virtual unsigned int getBombStock() const;
  virtual unsigned int getBombDropped() const;
  virtual void saveTimer();
  virtual void	pause() {};
  virtual void	unpause() {};
  bool	changeDirection(gdl::Keys::Key);
};

#endif
