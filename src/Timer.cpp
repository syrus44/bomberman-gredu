//
// Timer.cpp for Timer in /home/cerfon_f//taff/branches/cerfoninou/src
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Thu May  9 14:53:00 2013 florent cerfon
// Last update Fri May 10 18:00:38 2013 florent cerfon
//

#include "Timer.hpp"

void	*Tempo(void *av)
{
  thread_arg<StTime *>	*args = static_cast<thread_arg<StTime *> *>(av);
  Waiter(args->var->_time);
  args->var->_ptr(args->var->_object);
  return (0);
}

