#ifndef MICHAELGENERATOR_H
#define MICHAELGENERATOR_H

#include "../GeneratorBase.h"

class MichaelGenerator : public ScenarioGeneratorBase {
 private:
  //float waterLevel = 0.1;
  float snowLevel = 0.8;
  float mountainLevel = 0.5;


 public:
  std::vector<Color32> Generate(int sideSize, float displacement = 0) override;
  std::string GetName() override;
  

};

#endif  // MICHAELGENERATOR_H
