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

  Point2D GetValue(Point2D point, std::vector<HexTile> vec) 
  {
      for (int i = 0; i < vec.size(); i++) 
      {
      if (vec[i].nextPosition == point) 
          {
          return vec[i].startPosition;
          }
      }
      Point2D fail{-100, -100};
      return fail;
  };

Point2D Cat::Move(World* world) 
{
    auto rand = Random::Range(0, 5);
    auto pos = world->getCat();

    std::unordered_map<int, std::unordered_map<int, bool>> hasVisited;
    PriorityQueue<HexTile, int> frontier;
    std::vector<HexTile> cameFrom;

    Point2D finalPoint = pos;
    HexTile lastHex{};
    lastHex.startPosition = pos;
    lastHex.nextPosition = pos;
    lastHex.length = 0;
    frontier.put(lastHex, 0);
    cameFrom.push_back(lastHex);
    bool end = false;
    do {
        if (frontier.empty()) 
        {
          end = true;
        }
      // grab the top point
      HexTile thisHex = frontier.get();
      Point2D curr = thisHex.startPosition;

      // populate queue in a very silly way
      Point2D arr[6] = {world->E(curr),  world->NE(curr), world->NW(curr),
                        world->SE(curr), world->SW(curr), world->W(curr)};

      // next, go through them all
      for (int i = 0; i < 6; i++) 
      {
        Point2D next = arr[i];
        if (world->isValidPosition(next)) 
        {
          if (!hasVisited[next.y][next.x] && !world->getContent(next)) 
          {
            hasVisited[next.y][next.x] = true;
            HexTile newHex{};
            newHex.startPosition = curr;
            newHex.nextPosition = next;
            cameFrom.push_back(newHex);
            HexTile nextHex{};
            nextHex.startPosition = next;
            nextHex.length = thisHex.length += 1;
            frontier.put(nextHex, nextHex.length + 1);
          }
        } 
        else 
        {
          HexTile newHex{};
          newHex.startPosition = curr;
          newHex.nextPosition = next;
          newHex.isEnd = true;
          // cameFrom.push_back(newHex);
          end = true;
          finalPoint = curr;
          break;
        }
      }
    } while (!end);
    std::vector<Point2D> path;
    Point2D current = finalPoint;
    if (pos == finalPoint) 
    {
      // point can't be found!
      std::cout << "point cannot be found";
      return pos;
    }
    while (current != pos) {
      path.push_back(current);
      current = GetValue(current, cameFrom);
    }
    return path[path.size() - 1];
  };
