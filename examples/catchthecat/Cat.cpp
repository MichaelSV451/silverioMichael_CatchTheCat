#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>
#include <unordered_set>
#include <set>

using namespace std;

Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0,5);
  auto pos = world->getCat();

  //create hex graph using offset coordinates
  vector<unordered_set<int>> hexGrid = {};

  for (int i = 0; i < world->getWorldSideSize(); i++) {
      for (int j = 0; j < world->getWorldSideSize(); j++) {
          unordered_set<int> hexCoord = {i, j};
          hexGrid.push_back(hexCoord);
      }
  }
  



  //use pathfinding to get shortest route towards an exit point

  //move towards that direction!

  cout << World::NE(pos).x << ", " << World::NE(pos).y << endl;

  switch(rand){
    case 0:
      return World::NE(pos);
    case 1:
      return World::NW(pos);
    case 2:
      return World::E(pos);  //x + 1
    case 3:
      return World::W(pos);  //x - 1
    case 4:
      return World::SW(pos);
    case 5:
      return World::SE(pos);
    default:
      throw "random out of range";
  }
}
