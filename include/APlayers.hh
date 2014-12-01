//
// APlayers.hh for APlayers in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 14:57:14 2013 jordan bettin
// Last update Sun Jun  9 11:10:53 2013 jordan bettin
//

#ifndef APLAYERS_HH
#define APLAYERS_HH

#include "Vector3f.hh"
#include "AObjects.hh"
#include "Thread.hpp"

class	Map;

class	APlayers : public AObjects
{
public:
  enum	Direction
    {
      Up = 0,
      Down = 1,
      Left = 2,
      Right = 3,
    };
protected:
  bool		_isAlive;
  int		_nbLives;
  bool		isRunning;
  unsigned int	_bombStock;
  unsigned int	_bombDropped;
  int		_bombRange;
  int		_speed;
  Direction	_dir;
  gdl::Model	_model;
  Map		*_map;
  Mutex		_mutex;

public:
  APlayers();
  APlayers(const APlayers &);
  APlayers & operator=(const APlayers &);
  ~APlayers();
  int		getSpeed() const;
  void		putBomb();
  virtual int	getLives() const = 0;
  virtual const std::string & getCurrentBonus() const = 0;
  bool	isAlive() const;
  virtual bool	haveBonus() const = 0;
  virtual void	move(gdl::Input &) = 0;
  virtual APlayers::Direction getDir() const = 0;
  virtual void  increaseSpeed() = 0;
  virtual void  increaseBombRange() = 0;
  virtual void  addBomb() = 0;
  virtual void  addDropped() = 0;
  virtual void  rmDropped() = 0;
  virtual unsigned int  getBombStock() const = 0;
  virtual unsigned int  getBombDropped() const = 0;
};

#endif
