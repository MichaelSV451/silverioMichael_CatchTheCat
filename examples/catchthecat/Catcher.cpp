#include "Catcher.h"
#include "World.h"

using namespace std;

Point2D Catcher::Move(World* world) {

    cout << "catcher turn" << endl;
    
  auto pos = world->getCat();

  // clear graph
  graph.clear();
  visited.clear();

  // create queue
  vector<QueueEntry> queue;

  // winning spaces
  vector<QueueEntry> winningSpaces;

  // path to take
  vector<QueueEntry> pathToTake;

  // make head of queue current pos
  queue.push_back({Point2D(world->getCat()), 0});
  // mark head as visited
  visited.push_back({Point2D(world->getCat()), 0});

  while (!queue.empty()) {
    QueueEntry source = queue.front();
    queue.erase(queue.begin());

    // add to queue if its a valid position, its not blocked, AND its not
    // visited Look NE
    if (world->isValidPosition(World::NE(source.position)) &&
        !world->getContent(World::NE(source.position)) &&
        !CheckIfVisited(World::NE(source.position))) {
      queue.push_back({Point2D(World::NE(source.position)), source.weight + 1});
      visited.push_back(
          {Point2D(World::NE(source.position)), source.weight + 1});

      if (world->catWinsOnSpace(Point2D(World::NE(source.position))))
        winningSpaces.push_back(
            {Point2D(World::NE(source.position)), source.weight + 1});
    }
    // Look NW
    if (world->isValidPosition(World::NW(source.position)) &&
        !world->getContent(World::NW(source.position)) &&
        !CheckIfVisited(World::NW(source.position))) {
      queue.push_back({Point2D(World::NW(source.position)), source.weight + 1});
      visited.push_back(
          {Point2D(World::NW(source.position)), source.weight + 1});

      if (world->catWinsOnSpace(Point2D(World::NW(source.position))))
        winningSpaces.push_back(
            {Point2D(World::NW(source.position)), source.weight + 1});
    }
    // Look W
    if (world->isValidPosition(World::W(source.position)) &&
        !world->getContent(World::W(source.position)) &&
        !CheckIfVisited(World::W(source.position))) {
      queue.push_back({Point2D(World::W(source.position)), source.weight + 1});
      visited.push_back(
          {Point2D(World::W(source.position)), source.weight + 1});

      if (world->catWinsOnSpace(Point2D(World::W(source.position))))
        winningSpaces.push_back(
            {Point2D(World::W(source.position)), source.weight + 1});
    }
    // Look SW
    if (world->isValidPosition(World::SW(source.position)) &&
        !world->getContent(World::SW(source.position)) &&
        !CheckIfVisited(World::SW(source.position))) {
      queue.push_back({Point2D(World::SW(source.position)), source.weight + 1});
      visited.push_back(
          {Point2D(World::SW(source.position)), source.weight + 1});

      if (world->catWinsOnSpace(Point2D(World::SW(source.position))))
        winningSpaces.push_back(
            {Point2D(World::SW(source.position)), source.weight + 1});
    }
    // Look SE
    if (world->isValidPosition(World::SE(source.position)) &&
        !world->getContent(World::SE(source.position)) &&
        !CheckIfVisited(World::SE(source.position))) {
      queue.push_back({Point2D(World::SE(source.position)), source.weight + 1});
      visited.push_back(
          {Point2D(World::SE(source.position)), source.weight + 1});

      if (world->catWinsOnSpace(Point2D(World::SE(source.position))))
        winningSpaces.push_back(
            {Point2D(World::SE(source.position)), source.weight + 1});
    }
    // Look E
    if (world->isValidPosition(World::E(source.position)) &&
        !world->getContent(World::E(source.position)) &&
        !CheckIfVisited(World::E(source.position))) {
      queue.push_back({Point2D(World::E(source.position)), source.weight + 1});
      visited.push_back(
          {Point2D(World::E(source.position)), source.weight + 1});

      if (world->catWinsOnSpace(Point2D(World::E(source.position))))
        winningSpaces.push_back(
            {Point2D(World::E(source.position)), source.weight + 1});
    }
  }

  // look through winning spaces to find lowest distance
  QueueEntry bestWinningSpace = {pos, 1};
  int lowestDistance = INT_MAX;
  for (int i = 0; i < winningSpaces.size(); i++) {
    if (winningSpaces[i].weight < lowestDistance) {
      bestWinningSpace = winningSpaces[i];
      lowestDistance = winningSpaces[i].weight;
    }
  }

  //plug the best winning space IF ITS NOT ALREADY FULL
  if (!world->getContent(bestWinningSpace.position) && bestWinningSpace.position != pos) {
    cout << "plugging winning space" << endl;
    return bestWinningSpace.position;
  }
  else {
    // plug random point that is a neighor around the cat
    bool plug = false;
    while (!plug) {
      auto rand = Random::Range(0, 5);

      switch (rand) {
        case 0:
          if (world->isValidPosition(World::NE(pos)) &&
              !world->getContent(World::NE(pos))) {
            plug = true;
            return World::NE(pos);
          }
        case 1:
          if (world->isValidPosition(World::NW(pos)) &&
              !world->getContent(World::NW(pos))) {
            plug = true;
            return World::NW(pos);
          }
        case 2:
          if (world->isValidPosition(World::SW(pos)) &&
              !world->getContent(World::SW(pos))) {
            plug = true;
            return World::SW(pos);
          }  // x + 1
        case 3:
          if (world->isValidPosition(World::W(pos)) &&
              !world->getContent(World::W(pos))) {
            plug = true;
            return World::W(pos);
          }  // x - 1
        case 4:
          if (world->isValidPosition(World::SE(pos)) &&
              !world->getContent(World::SE(pos))) {
            plug = true;
            return World::SE(pos);
          }
        case 5:
          if (world->isValidPosition(World::E(pos)) &&
              !world->getContent(World::E(pos))) {
            plug = true;
            return World::E(pos);
          }
        default: {
        }
      }
    }
  
  }
 

 

  


 ////
 //auto side = world->getWorldSideSize()/2;
 //for(;;) {
 //  Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
 //  auto cat = world->getCat();
 //  if(cat.x!=p.x && cat.y!=p.y && !world->getContent(p))
 //    return p;
 //}

  

}
