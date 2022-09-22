#include "Catcher.h"
#include "World.h"

Point2D Catcher::Move(World* world) {


    
  // create a graph of the hexagonal grid

  // use pathfinding to get shortest route towards an exit point

  // block that final point! box the cat in!

    //BONUS check if you can plug a hole in the cat's route earlier?



  auto side = world->getWorldSideSize()/2;
  for(;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if(cat.x!=p.x && cat.y!=p.y && !world->getContent(p))
      return p;
  }



}
