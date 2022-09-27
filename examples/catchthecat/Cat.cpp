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
   public: 
    Point2D startPosition;
    Point2D nextPosition;
    int length = 0;
    HexTile();
    bool operator<(const HexTile& rhs) const
    {
      return startPosition.x + startPosition.y <
             rhs.startPosition.x + rhs.startPosition.y;
    }
  };

  //so basically use a vector and use the HexTile as the queue instead of Point2D. Populate the vector. 
  std::unordered_map<Point2D, bool> hasVisited;
  std::priority_queue<HexTile> frontier;
  std::vector<HexTile> cameFrom;
  //so since point2d doesn't have a constructor, I had to do some stuff. 
  int finalPosX;
  int finalPosY;
  Point2D final{0,0};
  HexTile hex{};
  hex.startPosition = pos;
  hex.length = 0;
  frontier.push(hex);
  //populate the vector I think? 

  while (!frontier.empty()) 
  {
    Point2D curr = frontier.top().startPosition;
    HexTile thisHex = frontier.top();
    frontier.pop();
    
    //populate queue in a very silly way
    Point2D arr[6] = {world->E(curr),  world->NE(curr), world->NW(curr),
                      world->SE(curr), world->SW(curr), world->W(curr)};

    //next, go through them all 
    for (int i = 0; i < 6; i++) {
      Point2D next = arr[i];
      if (!hasVisited[next]) 
      {
        hasVisited[next] = true;
        HexTile hex{};
        hex.startPosition = curr;
        hex.nextPosition = next;        
        cameFrom.push_back(hex);

        HexTile nextHex{};
        nextHex.startPosition = next;
        nextHex.length = thisHex.length += 1;
        frontier.push(nextHex);
      }
    }

    //time to go back.



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
