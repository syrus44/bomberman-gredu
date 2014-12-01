//
// main.cpp for bomberman in /home/caille_l//Documents/cpp/caille_l
// 
// Made by louis cailleux
// Login   <caille_l@epitech.net>
// 
// Started on  Thu May  2 12:59:08 2013 louis cailleux
// Last update Thu Jun  6 14:05:18 2013 louis cailleux
//

#include "Map.hh"
#include "Parser.hh"
#include "Menu.hh"

int	main()
{
  Map  *m = new Map();

  try
    {
      m->run();
    }
  catch (const Exception &e)
    {
      std::cerr << "Error: " << e.what() << std::endl;
    }
}
