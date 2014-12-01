//
// Computer.hh for Computer in /home/bettin_j//SVN/bomberman-gredu/trunk/caille_l
// 
// Made by jordan bettin
// Login   <bettin_j@epitech.net>
// 
// Started on  Thu May  2 15:17:49 2013 jordan bettin
// Last update Sun Jun  9 11:34:36 2013 florent cerfon
//

#ifndef COMPUTER_HH
#define COMPUTER_HH

#include <list>
#include "APlayers.hh"

#define	TICK_DIFFICULTY		25
#define WAY(a, b) ((a > b) ? (this->_dir = APlayers::Down) : (this->_dir = APlayers::Up))
#define DIR(x, y, a, b) ((x > y) ? (this->_dir = APlayers::Right) : (y > x ? (this->_dir = APlayers::Left) : WAY(a, b)))

typedef struct	path_str
{
  int		x;
  int		y;
}		elmpath;

class	Computer : public APlayers
{
  bool		_haveBonus;
  Map		*_map;
  int		_nbLives;
  std::string	_currentBonus;
  bool		isRunning;
  bool		isBombed;
  gdl::Model	_model;

  /* variables nécessaires à la réflexion de l'IA */
  
private:
  std::list<elmpath>	blowPath;
  std::list<elmpath>	escapePath;
  std::list<elmpath>	emergencyPath;
  int			targetX;
  int			targetY;
  typeObject		targetType;
  bool			bloody;
  int			playerTargetX;
  int			playerTargetY;
  bool			needToMove;
  int			tick;
  
public:
  Computer(Map *, const int, const int, int, int);
  Computer(const Computer &);
  Computer & operator=(const Computer &);
  ~Computer();
  
  /* Réflexion de l'IA */
  
  void		chooseDirectionToGo();
  int		chooseDestrToGo(int, int, int, std::map<int, std::map<int, AObjects *> >, std::list<elmpath>);
  int		CheckIfAlreadyPathed(int, int, int, std::map<int, std::map<int, AObjects *> > &, std::list<elmpath> &);
  void		readDestrToGo() const;
  void		readEmergencyToGo() const;
  bool		isThisPlaceSafe(int, int, std::map<int, std::map<int, AObjects *> > &) const;
  void		getToCover(int, int, int, std::map<int, std::map<int, AObjects *> > &, std::list<elmpath>);
  void		EmergencyAlreadyPathed(int, int, int, std::map<int, std::map<int, AObjects *> > &, std::list<elmpath> &);
  
  /* Fin réflexion de l'IA */

  virtual void	putBomb();
  virtual int	getScore() const;
  virtual int	getLives() const;
  virtual const std::string & getCurrentBonus() const;
  virtual void	setScore(int);
  virtual bool	haveBonus() const;
  virtual void	destroyObject();
  virtual void	initialize(void);
  virtual void	update(gdl::GameClock const &, gdl::Input &);
  virtual void	draw(void);
  virtual void	move(gdl::Input &);
  virtual bool	checkPos(int, int) const;
  virtual void	setVecX(float);
  virtual void	setVecY(float);
  virtual void	setVecZ(float);
  virtual int   getPosX() const;
  virtual int	getPosY() const;
  virtual void  setPosX(int);
  virtual void	setPosY(int);
  virtual float	getVecX() const;
  virtual float	getVecY() const;
  virtual float	getVecZ() const;
  virtual Map*	getMap() const;
  virtual int	getRange() const;
  virtual AObjects::typeObject  getType() const;
  virtual void  setMap(Map *);
  virtual void  setTexture(int);
  virtual void  increaseSpeed();
  virtual void  increaseBombRange();
  virtual APlayers::Direction getDir() const;
  virtual void  randomBonus(AObjects *);
  virtual void  setMap(std::map<int, std::map<int, AObjects *> > const &);
  virtual void  addBomb();
  virtual void  addDropped();
  virtual void  rmDropped();
  virtual unsigned int getBombStock() const;
  virtual unsigned int getBombDropped() const;
  virtual void	pause() {};
  virtual void	unpause() {};
};

#endif
