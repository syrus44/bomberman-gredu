//
// Map.hh for  in /home/dugast_a//CPP/Bomberman/bomberman-gredu/trunk/Ant
// 
// Made by antoine dugast
// Login   <dugast_a@epitech.net>
// 
// Started on  Thu May  2 14:36:20 2013 antoine dugast
// Last update Sun Jun  9 11:14:12 2013 jordan bettin
//

#ifndef		MAP_HH
#define		MAP_HH

#include	<map>
#include	<iostream>
#include	<utility>
#include	<cstdlib>
#include	"IronWall.hh"
#include	"LavaWall.hh"
#include	"Floor.hh"
#include	"WoodWall.hh"
#include	"ReadFile.hh"
#include	"Sound.hh"

#include	"Camera.hh"
#include	"AObjects.hh"
#include	"APlayers.hh"
#include	"Game.hpp"
#include	"Text.hpp"
#include	"Utils.hpp"

class		Menu;

class		Map : public gdl::Game
{
  std::map<int, std::map<int, AObjects *> >		map;
  std::map<int, std::map<int, AObjects *> >::iterator	yt;
  std::map<int, AObjects *>::iterator			xt;
  int							mapSizeX;
  int							mapSizeY;
  int							rLimit;
  int							lLimit;
  float							t;
  float							t2;
  int							uLimit;
  int							dLimit;
  int							_players;
  int							_AI;
  AObjects						*mapAir;
  AObjects						*mapFloor;
  AObjects						*mapBorder;
  AObjects						*mapWall;
  AObjects						*destWall;
  AObjects						*mapExpl;
  std::string						_filename;
  Camera						camera;
  Camera						camera2;
  AObjects						*player;
  AObjects						*player2;
  std::string						filename;
  int							x;
  int							y;
  bool							tosave;
  bool							_showMenu;
  bool							isAlone;
  bool							alreadyShown;
  Menu                                                  *_menu;
  Mutex							_mutex;
  gdl::Text						T;
  bool							pause;

public:
  int		_texture;
  Sound		_sound;
  void			initialize(void);
  void			update(void);
  void			draw(void);
  void			unload(void);
  void			makePlinth(void);
  void			setFileName(std::string const &);
  void			setSizeX(int);
  void			setSizeY(int);

public:
  Map();
  ~Map();
  void	lock();
  void	unlock();
  void	randomObject();
  void	fillRandom();
  void	init();
  void	blow(int, int, int);
  void	initMap();
  void	mapFile();
  void	drawStatic();
  void  calcLimits();
  void	affMap();
  void	addObj(int, int, AObjects *);
  void	rmObj(int, int);
  AObjects *getObj(int, int);
  AObjects *createObj(char, int, int);
  AObjects *getHuman(int);
  void	freeMap();
  void	Deflagration(int, int, int);
  int	getMapSizeX() const;
  int	getMapSizeY() const;
  void  pushBomb(Vector3f const &, std::pair<int, int>const &, int, APlayers *);
  void  splitScreen(std::map<int, AObjects *>::iterator x,
			   std::map<int, std::map<int, AObjects *> >::iterator y);
  std::pair<int, int> const  get2Dcoord(float x, float y) const;
  std::map<int, std::map<int, AObjects *> > const &getMap() const;
  bool	MovePlayer(int, int, int, int);
  void  setObj(int, int, AObjects *);
  void	setPlayers(int);
  void  initCoord(AObjects *, int, int);
  void	rmExpl();
  int	getPlayers() const;
  void  affScores();
  void  setShowMenu(bool);
  void  closeWindow();
  void  save() const;
  void  setSave(bool);
  void	drawScores();
  void  timeHandling();
  void  initGame();
  bool  checkKeys();
  void  selectMapSize();
  void	putAI();
  void	putBonus();
  void  affCredits();
  bool	getShown() const;
  int	countAI();
};

void	launchMap(Map *g, const std::string &, const std::string &);

#endif		/*MAP_HH*/
