#ifndef __MAIN_HH__
#define __MAIN_HH__

#define GLEW_STATIC

#include <iostream>
#include <memory>
#include <string>
#include <chrono>
#include <fstream>
#include <GL/glew.h>
#include <GL/glfw.h>
#include <GL/glu.h>

#include "engine/managers/sceneManager.hh"
#include "engine/stacks/templateStack.hh"
#include "engine/entitySystem.hh"

#include "game/scenes/introScene.hh"

#include "game/components.hh"

#include "game/systems/movementSystem.hh"
#include "game/messages/tickMessage.hh"


#endif // __MAIN_HH__
