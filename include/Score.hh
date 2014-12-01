//
// Score.hh for  in /home/dugast_a//CPP/Bomberman/Exception
// 
// Made by antoine dugast
// Login   <dugast_a@epitech.net>
// 
// Started on  Tue Apr 30 14:16:40 2013 antoine dugast
// Last update Sun Jun  9 11:17:03 2013 jordan bettin
//

#ifndef				SCORE_HH
#define				SCORE_HH

#include			"Text.hpp"
#include			<list>
#include			<fstream>
#include			<sstream>
#include			<iostream>

class				Score
{
private:
  std::list<Score>		lst;
  std::list<Score>::iterator	it;
  std::string			name;
  int				score;
public:
  Score();
  ~Score();
  void				init();
  void				cleanScores();
  void				addMemberLst(std::string const &, int);
  void				addMemberFile(std::string const &, int) const;
  void				affScore();
  void				triScore();
  void				affText(std::string const &, int, int, int, gdl::Color) const;
  void				getScores();
};

#endif				/*SCORE_HH*/
