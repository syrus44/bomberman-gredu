//
// Menu.cpp for  in /home/dugast_a//CPP/Bomberman/bomberman-gredu/trunk/Bomberman
// 
// Made by antoine dugast
// Login   <dugast_a@epitech.net>
// 
// Started on  Thu May 16 16:50:13 2013 antoine dugast
// Last update Sun Jun  9 11:02:35 2013 jordan bettin
//

#include	"Menu.hh"
#include	<dirent.h>

Menu::Menu(Map *g)
{
  this->game = g;
  this->S = new Score;
  this->numI = 0;
  this->numM = 0;
  this->numS = 0;
  this->nbrS = 0;
  this->numL = 0;
  this->nbrL = 0;
  this->nbP = MINPLAYER;
  this->IA = MINIA;
  this->x = 10;
  this->y = 10;
  this->th = 1;
  this->snd = 1;
  this->bo = 0;
  this->xname = 0;
  this->yname = 97;
  this->animation = true;
}

Menu::~Menu()
{}

/*-------------------------------------------------------------*/
/*---LOADING FUNCTIONS-----------------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::loadIntro()
{
  this->Intro[0] = gdl::Image::load("img/intro/intro1.png");
  this->Intro[1] = gdl::Image::load("img/intro/intro2.png");
  this->Intro[2] = gdl::Image::load("img/intro/intro3.png");
  this->Intro[3] = gdl::Image::load("img/intro/intro4.png");
  this->Intro[4] = gdl::Image::load("img/intro/intro5.png");
}

void		Menu::loadImage()
{
  this->M[0] = gdl::Image::load("img/menu/Mplay.png"); 
  this->M[1] = gdl::Image::load("img/menu/Mloads.png"); 
  this->M[2] = gdl::Image::load("img/menu/Mscores.png"); 
  this->M[3] = gdl::Image::load("img/menu/Moptions.png");
  this->M[4] = gdl::Image::load("img/menu/Mexit.png");
  this->M[5] = gdl::Image::load("img/menu/Conf0.png");
  this->M[6] = gdl::Image::load("img/menu/Conf1.png");
  this->M[7] = gdl::Image::load("img/menu/Conf2.png");
  this->M[8] = gdl::Image::load("img/menu/Conf3.png");
  this->M[9] = gdl::Image::load("img/menu/Conf4.png");
  this->M[10] = gdl::Image::load("img/menu/Conf5.png");
  this->M[11] = gdl::Image::load("img/menu/Conf6.png");
  this->M[12] = gdl::Image::load("img/menu/Conf7.png");
  this->M[13] = gdl::Image::load("img/menu/Load1.png");
  this->M[14] = gdl::Image::load("img/menu/Load2.png");
  this->M[15] = gdl::Image::load("img/menu/Load3.png");
  this->M[16] = gdl::Image::load("img/menu/Scores.png");
  this->M[17] = gdl::Image::load("img/menu/Options.png");
  this->M[18] = gdl::Image::load("img/menu/Options1.png");
  this->M[19] = gdl::Image::load("img/menu/Options2.png");
  this->M[20] = gdl::Image::load("img/menu/getName.png");
  this->M[21] = gdl::Image::load("img/menu/credit.png");
}

void		Menu::loadTheme()
{
  this->Th[1] = "Mine";
  this->Th[2] = "Desert";
  this->Th[3] = "Forest";
  this->Th[4] = "Snow";
}

void		Menu::loadSaves()
{
  DIR		*d;
  struct dirent	*dr;

  if ((d = opendir("./saves")) != NULL)
    {
      while ((dr = readdir(d)) != NULL)
	{
	  std::string	s = dr->d_name;
	  if (checkFiles(s) == true)
	    {
	      this->Saves[this->nbrS] = dr->d_name;
	      this->nbrS++;
	    }
	}
      closedir(d);
    }
  else
    std::cerr << "Impossible d'ouvrir le dossier saves." << std::endl;
}

void		Menu::loadMaps()
{
  DIR		*d;
  struct dirent	*dr;

  if ((d = opendir("./map")) != NULL)
    {
      while ((dr = readdir(d)) != NULL)
	{
	  std::string	s = dr->d_name;
	  if (checkFiles(s) == true)
	    {
	      this->Loads[this->nbrL] = dr->d_name;
	      this->nbrL++;
	    }
	}
      closedir(d);
    }
  else
    std::cerr << "Impossible d'ouvrir le dossier map." << std::endl;
}

void		Menu::loadName()
{
  int		x;

  for (x = 0; x != SIZENAME; x++)
    this->Name[x] = 97;
}

void		display(void *o)
{
  Menu		*m = static_cast<Menu *>(o);

  if (m->getPic() != 4)
    {
      m->setPic(m->getPic() + 1);
      m->drawIntro();
    }
  else
    m->setAnimation(false);
}

/*-------------------------------------------------------------*/
/*---LOOP GAME FUNCTIONS---------------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::initialize()
{
  this->curPic = 0;
  this->loadIntro();
  this->loadImage();
  this->loadTheme();
  this->loadSaves();
  this->loadMaps();
  this->loadName();
  this->S->getScores();
  this->game->_sound.playBackground();
  this->bo = 2; 
  this->drawIntro();
}

void		Menu::drawIntro()
{
  Timer<Menu>	T(4000000, &display, this); 
}

void		Menu::draw()
{
  gdl::Image	I = this->M[this->numI];

  if (animation)
    {
      I = this->Intro[this->curPic];
      this->affImage(I);
    }
  else
    {
      this->affImage(I);
      if (this->numI >= 5 &&
	  this->numI <= 12)
	this->affConf();
      if (this->numI >= 13 &&
	  this->numI <= 15)
	this->affSaves();
      if (this->numI == 16)
	this->affScores();
      if (this->numI >= 17 &&
	  this->numI <= 19)
	this->affOptions();
      if (this->numI == 20)
	this->affName();
    }
}
void		Menu::unload()
{}

/*-------------------------------------------------------------*/
/*---PLAY MENU FUNCTIONS---------------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::selectConf(gdl::Input &i)
{
  this->selectPlayers(i);
  this->selectIA(i);
  this->selectInfoMap(i);
  this->selectTheme(i);
  this->selectBack(10, i);
}

/*-------------------------------------------------------------*/

void            Menu::selectPlayers(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 5)
    {
      if (this->nbP == MINPLAYER)
        this->nbP = MAXPLAYER;
      else
        this->nbP--;
    }
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 5)
    {
      if (this->nbP == MAXPLAYER)
        this->nbP = MINPLAYER;
      else
        this->nbP++;
    }
}

/*-------------------------------------------------------------*/

void		Menu::selectIA(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 6)
    {
      if (this->IA == MINIA)
	this->IA = MAXIA;
      else
	this->IA--;
    }
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 6)
    {
      if (this->IA == MAXIA)
	this->IA = MINIA;
      else
	this->IA++;
    }
}

/*-------------------------------------------------------------*/

void		Menu::selectInfoMap(gdl::Input &i)
{
  this->selectMapXY(i);
  this->game->selectMapSize();
}

void		Menu::selectMapXY(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 11)
    this->numI = 12;
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 7)
    this->numI = 11;
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 11)
    this->numI = 7;
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 12)
    this->numI = 11;
}

/*-------------------------------------------------------------*/

void		Menu::selectTheme(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 8)
    {
      if (this->th == 1)
	this->th = NBRTHEME;
      else
	this->th--;
    }
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 8)
    {
      if (this->th == NBRTHEME)
	this->th = 1;
      else
	this->th++;
    }
}

/*-------------------------------------------------------------*/
/*---LOADS MENU FUNCTIONS--------------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::selectLoads(gdl::Input &i)
{
  this->selectSaves(i);
  this->selectMaps(i);
  this->selectBack(15, i);
}

void		Menu::selectSaves(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 13)
    {
      if (this->numS == 0)
	this->numS = this->nbrS - 1;
      else
	this->numS--;
    }
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 13)
    {
      if (this->numS == this->nbrS - 1)
	this->numS = 0;
      else
	this->numS++;
    }
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->nbrS != 0 &&
      this->numI == 13)
    {
      this->game->setFileName("saves/" + this->Saves[this->numS]);
      this->game->_texture = this->th;
      this->game->initGame();
      this->game->setShowMenu(false);
    }
}

void		Menu::selectMaps(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 14)
    {
      if (this->numL == 0)
	this->numL = this->nbrL - 1;
      else
	this->numL--;
    }
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 14)
    {
      if (this->numL == this->nbrL - 1)
	this->numL = 0;
      else
	this->numL++;
    }
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->nbrL != 0 &&
      this->numI == 14)
    {
      this->game->setFileName("map/" + this->Loads[this->numL]);
      this->game->_texture = this->th;
      this->game->initGame();
      this->game->setShowMenu(false);
    }
}

/*-------------------------------------------------------------*/
/*---OPTIONS MENU FUNCTIONS------------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::selectSounds(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 17)
    {
      if (this->snd == 0)
	this->snd = 3;
      else
	this->snd--;
    }
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 17)
    {
      if (this->snd == 3)
	this->snd = 0;
      else
	this->snd++;
    }
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 18)
    {
      if (this->bo == 0)
	this->bo = NBRMUS - 1;
      else
	this->bo--;
    }
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 18)
    {
      if (this->bo == NBRMUS - 1)
	this->bo = 0;
      else
	this->bo++;
    }
  this->selectBack(19, i);
}

/*-------------------------------------------------------------*/
/*---FINAL SCORE NAME FUNCTION---------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::selectName(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Up) == true)
    {
      if (this->yname == 122)
	this->yname = 97;
      else
	this->yname++;
      this->Name[this->xname] = this->yname;
    }
  if (i.isKeyDown(gdl::Keys::Down) == true)
    {
      if (this->yname == 97)
	this->yname = 122;
      else
	this->yname--;
      this->Name[this->xname] = this->yname;
    }
  if (i.isKeyDown(gdl::Keys::Left) == true)
    {
      if (this->xname != 0)
	this->xname--;
      this->yname = this->Name[xname];       
    }
  if (i.isKeyDown(gdl::Keys::Right) == true)
    {
      if (this->xname != SIZENAME - 1)
	this->xname++;
      this->yname = this->Name[xname];
    }
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->numI == 20)
    {
      this->S->addMemberFile(returnName(), this->_score);
      this->S->addMemberLst(returnName(), this->_score);
      this->S->triScore();
      this->xname = 0;
      this->loadName();
      this->numM = 3;
      this->numI = 16;
    }
}

std::string		Menu::returnName()
{
  int			i;
  std::string		name;

  i = 0;
  while (i != SIZENAME)
    {
      name += this->Name[i];
      i++;
    }
  return (name);
}

/*-------------------------------------------------------------*/
/*---AFF FUNCTIONS---------------------------------------------*/
/*-------------------------------------------------------------*/

void			Menu::affCredits(void)
{
  this->numI = 21;
}

void			Menu::affImage(gdl::Image I) const
{
  I.bind();
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0); glVertex2i(-1, 1);
  glTexCoord2f(1, 0); glVertex2i(1, 1);
  glTexCoord2f(1, 1); glVertex2i(1, -1);
  glTexCoord2f(0, 1); glVertex2i(-1, -1);
  glEnd();
}

void			Menu::affString(std::string const &s, unsigned int x, unsigned int y, unsigned int size)
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT |
	       GL_ENABLE_BIT | GL_TEXTURE_BIT |
	       GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
  this->T.setText(s);
  this->T.setFont("./font/bm.ttf");
  this->T.setSize(size);
  this->T.setPosition(x, y);
  this->T.draw();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glPopAttrib();
}

/*-------------------------------------------------------------*/

void			Menu::affConf()
{
  std::ostringstream	os;
  std::ostringstream	oss;

  os << this->nbP;
  this->affString(os.str(), XCONF, 485, 35);
  os.seekp(0);
  os << this->IA;
  this->affString(os.str(), XCONF, 550, 35);
  os.seekp(0);
  os << this->x;
  this->affString(os.str(), XCONF, 620, 35);
  os.seekp(0);
  oss << this->y;
  this->affString(oss.str(), XCONF + 120, 620, 35);
  this->affString(this->Th[this->th], XCONF, 690, 35);
  os.seekp(0);
}

/*-------------------------------------------------------------*/

void			Menu::affSaves()
{
  this->affSaveMap();
  this->affCreatMap();
}

void			Menu::affSaveMap()
{
  if (this->nbrS == 0)
    this->affString(SAVES_ERROR, 380, 530, 30);
  else
    this->affString(this->Saves[this->numS], 380, 530, 30);
}

void			Menu::affCreatMap()
{
  if (this->nbrL == 0)
    this->affString(MAPSAVES_ERROR, 370, 665, 30);
  else
    this->affString(this->Loads[this->numL], 370, 665, 30);
}

/*-------------------------------------------------------------*/

void			Menu::affScores()
{
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT |
  	       GL_ENABLE_BIT | GL_TEXTURE_BIT |
  	       GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
  this->S->affScore();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glPopAttrib();
}

/*-------------------------------------------------------------*/

void			Menu::affOptions()
{
  this->affString("Sounds : ", XSND, YSND, 30);
  if (this->snd == 0)
    this->affString("LOW", XSND + 200, YSND, 30);
  if (this->snd == 1)
    this->affString("MEDIUM", XSND + 200, YSND, 30);
  if (this->snd == 2)
    this->affString("HIGH", XSND + 200, YSND, 30);
  if (this->snd == 3)
    this->affString("MUTE", XSND + 200, YSND, 30);

  this->game->_sound.setVolume(this->snd);

  this->affString("Musics : ", XMUS, YMUS, 30);
  if (this->bo == 0)
    this->affString("Mass Effect 2", XMUS + 200, YMUS, 30);
  if (this->bo == 1)
    this->affString("Halo 1", XMUS + 200, YMUS, 30);
  if (this->bo == 2)
    this->affString("Battle Field 3", XMUS + 200, YMUS, 30);

  this->game->_sound.changeMusic(this->bo);
  this->game->_sound.setVolume(this->snd);
}

/*-------------------------------------------------------------*/

void				Menu::affName()
{
  int				x;
  int				i;
  std::ostringstream		os;

  x = XNAME;
  i = 0;
  os << this->_score;
  this->affString(os.str(), XNAME + 35, YNAME - 225, 35);
  while (i != SIZENAME)
    {
      std::string s;
      s = this->Name[i];
      this->affString(s, x, YNAME, 35);
      x += 40;
      i++;
    }
}

/*-------------------------------------------------------------*/
/*---MANAGE MENU FUNCTIONS-------------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::loopMenu(int a, int b, gdl::Input &i)
{
 if (i.isKeyDown(gdl::Keys::Up) == true &&
      this->numI >= a && this->numI <= b)
    {
      if (this->numI == a)
	this->numI = b;
      else
	this->numI--;
    }
  if (i.isKeyDown(gdl::Keys::Down) == true &&
      this->numI >= a && this->numI <= b)
    {
      if (this->numI == b)
	this->numI = a;
      else
	this->numI++;
    }
}

void		Menu::selectBack(int nb, gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->numI == nb)
    {
      this->numM = 0;
      this->numI = 0;
    }
}

void		Menu::optiConf(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Left) == true &&
      this->numI == 9)
    this->numI = 10;
  if (i.isKeyDown(gdl::Keys::Right) == true &&
      this->numI == 10)
    this->numI = 9;
}

/*-------------------------------------------------------------*/

void		Menu::launchMenu(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->numI == 0)
    {
      this->numM = 1;
      this->numI = 5;
    }
}

void		Menu::loadMenu(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->numI == 1)
    {
      this->numM = 2;
      this->numI = 13;
    }
}

void		Menu::scoresMenu(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->numI == 2)
    {
      this->numM = 3;
      this->numI = 16;
    }
}

void            Menu::chooseScoreMenu()
{
  this->numM = 5;
  this->numI = 20;
}

void		Menu::optionsMenu(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->numI == 3)
    {
      this->numM = 4;
      this->numI = 17;
    }
}

bool		Menu::quitMenu(gdl::Input &i) const
{
  if ((i.isKeyDown(gdl::Keys::Space) == true &&
       this->numI == 4) ||
      (i.isKeyDown(gdl::Keys::Escape) == true))
    return (true);
  return (false);
}

void		Menu::nameMenu()
{
  this->numM = 5;
  this->numI = 20;
}

/*-------------------------------------------------------------*/
/*---CHECK FUNCTIONS-------------------------------------------*/
/*-------------------------------------------------------------*/

bool		Menu::checkFiles(std::string const &s) const
{
  if (s.size() <= 30 &&
      s.compare(".") != 0 &&
      s.compare("..") != 0 &&
      s.compare(".svn") != 0 &&
      s.find("~") > 30 &&
      s.find("#") > 30)
    return (true);
  else
    return (false);
}

/*-------------------------------------------------------------*/
/*---LAUNCH GAME FUNCTION--------------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::launchGame(gdl::Input &i)
{
  if (i.isKeyDown(gdl::Keys::Space) == true &&
      this->numI == 9)
    {
      this->game->_texture = this->th;
      this->game->setSizeX(this->x);
      this->game->setSizeY(this->y);
      this->game->setPlayers(this->nbP);
      this->game->initGame();
      this->game->setShowMenu(false);
    }
}

/*-------------------------------------------------------------*/
/*---MAIN MENU FUNCTION----------------------------------------*/
/*-------------------------------------------------------------*/

void		Menu::manageMenu(gdl::Input &i)
{
  this->launchMenu(i);
  if (this->numM == 0)
    this->loopMenu(0, 4, i);
  if (this->numM == 1)
    {
      this->loopMenu(5, 10, i);
      this->optiConf(i);
      this->selectConf(i);
      this->launchGame(i);
    }
  if (this->numM == 2)
    {
      this->loopMenu(13, 15, i);
      this->selectLoads(i);
    }
  if (this->numM == 3)
    this->selectBack(16, i);
  if (this->numM == 4)
    {
      this->loopMenu(17, 19, i);
      this->selectSounds(i);
    }
  if (this->numM == 5)
    this->selectName(i);
  this->loadMenu(i);
  this->scoresMenu(i);
  this->optionsMenu(i);
}

int	Menu::getNumI() const
{
  return (this->numI);
}

unsigned int Menu::getNumM() const
{
  return (this->numM);
}

void	Menu::setScore(int score)
{
  this->_score = score;
}

void	Menu::setX(unsigned int x)
{
  this->x = x;
}

void	Menu::setY(unsigned int y)
{
  this->y = y;
}

unsigned int Menu::getX() const
{
  return (this->x);
}

unsigned int Menu::getY() const
{
  return (this->y);
}

bool	Menu::getAnimation() const
{
  return (this->animation);
}

int	Menu::getPic() const
{
  return (this->curPic);
}

void	Menu::setPic(int i)
{
  this->curPic = i;
}

void	Menu::setAnimation(bool b)
{
  this->animation = b;
}

unsigned int Menu::getAI() const
{
  return (this->IA);
}

void	Menu::setAI(unsigned int i)
{
  this->IA = i;
}
