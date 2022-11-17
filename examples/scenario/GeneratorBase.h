#ifndef SCENARIOGENERATORBASE_H
#define SCENARIOGENERATORBASE_H
#include <ColorT.h>
#include <string>
#include <vector>

class ScenarioGeneratorBase {
 protected:
  float redistribution = 1.0;
  float waterLevel = 0.1;
  float beachLevel = 0.2;
  float grassLevel = 0.3;
  float forestLevel = 0.4;
  float savannahLevel = 0.6;
  float mountainLevel = 0.8;
  float snowLevel = 2;
  float polarDistance = 8;
  float x = 100;
  float y = 100;
  int octaves = 4;

 public:
  virtual std::vector<Color32> Generate(int sideSize, float displacement=0)=0;
  virtual std::string GetName()=0;
  virtual void SetValX(float newX) { x = newX; }
  virtual void SetValY(float newY) { y = newY; }
  virtual void SetRedistribution(float newVal) { redistribution = newVal; }
  virtual void SetWaterLevel(float newVal) { waterLevel = newVal; }
  virtual void SetBeachLevel(float newVal) { beachLevel = newVal; }
  virtual void SetGrassLevel(float newVal) { grassLevel = newVal; }
  virtual void SetForestLevel(float newVal) { forestLevel = newVal; }
  virtual void SetSavannahLevel(float newVal) { savannahLevel = newVal; }
  virtual void SetMountainLevel(float newVal) { mountainLevel = newVal; }
  virtual void SetSnowLevel(float newVal) { snowLevel = newVal; }
  virtual void SetOctaves(int newval) { octaves = newval; }
  virtual void SetPolarDistance(float newVal) { polarDistance = newVal; }
};

#endif  // SCENARIOGENERATORBASE_H
