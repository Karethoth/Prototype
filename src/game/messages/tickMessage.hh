#ifndef __TICKMESSAGE_HH__
#define __TICKMESSAGE_HH__

#include "../../engine/message.hh"

#include <chrono>

typedef std::chrono::duration<float, std::ratio<1,1000>> GameTicks;


class TickMessage : public Engine::Message
{
 public:
  std::chrono::time_point<std::chrono::steady_clock> frameStart;
  std::chrono::microseconds frameDelta;
};

#endif // __TICKMESSAGE_HH__
