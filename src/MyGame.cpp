//
// MyGame.cpp for Map in /home/charle_b//bomberman-gredu/trunk
// 
// Made by mael charles
// Login   <charle_b@epitech.net>
// 
// Started on  Sat Jun  8 11:40:25 2013 mael charles
//

#include "Map.hh"
#include "Air.hh"
#include "Explosion.hh"
#include "Menu.hh"

void	display2(void *o)
{
  Map	*m = static_cast<Map *>(o);

  m->closeWindow();
}

void	Map::initialize(void)
{
  this->window_.setWidth(1280);
  this->window_.setHeight(1024);
  this->window_.create();
  this->window_.setTitle("BomberCraft !!");
  this->_showMenu = true;
  this->_menu->initialize();
  this->pause = false;
}

void    Map::initGame()
{
  this->camera.initialize();
  this->camera2.initialize();
  this->mapAir = new Air(0, 0);
  this->mapFloor = new Floor(0, 0, this->mapSizeX, this->mapSizeY);
  this->mapWall = new IronWall(0, 0);
  this->destWall = new WoodWall(0, 0);
  this->mapExpl = new Explosion(this, 0, 0);
  this->mapExpl->setMap(this->map);
  this->isAlone = false;
  this->_AI = 0;
  if (this->filename.size() > 1)
    {
      this->mapSizeX = 0;
      this->mapSizeY = 0;
      this->_filename = filename;
      this->mapFile();
    }
  else
    {
      this->mapSizeX = this->x;
      this->mapSizeY = this->y;
      this->_filename = "";
      this->initMap();
    }
  if (this->_players == 1 && this->_AI == 0)
    this->isAlone = true;
  this->player = this->getHuman(1);
  this->player2 = this->getHuman(0);
  this->mapBorder = new LavaWall(-1, -1, this->mapSizeX, this->mapSizeY);
  this->makePlinth();
  this->tosave = false;
  this->alreadyShown = false;
  this->_AI = this->countAI();
}

void	Map::update(void)
{
  if (this->input_.isKeyDown(gdl::Keys::Escape) == true)
    this->closeWindow();
  if (this->input_.isKeyDown(gdl::Keys::LControl) == true)
    this->_menu->setAnimation(false);
  if (this->_showMenu == false)
    {
      if (this->isAlone == false && this->_players == 1 && this->_AI == 0)
	{
	  this->alreadyShown = true;
	  this->isAlone = true;
	  this->affScores();
	}


      if (this->input_.isKeyDown(gdl::Keys::P) == true)
	{
	  Waiter(120000);
	  if (this->pause == true)
	    this->pause = false;
	  else
	    this->pause = true;
	}

      if (this->pause == false)
	{

	  std::map<int, AObjects *>::iterator x;
	  std::map<int, std::map<int, AObjects *> >::iterator y;
	  this->calcLimits();
	  for (y = this->map.begin(); y != this->map.end(); ++y)
	    {
	      for (x = y->second.begin(); x != y->second.end(); ++x)
		{
		  x->second->unpause();
		  if (x->second->getType() != AObjects::Wall && x->second->getType() != AObjects::Air)
		    if ((x->second->getVecX() > this->lLimit && y->first < this->rLimit &&
			       x->second->getVecZ() > this->uLimit && x->first < this->dLimit) || x->second->getType() == AObjects::Computer || x->second->getType()== AObjects::Human)
		      {
			x->second->update(this->gameClock_, this->input_);
			if (this->getPlayers() == 1)
			  this->camera.update(this->gameClock_, this->input_);
			if (this->getPlayers() == 2)
			  {
			    this->camera.update(this->gameClock_, this->input_);
			    this->camera2.update(this->gameClock_, this->input_);
			  }
		      }
		}
	    }
	}
      else
	{
	  for (std::map<int, std::map<int, AObjects *> >::iterator y = this->map.begin(); y != this->map.end(); ++y)
	    {
	      for (std::map<int, AObjects *>::iterator x = y->second.begin(); x != y->second.end(); ++x)
		x->second->pause();
	    }
	}
    }
  else
    this->timeHandling();
}

void	Map::calcLimits()
{
  this->rLimit = (this->camera._position.x / FLOOR_WIDTH_SIZE) + 10000+ (1280 / (FLOOR_WIDTH_SIZE / 2));
  this->dLimit = (this->camera._position.z / FLOOR_WIDTH_SIZE) + 10000+ (1280 / (FLOOR_WIDTH_SIZE / 2));
  this->lLimit = this->camera._position.x - 100000 - (1600 * 2);
  this->uLimit = this->camera._position.z - 100000- (1600 * 2);
}


void	Map::draw(void)
{  
  ScopedLock(&(this->_mutex));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (this->pause == true)
    {
      
      this->T.setText("Pause");
      this->T.setSize(60);
      this->T.setPosition(10, 60);
      this->T.draw();
    }


  if (this->_showMenu == false)
    {
      std::map<int, AObjects *>::iterator x;
      std::map<int, std::map<int, AObjects *> >::iterator y;
      this->calcLimits();
      switch (this->_texture)
	{
	case 1:
	  glClearColor(0.0f, 0.2f, 0.2f, 0.2);
	  break;
	case 2:
	  glClearColor(1.f, 0.80f, 0.3f, 0.0f);
	  break;
	case 3:
	  glClearColor(0.0f, 0.55f, 0.0f, 0.0f);
	  break;
	case 4:
	  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	  break;
	}
      glClearDepth(1.0f); 
      if (this->getPlayers() == 1)
	{
	  this->camera._position.x = this->player->getVecX();
	  this->camera._position.z = this->player->getVecZ();
	  this->camera.update(this->gameClock_, this->input_);
	  this->drawStatic();
	  this->save();
	  for (y = this->map.begin(); y != this->map.end(); ++y)
	    {
	      for (x = y->second.begin(); x != y->second.end(); ++x)
		{
		  if (x->second->getVecX() > this->lLimit && y->first < this->rLimit &&
	      x->second->getVecZ() > this->uLimit && x->first < this->dLimit)
		    {
		      if (x->second->getType() != AObjects::Wall && x->second->getType() != AObjects::WallDestr)
			x->second->draw();
		    }
		}
	    }
	}
      if (this->getPlayers() == 2)
	this->splitScreen(x, y);
      this->drawScores();
    }
  else
    {
      glDisable(GL_SCISSOR_TEST);
      glViewport(0, 0, this->window_.getWidth(), (this->window_.getHeight()));
      glScissor(0, 0, this->window_.getWidth(), (this->window_.getHeight()));
      glEnable(GL_SCISSOR_TEST);
      this->_menu->draw();
    }
}

void	Map::splitScreen(      std::map<int, AObjects *>::iterator x,
				std::map<int, std::map<int, AObjects *> >::iterator y)
{
  glViewport(0, (this->window_.getHeight() / 2), this->window_.getWidth(), (this->window_.getHeight() / 2));
  glScissor(0, (this->window_.getHeight() / 2), this->window_.getWidth(), (this->window_.getHeight() / 2));
  glEnable(GL_SCISSOR_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->save();
  this->camera._position.x = this->player->getVecX();
  this->camera._position.z = this->player->getVecZ();
  this->camera.update(this->gameClock_, this->input_);
  this->drawStatic();
  for (y = this->map.begin(); y != this->map.end(); ++y)
    for (x = y->second.begin(); x != y->second.end(); ++x)
      if (x->second->getVecX() > this->lLimit && y->first < this->rLimit &&
	      x->second->getVecZ() > this->uLimit && x->first < this->dLimit)
	if (x->second->getType() != AObjects::Wall && x->second->getType() != AObjects::WallDestr)
	  x->second->draw();
  glViewport(0, 0, this->window_.getWidth(), (this->window_.getHeight() / 2));
  glScissor(0, 0, this->window_.getWidth(), (this->window_.getHeight() / 2));
  glEnable(GL_SCISSOR_TEST);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  this->camera2._position.x = this->player2->getVecX();
  this->camera2._position.z = this->player2->getVecZ();
  this->camera2.update(this->gameClock_, this->input_);
  this->drawStatic();
  for (y = this->map.begin(); y != this->map.end(); ++y)
    for (x = y->second.begin(); x != y->second.end(); ++x)
      if (x->second->getVecX() > this->lLimit && y->first < this->rLimit &&
	      x->second->getVecZ() > this->uLimit && x->first < this->dLimit)
	if (x->second->getType() != AObjects::Wall && x->second->getType() != AObjects::WallDestr)
	  x->second->draw();
}

void	Map::drawScores()
{
  std::ostringstream	os;

  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT |
	       GL_ENABLE_BIT | GL_TEXTURE_BIT |
	       GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);

  this->T.setFont("./font/bm.ttf");
  this->T.setSize(30);
  this->T.setPosition(10, 10);
  this->T.setText("Score : ");
  this->T.draw();

  os << this->player->getScore();

  this->T.setText(os.str());
  this->T.setPosition(150, 10);
  this->T.draw();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glPopAttrib();
}
  
void	Map::drawStatic()
{
  this->mapExpl->draw();
  this->mapExpl->setMap(this->map);
  this->mapBorder->draw();
  this->mapFloor->draw();
  this->mapWall->draw();
  this->destWall->draw();
  this->destWall->setMap(this->map);
}

void	Map::unload(void)
{
  this->freeMap();
}

void	Map::makePlinth(void)
{
  this->mapFloor->setTexture(this->_texture);
  this->mapFloor->setVecX(0);
  this->mapFloor->setVecY(0);
  this->mapFloor->setVecZ(0);
  this->mapBorder->setTexture(this->_texture);
  this->mapBorder->setVecX(-300);
  this->mapBorder->setVecY(0);
  this->mapBorder->setVecZ(-300);
}

void	Map::setFileName(std::string const &str)
{
  this->filename = str;
}

void	Map::setSizeX(int sizeX)
{
  this->x = sizeX;
}

void	Map::setSizeY(int sizeY)
{
  this->y = sizeY;
}

void	Map::setPlayers(int pl)
{
  this->_players = pl;
}

void	Map::affCredits()
{
  this->_menu->affCredits();
}

void    Map::closeWindow()
{
  this->window_.close();
}

void    Map::affScores()
{
  this->setFileName("");
  this->_menu->chooseScoreMenu();
  this->_showMenu = true;
  this->_menu->setScore(this->player->getScore());
}

void    Map::setShowMenu(bool b)
{
  this->_showMenu = b;
}

void    Map::save() const
{
  if (this->tosave == true)
    {
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_CURRENT_BIT |
                   GL_ENABLE_BIT | GL_TEXTURE_BIT |
                   GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);
      gdl::Text T("./font/bm.ttf");
      T.setText("Game saved");
      T.setSize(30);
      T.setPosition(1050, 10);
      T.draw();
      glMatrixMode(GL_PROJECTION);
      glPopMatrix();
      glPopAttrib();
    }
}

void    Map::timeHandling()
{
  if (checkKeys() == true)
    {
      if (this->_menu->getAnimation() == false)
	{
	  if (this->gameClock_.getTotalGameTime() - this->t > TIMECLOCK)
	    {
	      
	      if (this->input_.isKeyDown(gdl::Keys::Space) == true)
		this->_sound.playButtonValid();
	      else
		this->_sound.playButton();
	      this->_menu->manageMenu(this->input_);
	      if (this->_menu->quitMenu(this->input_))
		{
		  this->affCredits();
		  Timer<Map>	T(4000000, &display2, this);
		}
	      this->t = this->gameClock_.getTotalGameTime();
	    }
	}
    }
}

bool            Map::checkKeys()
{
  if (this->input_.isKeyDown(gdl::Keys::Up) == true ||
      this->input_.isKeyDown(gdl::Keys::Down) == true ||
      this->input_.isKeyDown(gdl::Keys::Space) == true ||
      this->input_.isKeyDown(gdl::Keys::Escape) == true ||
      this->input_.isKeyDown(gdl::Keys::Back) == true ||
      this->input_.isKeyDown(gdl::Keys::Left) == true ||
      this->input_.isKeyDown(gdl::Keys::Right) == true)
    return (true);
  else
    return (false);
}

void		Map::selectMapSize()
{
  if (this->input_.isKeyDown(gdl::Keys::Up) == true &&
      this->_menu->getNumI() == 11)
    {
      if (this->gameClock_.getTotalGameTime() - this->t2 > 0.2)
	this->_menu->setX(this->_menu->getX() + 1);
      else
	this->_menu->setX(this->_menu->getX() + 5);
      if (this->_menu->getX() >= MAXMAPX)
	this->_menu->setX(MINMAPX);
      this->t2 = this->gameClock_.getTotalGameTime();
    }
  if (this->input_.isKeyDown(gdl::Keys::Down) == true &&
      this->_menu->getNumI() == 11)
    {
      if (this->gameClock_.getTotalGameTime() - this->t2 > 0.2)
	this->_menu->setX(this->_menu->getX() - 1);
      else
	this->_menu->setX(this->_menu->getX() - 5);
      if (this->_menu->getX() <= MINMAPX)
	this->_menu->setX(MAXMAPX);
      this->t2 = this->gameClock_.getTotalGameTime();
    }

  if (this->input_.isKeyDown(gdl::Keys::Up) == true &&
      this->_menu->getNumI() == 12)
    {
      if (this->gameClock_.getTotalGameTime() - this->t2 > 0.2)
	this->_menu->setY(this->_menu->getY() + 1);
      else
	this->_menu->setY(this->_menu->getY() + 5);
      if (this->_menu->getY() >= MAXMAPY)
	this->_menu->setY(MINMAPY);
      this->t2 = this->gameClock_.getTotalGameTime();
    }
  if (this->input_.isKeyDown(gdl::Keys::Down) == true &&
      this->_menu->getNumI() == 12)
    {
      if (this->gameClock_.getTotalGameTime() - this->t2 > 0.2)
	this->_menu->setY(this->_menu->getY() - 1);
      else
	this->_menu->setY(this->_menu->getY() - 5);
      if (this->_menu->getY() <= MINMAPY)
	this->_menu->setY(MAXMAPY);
      this->t2 = this->gameClock_.getTotalGameTime();
    }
}

bool Map::getShown() const
{
  return (this->alreadyShown);
}
