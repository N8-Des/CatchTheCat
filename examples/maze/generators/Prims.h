#pragma once
#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>
#include <unordered_map>

enum direction
{
	North,
	South,
	East,
	West
};
class PrimsAlgorithm : public MazeGeneratorBase {
 public:
  PrimsAlgorithm() = default;
  std::string GetName() override { return "Prim's Algorithm"; };
  bool Step(World* world) override;
  void Clear(World* world) override;
  std::unordered_map<int, std::unordered_map<int, bool>> insideMaze;

  std::vector<Point2D> frontier;
  std::vector<Point2D> added;


};