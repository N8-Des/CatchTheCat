#include "Catcher.h"
#include "World.h"
#include <queue>
#include <unordered_map>

// Priority Queue wrapper shamelessly stolen from redblobgames' A* blog.
template <typename T, typename priority_t>
struct PrioQueue {
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

//ok look I just wanted to make sure it worked and if its still here it means I forgot to put it in a header file. 
struct HexagonTile {
 public:
  Point2D startPosition{0, 0};
  Point2D nextPosition{0, 0};
  int length = 0;
  bool isEnd = false;
  HexagonTile(){};
  bool operator<(const HexagonTile& rhs) const {
    return startPosition.x + startPosition.y <
           rhs.startPosition.x + rhs.startPosition.y;
  }
  bool operator=(const Point2D& rhs) const { return startPosition == rhs; };
};

Point2D GetValue(Point2D point, std::vector<HexagonTile> vec) {
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i].nextPosition == point) {
      return vec[i].startPosition;
    }
  }
  Point2D fail{-100, -100};
  return fail;
};

Point2D Catcher::Move(World* world) {
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();

  std::unordered_map<int, std::unordered_map<int, bool>> hasVisited;
  PrioQueue<HexagonTile, int> frontier;
  std::vector<HexagonTile> cameFrom;

  Point2D finalPoint{0, 0};
  HexagonTile lastHex{};
  lastHex.startPosition = pos;
  lastHex.nextPosition = pos;
  lastHex.length = 0;
  frontier.put(lastHex, 0);
  cameFrom.push_back(lastHex);
  bool end = false;
  do {
    // grab the top point
    HexagonTile thisHex = frontier.get();
    Point2D curr = thisHex.startPosition;

    // populate queue in a very silly way
    Point2D arr[6] = {world->E(curr),  world->NE(curr), world->NW(curr),
                      world->SE(curr), world->SW(curr), world->W(curr)};

    int nextAmt = 0;
    // next, go through them all
    for (int i = 0; i < 6; i++) {
      Point2D next = arr[i];
      if (!hasVisited[next.y][next.x] && !world->getContent(next)) {
        hasVisited[next.y][next.x] = true;
        HexagonTile newHex{};
        newHex.startPosition = curr;
        newHex.nextPosition = next;
        if (!world->isValidPosition(next)) {
          newHex.isEnd = true;
          // cameFrom.push_back(newHex);
          end = true;
          finalPoint = curr;
          break;
        } else {
          cameFrom.push_back(newHex);
        }

        HexagonTile nextHex{};
        nextHex.startPosition = next;
        nextHex.length = thisHex.length += 1;
        frontier.put(nextHex, nextHex.length + 1);
      }
    }
  } while (!end);
  std::vector<Point2D> path;
  Point2D current = finalPoint;
  if (cameFrom.back().startPosition == finalPoint) {
    // point can't be found!
    std::cout << "point cannot be found";
    return pos;
  }
  while (current != pos) {
    path.push_back(current);
    current = GetValue(current, cameFrom);
  }
  return path[path.size() - 1];
}
