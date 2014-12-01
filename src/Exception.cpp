//
// Exception.cpp for  in /home/dugast_a//CPP/Bomberman/Exception
// 
// Made by antoine dugast
// Login   <dugast_a@epitech.net>
// 
// Started on  Tue Apr 30 13:49:11 2013 antoine dugast
// Last update Tue Apr 30 13:49:13 2013 antoine dugast
//

#include	"Exception.hh"

Exception::Exception(const char *msg)
{
  std::ostringstream oss;

  oss << msg << ".";
  this->msg = oss.str();
}

Exception::~Exception() throw ()
{}

const char *Exception::what() const throw ()
{
  return (this->msg.c_str());
}
