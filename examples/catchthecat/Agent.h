#ifndef AGENT_H
#define AGENT_H
#include "Point2D.h"
#include <unordered_map>
#include <vector>


class World;


struct QueueEntry {
  Point2D position;  //where i am
  int weight;
  bool operator < (const QueueEntry& rhs) const;
};

class Agent {
public:
  explicit Agent()= default;;
  virtual Point2D Move(World*)=0;

  std::vector<QueueEntry> graph;
  std::vector<QueueEntry> visited;

  bool CheckIfVisited(Point2D thePoint);

  int FindWeightOfPoint(Point2D thePoint);

  //std::vector<Point2D> graph;
  std::vector<Point2D> shortestPath;


  //std::unordered_map<int, std::unordered_map<int, bool>> visited;
  //std::unordered_map<int, std::unordered_map<int, Point2D>> from;

 // int FindShortestDistance(int distances[], bool tSet[], int graphSize);

  void Dijkstra(std::vector<Point2D> graph, int source, int graphSize);


};

#endif  // AGENT_H
