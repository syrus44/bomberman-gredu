//
// Timer.hh for Timer in /home/cerfon_f//taff/branches/cerfoninou/src
// 
// Made by florent cerfon
// Login   <cerfon_f@epitech.net>
// 
// Started on  Wed May  8 16:40:56 2013 florent cerfon
// Last update Thu May 30 19:20:38 2013 louis cailleux
//

#ifndef _TIMER_
#define _TIMER_

#include "Utils.hpp"
#include "Thread.hpp"

typedef	void (*PtTime)(void *);

struct	StTime
{
  int		_time;
  void		*_object;
  PtTime	_ptr;
};

void	*Tempo(void *av);

template <typename T>
class	Timer
{
  ThreadPool<StTime*>	*_thread;
public:
  Timer(int time, PtTime ptr, T *object)
  {
    StTime	*args = new StTime;
    args->_time = time;
    args->_ptr = ptr;
    args->_object = object;
    ThreadPool<StTime*>(&Tempo, args, 1);
  }
  ~Timer() {}
};

#endif /* _TIMER_ */
