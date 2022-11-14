#include "../Noise.h"
#include "../PerlinNoise.hpp"
#include "MichaelGenerator.h"
#include <iostream>

std::vector<Color32> MichaelGenerator::Generate(int sideSize,
                                                       float displacement) {
  std::vector<Color32> colors;

  Vector3 green = {0, 255, 0};
  Vector3 white = {255, 255, 255};
  Vector3 blue = {0, 0, 255};

  //   create your own function for noise generation
  siv::BasicPerlinNoise<float> noise;
  noise.reseed(1337);


  //  Noise noise(1337, 1024,0,255);
  for (int l = 0; l < sideSize; l++) {
    for (int c = 0; c < sideSize; c++) {
     
        float e = noise.octave3D(c / 75.0, l / 75.0, displacement, octaves);

        e = powf(e, redistribution);

      if (e >= snowLevel)
          colors.emplace_back(white.x, white.y, white.z);
        else if (e < snowLevel && e >= mountainLevel)
          colors.emplace_back(100, 100, 100);
        else if (e < mountainLevel && e >= waterLevel)
          colors.emplace_back(0, 255, 0);
        else if (e < waterLevel)
          colors.emplace_back(0, 0, 255);
        else {
          colors.emplace_back(0, 0, 255);
        }
          

    }
  }
  //std::cout << colors.size() << std::endl;
  return colors;
}
std::string MichaelGenerator::GetName() { return "Michael Generator"; }
