#ifndef MICHAELGENERATOR_H
#define MICHAELGENERATOR_H

#include "../GeneratorBase.h"

class MichaelGenerator : public ScenarioGeneratorBase {
 public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;
};

#endif  // MICHAELGENERATOR_H
