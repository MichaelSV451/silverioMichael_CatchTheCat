#include "Catcher.h"
#include "World.h"

using namespace std;

Point2D Catcher::Move(World* world) {


    
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
  QueueEntry bestWinningSpace;
  int lowestDistance = INT_MAX;
  for (int i = 0; i < winningSpaces.size(); i++) {
    if (winningSpaces[i].weight < lowestDistance) {
      bestWinningSpace = winningSpaces[i];
      lowestDistance = winningSpaces[i].weight;
    }
  }

  //plug the best winning space IF ITS NOT ALREADY FULL
  if(!world->getContent(bestWinningSpace.position)) return bestWinningSpace.position;

  //else plug a position right next to the cat
  auto side = world->getWorldSideSize()/2;
  for(;;) {
    Point2D p = {Random::Range(-side, side), Random::Range(-side, side)};
    auto cat = world->getCat();
    if(cat.x!=p.x && cat.y!=p.y && !world->getContent(p))
      return p;
  }



}
