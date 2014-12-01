//
// Exception.hh for  in /home/dugast_a//CPP/Bomberman/Exception
// 
// Made by antoine dugast
// Login   <dugast_a@epitech.net>
// 
// Started on  Tue Apr 30 13:47:38 2013 antoine dugast
// Last update Tue Apr 30 13:47:39 2013 antoine dugast
//

#ifndef			EXCEPTION_HH
#define			EXCEPTION_HH

#include		<iostream>
#include		<sstream>
#include		<exception>

class			Exception : public std::exception
{
public:
  Exception(const char *);
  virtual ~Exception() throw();
  virtual const char *what() const throw();
private:
  std::string msg;
};

#endif			/*EXCEPTION_HH*/
