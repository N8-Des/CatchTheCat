#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <queue>
#include <unordered_map>
#include <vector>
#include <algorithm>


//Priority Queue wrapper shamelessly stolen from redblobgames' A* blog. 
template <typename T, typename priority_t>
struct PriorityQueue {
  typedef std::pair<priority_t, T> PQElement;
  std::priority_queue<PQElement, std::vector<PQElement>,
                      std::greater<PQElement>>
      elements;

  inline bool empty() const { return elements.empty(); }

  inline void put(T item, priority_t priority) {
    elements.emplace(priority, item);
  }

  T get() {
    T best_item = elements.top().second;
    elements.pop();
    return best_item;
  }
};

//hex tile struct to store all my fancy stuff. 
struct HexTile {
 public:
  Point2D startPosition{0, 0};
  Point2D nextPosition{0, 0};
  int length = 0;
  bool isEnd = false;
  HexTile(){};
  bool operator<(const HexTile& rhs) const {
    return startPosition.x + startPosition.y <
           rhs.startPosition.x + rhs.startPosition.y;
  }
  bool operator=(const Point2D& rhs) const { return startPosition == rhs; };
};



Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0,5);
  auto pos = world->getCat();


  std::unordered_map<int, std::unordered_map<int, bool>> hasVisited;
  PriorityQueue<HexTile, int> frontier;
  std::vector<HexTile> cameFrom;

  Point2D finalPoint{0,0};
  HexTile lastHex{};
  lastHex.startPosition = pos;
  lastHex.length = 0;
  frontier.put(lastHex, 0);
  bool end = false;
  while (!frontier.empty() || end) 
  {
    //grab the top point
    HexTile thisHex = frontier.get();
    Point2D curr = thisHex.startPosition;
    
    //populate queue in a very silly way
    Point2D arr[6] = {world->E(curr),  world->NE(curr), world->NW(curr),
                      world->SE(curr), world->SW(curr), world->W(curr)};

    int nextAmt = 0;
    //next, go through them all 
    for (int i = 0; i < 6; i++) {

      Point2D next = arr[i];
      if (!hasVisited[next.y][next.x]) 
      {
        hasVisited[next.y][next.x] = true;
        HexTile newHex{};
        newHex.startPosition = curr;
        newHex.nextPosition = next;        
        if (world->isValidPosition(arr[i])) 
        {
          newHex.isEnd = true;
          cameFrom.push_back(newHex);
          end = true;
          finalPoint = curr;
        }
        else
        {
          cameFrom.push_back(newHex);
        }

        HexTile nextHex{};
        nextHex.startPosition = next;
        nextHex.length = thisHex.length += 1;
        frontier.put(nextHex, nextHex.length + 1);        
      }
    }

    //time to go back.

    //arbitrary number, point
    std::vector<Point2D> path;
    Point2D current = finalPoint;
    if (cameFrom.back().nextPosition == finalPoint) 
    {
        //point can't be found!
        std::cout << "point cannot be found";
        return pos;
    }
    while (current != pos) 
    {
      path.push_back(current);
      current = std::find(cameFrom, current);
    }

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
