#include "Prims.h"
#include <stdlib.h>     
#include <time.h> 
#include "Random.h"
#include "../World.h"
#include <unordered_map>
#include <queue>
bool PrimsAlgorithm::Step(World* world) 
{
  bool finished = false;
  srand(time(NULL));
  std::unordered_map<int, std::unordered_map<int, bool>> insideMaze;
  std::vector<Point2D> frontier;
  std::vector<Point2D> added;
  int length = world->GetSize();
  Point2D startPosition{Random::Range(0, world->GetSize()),
                        Random::Range(0, world->GetSize())};
  insideMaze[startPosition.x][startPosition.y] = true;
  added.push_back(startPosition);
  while (!finished) 
  {
    Point2D latest = added.back();
      //iterate over every possible node to see if its been added yet... yuck. 
      //if not add it to the frontier.
      if (!insideMaze[latest.x - 1][latest.y])
      {

      }
  }
}