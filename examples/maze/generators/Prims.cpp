#include "Prims.h"
#include <stdlib.h>     
#include <time.h> 
#include "Random.h"
bool PrimsAlgorithm::Step(World* world) 
{
  bool finished = false;
  srand(time(NULL));
  std::vector<Point2D> pointsIn;
  std::vector<Point2D> frontier;
  int length = world->sideSize;
  Point2D startPosition { Random::Range(0, world->sideSize) }
  while (!finished) 
  {
	
  }
}