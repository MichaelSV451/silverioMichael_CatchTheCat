#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0,5);
  auto pos = world->getCat();

  const Vector2 NORTHWEST;
  const Vector2 NORTHEAST;
  const Vector2 EAST = {1, 0};
  const Vector2 SOUTHEAST;
  const Vector2 SOUTHWEST;
  const Vector2 WEST = {-1, 0};
  

  //clear the map
  visited.clear();
  from.clear();

  //start queue with position of the cat
  vector<QueueEntry> queue;
  queue.push_back({world->getCat(), 0});

  //main loop
  while (!queue.empty()) {
      //sort from beginning to end
    sort(queue.begin(), queue.end());

    //remove head
    queue.erase(queue.begin());

  // //look ne
  // if(world->isValidPosition(World::NE(pos))) 
  //     queue.push_back({World::NE(pos), 1});
  // // look nw
  // if (world->isValidPosition(World::NW(pos))) 
  //     queue.push_back({World::NW(pos), 1});
  // //look e
  // if (world->isValidPosition(World::E(pos)))
  //   queue.push_back({World::E(pos), 1});
  // //look se
  // if (world->isValidPosition(World::SE(pos)))
  //   queue.push_back({World::SE(pos), 1});
  // //look sw
  // if (world->isValidPosition(World::SW(pos)))
  //   queue.push_back({World::SW(pos), 1});
  // //look w
  // if (world->isValidPosition(World::W(pos)))
  //   queue.push_back({World::W(pos), 1});
  // //mark head as visited

    //for each neighbor:
    //if not visited add to the queue with 1 weight
    //mark where this element comes from
  }


  //use pathfinding to get shortest route towards an exit point

  //move towards that direction!


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
