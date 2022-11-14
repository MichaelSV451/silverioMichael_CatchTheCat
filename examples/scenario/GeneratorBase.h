#ifndef SCENARIOGENERATORBASE_H
#define SCENARIOGENERATORBASE_H
#include <ColorT.h>
#include <string>
#include <vector>

class ScenarioGeneratorBase {
 protected:
  float redistribution = 1.0;
  float waterLevel = 0.1;
  int octaves = 3;

 public:
  virtual std::vector<Color32> Generate(int sideSize, float displacement=0)=0;
  virtual std::string GetName()=0;
  virtual void SetRedistribution(float newVal) { redistribution = newVal; }
  virtual void SetWaterLevel(float newVal) { waterLevel = newVal; }
  virtual void SetOctaves(int newval) { octaves = newval; }
};

#endif  // SCENARIOGENERATORBASE_H
