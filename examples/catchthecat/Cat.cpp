#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;


Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();
  
  //clear graph
  graph.clear();
  visited.clear();

  //create queue
  vector<QueueEntry> queue;

  //winning spaces
  vector<QueueEntry> winningSpaces;

  //path to take
  vector<QueueEntry> pathToTake;

  //make head of queue current pos
  queue.push_back({Point2D(world->getCat()), 0});
  //mark head as visited 
  visited.push_back({Point2D(world->getCat()), 0});

  while (!queue.empty()) {
        
      QueueEntry source = queue.front();
      queue.erase(queue.begin());

      
      //add to queue if its a valid position, its not blocked, AND its not visited
      //Look NE
      if (world->isValidPosition(World::NE(source.position)) && !world->getContent(World::NE(source.position)) && !CheckIfVisited(World::NE(source.position)))
      {
        queue.push_back({Point2D(World::NE(source.position)), source.weight +1});
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
        queue.push_back(
            {Point2D(World::NW(source.position)), source.weight + 1});
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
        queue.push_back(
            {Point2D(World::W(source.position)), source.weight + 1});
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
        queue.push_back(
            {Point2D(World::SW(source.position)), source.weight + 1});
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
        queue.push_back(
            {Point2D(World::SE(source.position)), source.weight + 1});
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
        queue.push_back(
            {Point2D(World::E(source.position)), source.weight + 1});
        visited.push_back(
            {Point2D(World::E(source.position)), source.weight + 1});

         if (world->catWinsOnSpace(Point2D(World::E(source.position))))
          winningSpaces.push_back(
              {Point2D(World::E(source.position)), source.weight + 1});
      }

  }

  //look through winning spaces to find lowest distance
  QueueEntry bestWinningSpace;
  int lowestDistance = INT_MAX;
  for (int i = 0; i < winningSpaces.size(); i++) 
      {
    if (winningSpaces[i].weight < lowestDistance) {
      bestWinningSpace = winningSpaces[i];
      lowestDistance = winningSpaces[i].weight;
    }   
  }
  
  cout << "Best winning space is " << bestWinningSpace.position.x << ", "
       << bestWinningSpace.position.y << " with a distance of "
       << bestWinningSpace.weight << endl;

  //now that we've got the best space, find the best path to it
  vector<Point2D> neighbors;

  //push back all of our neighbors if valid
  if (world->isValidPosition(World::NE(pos)) && !world->getContent(World::NE(pos))) {
    neighbors.push_back(World::NE(pos));
  }
  if (world->isValidPosition(World::NW(pos)) &&
      !world->getContent(World::NW(pos))) {
    neighbors.push_back(World::NW(pos));
  }
  if (world->isValidPosition(World::W(pos)) &&
      !world->getContent(World::W(pos))) {
    neighbors.push_back(World::W(pos));
  }
  if (world->isValidPosition(World::SW(pos)) &&
      !world->getContent(World::SW(pos))) {
    neighbors.push_back(World::SW(pos));
  }
  if (world->isValidPosition(World::SE(pos)) &&
      !world->getContent(World::SE(pos))) {
    neighbors.push_back(World::SE(pos));
  }
  if (world->isValidPosition(World::E(pos)) &&
      !world->getContent(World::E(pos))) {
    neighbors.push_back(World::E(pos));
  }

  Point2D pointToGoTo;
  int pointWeight = INT_MAX;

  //Get weight of our neighbors, then go to lowest weighted point
  for(int i = 0; i < neighbors.size(); i++) {
    if (FindWeightOfPoint(neighbors[i]) < pointWeight) {
        pointWeight = FindWeightOfPoint(neighbors[i]);
      pointToGoTo = neighbors[i];
    }
  }

  return pointToGoTo;

  
  //print winning spaces
 // for (int i = 0; i < winningSpaces.size(); i ++) {
 //   cout << winningSpaces[i].position.x << ", " << winningSpaces[i].position.y << endl;
 //   cout << "Distance from source is " << winningSpaces[i].weight << endl;
 // }
 


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
