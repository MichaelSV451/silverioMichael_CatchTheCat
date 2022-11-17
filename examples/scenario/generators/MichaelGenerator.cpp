#include "MichaelGenerator.h"
#include "../Noise.h"
#include "../PerlinNoise.hpp"
#include "Random.h"
#include <iostream>

std::vector<Color32> MichaelGenerator::Generate(int sideSize,
                                                float displacement) {
  std::vector<Color32> colors;

  // biome colors
  Vector3 water = {0, 0, 255};
  Vector3 beach = {255, 255, 200};
  Vector3 grass = {0, 200, 100};
  Vector3 forest = {0, 125, 50};
  Vector3 savannah = {75, 125, 50};
  Vector3 mountain = {100, 100, 100};
  Vector3 snow = {255, 255, 255};

  Vector3 snowAdd = {255, 255, 255};

  siv::BasicPerlinNoise<float> noise;
  noise.reseed(1337);

  for (int l = 0; l < sideSize; l++) {
    for (int c = 0; c < sideSize; c++) {
      // get noise and octaves
      float e = noise.octave3D(c / x, l / y, displacement, octaves);

      // set redistribution
      e = powf(e, redistribution);


      Vector3 color = Vector3{0, 0, 0};

      if (l < sideSize / polarDistance && e > waterLevel) {
        e += 100;
      }
      if (l > (sideSize / polarDistance) * (polarDistance - 1) &&
          e > waterLevel) {
        e += 100;
      }
      
      // set biomes
      if (e < waterLevel)
        color = color + water;
      else if (e < beachLevel)
        color = color + beach;
      else if (e < grassLevel)
        color = color + grass;
      else if (e < forestLevel)
        color = color + forest;
      else if (e < savannahLevel)
        color = color + savannah;
      else if (e < mountainLevel)
        color = color + mountain;
      else if (e <= snowLevel || e > snowLevel)
        color = color + snow;
      else {
        color = color + snow;
      }

      colors.emplace_back(color.x, color.y, color.z);

     // // set biomes
     // if (e < waterLevel)
     //   colors.emplace_back(water.x, water.y, water.z);
     // else if (e < beachLevel)
     //   colors.emplace_back(beach.x, beach.y, beach.z);
     // else if (e < grassLevel)
     //   colors.emplace_back(grass.x, grass.y, grass.z);
     // else if (e < forestLevel)
     //   colors.emplace_back(forest.x, forest.y, forest.z);
     // else if (e < savannahLevel)
     //   colors.emplace_back(savannah.x, savannah.y, savannah.z);
     // else if (e < mountainLevel)
     //   colors.emplace_back(mountain.x, mountain.y, mountain.z);
     // else if (e <= snowLevel || e > snowLevel)
     //   colors.emplace_back(snow.x, snow.y, snow.z);
     // else {
     //   colors.emplace_back(water.x, water.y, water.z);
     // }
    }
  }
  // std::cout << colors.size() << std::endl;
  return colors;
}
std::string MichaelGenerator::GetName() { return "Michael Generator"; }
