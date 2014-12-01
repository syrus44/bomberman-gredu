//
// Menu.hh for  in /home/dugast_a//CPP/Bomberman/bomberman-gredu/trunk/Bomberman
// 
// Made by antoine dugast
// Login   <dugast_a@epitech.net>
// 
// Started on  Thu May 16 16:45:41 2013 antoine dugast
// Last update Sun Jun  9 11:04:24 2013 jordan bettin
// Last update Thu Jun  6 10:02:01 2013 pierre petit
//

#ifndef			MENU_HH
#define			MENU_HH

#include		"Game.hpp"
#include		"Input.hpp"
#include		"Text.hpp"
#include		"Map.hh"
#include		"Camera.hh"
#include		"Human.hh"
#include		"Score.hh"
#include		"Utils.hpp"
#include		<list>
#include		<fstream>
#include		<sstream>
#include		<iostream>

#define			WINSIZEX	1280	/*Window size x*/
#define			WINSIZEY	1024	/*Window size y*/
#define			MAXPLAYER	2	/*nbr Player max*/
#define			MINPLAYER	1	/*nbr Player min*/
#define			MAXIA		10	/*nbr IA max*/
#define			MINIA		0	/*nbr IA min*/
#define			MAXMAPX		100	/*x size max*/
#define			MINMAPX		10	/*x size min*/
#define			MAXMAPY		100	/*y size max*/
#define			MINMAPY		10	/*y size min*/
#define			NBRTHEME	4	/*nbr theme*/
#define			TIMECLOCK	0.15	/*temps entre chaque boucle*/
#define			XCONF		600	/*configuration marge*/
#define			XSND		340	/*options marge x*/
#define			YSND		450	/*options marge y*/
#define			XMUS		340	/*options marge x*/
#define			YMUS		555	/*options marge y*/
#define			XNAME		500	/*posx name*/
#define			YNAME		700	/*posy name*/
#define			SIZENAME	3	/*size name*/
#define			NBRMUS		3	/*nbr musics*/
#define			SAVES_ERROR	"There are no available saves."
#define			MAPSAVES_ERROR	"There are no available maps."
#define			FONT		"./font/bm.ttf" /*font*/

class				Menu
{
private:
  std::map<int, gdl::Image >	M;
  std::map<int, gdl::Image >	Intro;
  gdl::Text			T;
  int				numI;
  unsigned int			numM;
  std::map<int, std::string >	Saves;
  unsigned int			nbrS;
  unsigned int			numS;
  std::map<int, std::string >	Loads;
  unsigned int			nbrL;
  unsigned int			numL;
  unsigned int			nbP;
  unsigned int 			IA;
  unsigned int			x;
  unsigned int 			y;
  std::map<int, std::string >	Th;
  int				th;
  Score				*S;
  Map				*game;
  unsigned int			snd;
  unsigned int			bo;
  std::map<int, int>		Name;
  int				xname;
  int				yname;
  bool				animation;
  int				curPic;
  int				_score;

public:
  Menu(Map *);
  ~Menu();
  /*loading functions*/
  void			loadIntro();
  void			loadImage();
  void			loadTheme();
  void			loadSaves();
  void			loadMaps();
  void			loadName();
  /*loop game functions*/
  void			initialize(void);
  void			update(void);
  void			draw(void);
  void			drawIntro(void);
  void			unload(void);
  /*play menu functions*/
  void                  selectConf(gdl::Input &);
  void                  selectPlayers(gdl::Input &);
  void                  selectIA(gdl::Input &);
  void                  selectInfoMap(gdl::Input &);
  void                  selectMapXY(gdl::Input &);
  void                  selectTheme(gdl::Input &);
  /*loads menu functions*/
  void                  selectLoads(gdl::Input &);
  void                  selectSaves(gdl::Input &);
  void                  selectMaps(gdl::Input &);
  /*options menu functions*/
  void                  selectSounds(gdl::Input &);
  /*final score name function*/
  void                  selectName(gdl::Input &);
  std::string  		returnName();
  /*aff functions*/
  void			affCredits();
  void			affImage(gdl::Image) const;
  void			affString(std::string const &, unsigned int, unsigned int, unsigned int);
  void			affConf();
  void			affSaves();
  void			affSaveMap();
  void			affCreatMap();
  void			affScores();
  void			affOptions();
  void			affName();
  /*Manage Menu Functions*/
  void                  loopMenu(int, int, gdl::Input &);
  void                  selectBack(int, gdl::Input &);
  void                  optiConf(gdl::Input &);
  void                  launchMenu(gdl::Input &);
  void                  loadMenu(gdl::Input &);
  void                  scoresMenu(gdl::Input &);
  void                  chooseScoreMenu();
  void                  optionsMenu(gdl::Input &);
  bool                  quitMenu(gdl::Input &) const;
  void                  nameMenu();
  /*Check Functions*/
  bool			checkFiles(std::string const &) const;
  bool			checkKeys();
  /*Launch Game Function*/
  void			launchGame(gdl::Input &);
  /*Main Menu Function*/
  void			manageMenu(gdl::Input &);
  int			getNumI() const;
  unsigned int		getNumM() const;
  unsigned int		getX() const;
  unsigned int		getY() const;
  void			setX(unsigned int);
  void			setY(unsigned int);
  bool			getAnimation() const;
  void			setAnimation(bool);
  int			getPic() const;
  void			setScore(int);
  void			setPic(int);
  unsigned int		getAI() const;
  void			setAI(unsigned int);
};

#endif			/*MENU_HH*/
