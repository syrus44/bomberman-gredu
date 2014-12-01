//
// WoodWall.hh for WoodWall in /home/bettin_j//Dropbox/Epitech/Bomberman/true_include
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Tue May 14 17:56:01 2013 jordan bettin
// Last update Sat Jun  8 18:49:45 2013 florent cerfon
//

#ifndef WOODWALL_HH
#define WOODWALL_HH

#include "AObjects.hh"
#include "Image.hpp"
#include "GameClock.hpp"
#include "Input.hpp"

class	WoodWall : public AObjects
{
  gdl::Image	_texture;
  std::map<int, std::map<int, AObjects*> > _map;
  
public:
  WoodWall(int, int);
  WoodWall(const WoodWall &);
  ~WoodWall();
  WoodWall & operator=(const WoodWall &);
  void		initialize(void);
  void		update(gdl::GameClock const &, gdl::Input &);
  void		draw(void);
  virtual void	setVecX(float);
  virtual void	setVecY(float);
  virtual void	setVecZ(float);
  virtual float	getVecX(void) const;
  virtual float	getVecY(void) const;
  virtual float	getVecZ(void) const;
  virtual void	setScore(int);
  virtual int	getScore() const;
  virtual void	destroyObject();
  virtual int   getPosX() const;
  virtual int	getPosY() const;
  virtual int	getRange() const;
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
