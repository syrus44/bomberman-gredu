//
// Floor.hh for Bomberman in /home/caille_l//Documents/merge_map_objects
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Mon May  6 10:29:41 2013 louis cailleux
// Last update Sat Jun  8 18:48:46 2013 florent cerfon
//

#ifndef	FLOOR_HH_
# define FLOOR_HH_

#include "AObjects.hh"
#include "Image.hpp"
#include "GameClock.hpp"
#include "Input.hpp"

#define	FLOOR_WIDTH_SIZE	150
#define	FLOOR_DEEP_SIZE		100

class Floor : public AObjects
{
  gdl::Image	_texture;
  int           _mapx;
  int           _mapy;

public:
  Floor(int, int, int, int);
  Floor(const Floor &);
  ~Floor();
  Floor&  operator=(const Floor &);
  virtual void	initialize(void);
  virtual void	update(gdl::GameClock const &, gdl::Input &);
  virtual void	draw(void);
  virtual void	setVecX(float);
  virtual void	setVecY(float);
  virtual void	setVecZ(float);
  virtual float	getVecX() const;
  virtual float	getVecY() const;
  virtual float	getVecZ() const;
  virtual void	setScore(int);
  virtual int	getScore() const;
  virtual void	destroyObject();
  virtual int	getRange() const;
  virtual int   getPosX() const;
  virtual int	getPosY() const;
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual void  setTexture(int);
  virtual AObjects::typeObject  getType() const;
  virtual void  randomBonus(AObjects *);
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
  virtual void	pause() {};
  virtual void	unpause() {};
};

#endif
