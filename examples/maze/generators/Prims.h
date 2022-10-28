#pragma once
#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>

class PrimsAlgorithm : public MazeGeneratorBase {
 public:
  PrimsAlgorithm() = default;
  std::string GetName() override { return "Prim's Algorithm"; };
  bool Step(World* world) override;
  void Clear(World* world) override;
};