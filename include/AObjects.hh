//
// AObjects.hh for AObjects in /home/bettin_j//Dropbox/Epitech/Bomberman/true_include
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Tue May 14 17:24:40 2013 jordan bettin
// Last update Sun Jun  9 10:37:57 2013 jordan bettin
//

#ifndef AOBJECTS_HH
#define AOBJECTS_HH

#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <string>

#include "GameClock.hpp"
#include "Input.hpp"
#include "Model.hpp"
#include "Vector3f.hh"

#define WALL_WIDTH_SIZE         150
#define WALL_DEEP_SIZE          100

class	AObjects
{
public:
  enum typeObject
    {
      // objets indestructibles
      Air,
      Wall,
      Bonus,
      Explosion,

      // défini comme une limite entre objets destructibles (inférieur à) et indestructibles
      Destructible,
      // objets destructibles
      Bomb,
      Unknown,
      WallDestr,

      Through,

      //traversable
      Human,
      Computer,
    };

protected:
  std::string	_name;
  int		_score;
  int		_range;
  Vector3f	_position;
  Vector3f	_rotation;
  typeObject	_type;
  int		_x;
  int		_y;
  bool		existence;
  unsigned int  _bonusType;

public:
  AObjects(void);
  AObjects(const AObjects &);
  ~AObjects();
  AObjects& operator=(const AObjects &);
  void	setName(const std::string&);
  bool	doesExist() const;
  void	setExistence(bool);
  const std::string & getName() const;

  virtual void	initialize(void) = 0;
  virtual void	update(gdl::GameClock const &, gdl::Input &) = 0;
  virtual void	draw(void) = 0;

  virtual void	setVecX(float) = 0;
  virtual void	setVecY(float) = 0;
  virtual void	setVecZ(float) = 0;
  virtual void  setScore(int) = 0;

  virtual float	getVecX() const = 0;
  virtual float	getVecY() const = 0;
  virtual float	getVecZ() const = 0;
  virtual int   getPosX() const = 0;
  virtual int	getPosY() const = 0;
  virtual void  setPosX(int) = 0;
  virtual void	setPosY(int) = 0;
  virtual void  setTexture(int) = 0;
  virtual int	getScore() const = 0;
  virtual int	getRange() const = 0;

  virtual void	destroyObject() = 0;
  virtual void  randomBonus(AObjects *) = 0;
  virtual AObjects::typeObject  getType() const = 0;
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &) = 0;
  virtual void	pause() = 0;
  virtual void	unpause() = 0;
};

#endif
