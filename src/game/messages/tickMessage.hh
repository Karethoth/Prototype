#ifndef __TICKMESSAGE_HH__
#define __TICKMESSAGE_HH__

#include "../../engine/message.hh"

#include <chrono>

typedef std::chrono::duration<int, std::ratio<1,10000>> gameTicks;


class TickMessage : public Engine::Message
{
 public:
  std::chrono::time_point<std::chrono::high_resolution_clock> frameStart;
  gameTicks frameDelta;
};

#endif // __TICKMESSAGE_HH__
