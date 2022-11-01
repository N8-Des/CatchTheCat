#include "Prims.h"
#include "Random.h"
#include "../World.h"
#include <unordered_map>
#include <algorithm>
void PrimsAlgorithm::Clear(World* world) 
{ 
    added.clear();
    insideMaze.clear();
    frontier.clear();
}
bool PrimsAlgorithm::Step(World* world) 
{
  if (added.size() == 0) 
  {
    Point2D startPosition{Random::Range(0, world->GetSize() / 2),
                          Random::Range(0, world->GetSize() / 2)};
    insideMaze[startPosition.x][startPosition.y] = true;
    added.push_back(startPosition);
  }
  if (added.size() >= world->GetSize() * world->GetSize()) 
  { 
      return false;
  }
      Point2D latest = added.back();
      //iterate over every possible node to see if its been added yet... yuck. 
      //if not add it to the frontier.
      Point2D next{latest.x - 1, latest.y};
      if (!insideMaze[next.x][next.y] && world->IsValidPosition(next) &&
          std::find(frontier.begin(), frontier.end(), next) == frontier.end())
      {
        world->SetNodeColor(next, Color::OrangeRed);
        frontier.push_back(next);
      }

      next = Point2D{latest.x + 1, latest.y};
      if (!insideMaze[next.x][next.y] && world->IsValidPosition(next) &&
          std::find(frontier.begin(), frontier.end(), next) == frontier.end())
      {
        world->SetNodeColor(next, Color::OrangeRed);
        frontier.push_back(next);
      }

      next = Point2D{latest.x, latest.y - 1};
      if (!insideMaze[next.x][next.y] && world->IsValidPosition(next) &&
          std::find(frontier.begin(), frontier.end(), next) == frontier.end())
      {
        world->SetNodeColor(next, Color::OrangeRed);
        frontier.push_back(next);
      }

      next = Point2D{latest.x, latest.y + 1};
      if (!insideMaze[next.x][next.y] && world->IsValidPosition(next) &&
          std::find(frontier.begin(), frontier.end(), next) == frontier.end())
      {
        world->SetNodeColor(next, Color::OrangeRed);
        frontier.push_back(next);
      }
      auto vecSize = frontier.size();
      int randIndex = Random::Range(0, vecSize - 1);
      Point2D nextPoint = frontier[randIndex];
      frontier.erase(frontier.begin() + randIndex);
      added.push_back(nextPoint);
      insideMaze[nextPoint.x][nextPoint.y] = true;
      std::cout << nextPoint.x << " " << nextPoint.y << std::endl;
      world->SetNodeColor(nextPoint, Color::Black);
      if (added.size() != 1) 
      {
          //ok so next we take everything in the frontier, and grab a random point from the list. 
          std::vector<direction> validDirectons;
          //now we grab all of the points its next to, and check to see which ones are already in the list. 
          //so lets do the same thing again but backwards. Awesome :)
          if (insideMaze[nextPoint.x - 1][nextPoint.y]) 
          {
            validDirectons.push_back(direction::West);
          }
          if (insideMaze[nextPoint.x + 1][nextPoint.y]) {
            validDirectons.push_back(direction::East);
          }
          if (insideMaze[nextPoint.x][nextPoint.y + 1]) {
            validDirectons.push_back(direction::South);
          }
          if (insideMaze[nextPoint.x][nextPoint.y - 1]) {
            validDirectons.push_back(direction::North);
          }
          
          //grab a random position from the options...
          int randIndexDirection = Random::Range(0, validDirectons.size() - 1);
          direction dir = validDirectons[randIndexDirection];
          //and remove the wall connecting it!
          switch (dir) 
          { 
            case North:
              world->SetNorth(nextPoint, false);
              break;
            case East:
              world->SetEast(nextPoint, false);
              break;
            case South:
              world->SetSouth(nextPoint, false);
              break;
            case West:
              world->SetWest(nextPoint, false);
              break;
          }          
      }
      return true;
}