#include "../GeneratorBase.h"
#include "../NoiseGeneration.h"
#include "../Noise.h"
#include "../PerlinNoise.hpp"

class NateNoise: public ScenarioGeneratorBase
{
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;
};