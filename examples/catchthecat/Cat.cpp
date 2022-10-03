#include "Cat.h"
#include "World.h"
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

Point2D Cat::Move(World* world) {
  auto rand = Random::Range(0, 5);
  auto pos = world->getCat();

  const int DIRECTIONS = 5;

  visited.clear();
  from.clear();

  vector<QueueEntry> queue;
  queue.push_back({pos, 0});

  auto queueHead = queue[0];

  while (!queue.empty()) {

    //sort queue
    sort(queue.begin(), queue.end());
 
    queueHead = queue[0];

    //remove head
    queue.erase(queue.begin());

    //marked head visited
    visited[queueHead.position.x][queueHead.position.y] = true;

    for (int i = 0; i <= DIRECTIONS; i++) {
      Point2D search = {0, 0};

      //set search point
      switch (i) {
        case 0:
          search = World::NE(queueHead.position);
          break;
        case 1:
          search = World::NW(queueHead.position);
          break;
        case 2:
          search = World::E(queueHead.position);
          break;
        case 3:
          search = World::W(queueHead.position);
          break;
        case 4:
          search = World::SW(queueHead.position);
          break;
        case 5:
          search = World::SE(queueHead.position);
          break;
      }

      //if not visited, and is valid position,
      if (!world->getContent(search) && visited[search.x][search.y] == false && world->isValidPosition(search)) {

          cout << "pushing back " << search.x << " , " << search.y << endl;

          //add it to the queue
          queue.push_back({search, queueHead.weight + 1});

          //set from
          from[search.x][search.y] = queueHead.position;
      }
    }

    cout << queue.size() << endl;
  }

 ////clear the map
 //
 //
 ////start queue with position of the cat
 //vector<QueueEntry> queue;
 //
 //from[world->getCat().x][world->getCat().y] = world->getCat();
 //visited[world->getCat().x][world->getCat().y] = true;
 //queue.push_back({world->getCat(), 0});
 //
 ////main loop
 //while (!queue.empty()) {
 //  //sort from beginning to end
 //  sort(queue.begin(), queue.end());
 //
 //  //remove head
 //  queue.erase(queue.begin());
 //
 //  
 //
 //  cout << queue.size() << endl;
 //
 //
 //  //mark head as visited
 //
 //  //for each neighbor:
 //  //if not visited add to the queue with 1 weight
 //  //mark where this element comes from
 //}


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
