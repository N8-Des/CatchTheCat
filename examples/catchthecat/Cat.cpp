#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <queue>
#include <unordered_map>
#include <vector>

Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0,5);
  auto pos = world->getCat();

  struct HexTile
  {
    Point2D startPosition;
    Point2D nextPosition;
    int length;
  };

  //so basically use a vector and use the HexTile as the queue instead of Point2D. Populate the vector. 
  std::vector<std::vector<bool>> cameFrom;
  std::queue<Point2D> frontier;
  frontier.push(pos);
  while (!frontier.empty()) 
  {
    Point2D curr = frontier.front();
    frontier.pop();
    
    //populate queue in a very silly way
    frontier.push(world->E(curr));
    frontier.push(world->NE(curr));
    frontier.push(world->NW(curr));
    frontier.push(world->SE(curr));
    frontier.push(world->SW(curr));
    frontier.push(world->W(curr));

    //next, go through them all 


  }
  int amt = world->getWorldSideSize();

  switch(rand){
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);
    case 3:
      return World::W(pos);
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}
