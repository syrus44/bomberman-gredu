//
// IronWall.hh for IronWall in /home/bettin_j//Dropbox/Epitech/Bomberman/true_include
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Tue May 14 17:57:21 2013 jordan bettin
// Last update Sat Jun  8 18:50:01 2013 florent cerfon
//

#ifndef LAVAWALL_HH
#define LAVAWALL_HH

#include "AObjects.hh"
#include "Image.hpp"
#include "GameClock.hpp"
#include "Input.hpp"

class	LavaWall : public AObjects
{
  gdl::Image	_texture;
  int           _mapx;
  int           _mapy;
  
public:
  LavaWall(int, int, int, int);
  LavaWall(const LavaWall &);
  ~LavaWall();
  LavaWall & operator=(const LavaWall &);
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
  virtual int   getPosX() const;
  virtual int	getPosY() const;
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual int	getScore() const;
  virtual void	destroyObject();
  virtual int	getRange() const;
  virtual void  setTexture(int);
  virtual void  randomBonus(AObjects *);
  virtual AObjects::typeObject  getType() const;
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
  virtual void	pause() {};
  virtual void	unpause() {};
};

#endif
