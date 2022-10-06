#include "Agent.h"

bool QueueEntry::operator<(const QueueEntry& rhs) const { 
	if (this->weight >= rhs.weight)
    return true;
  else
    return false;

}

bool Agent::CheckIfVisited(Point2D thePoint) { 
    bool found = false;

    for (int i = 0; i < visited.size(); i++) {
      if (thePoint == visited[i].position) found = true;
    }

    return found;
}

int Agent::FindWeightOfPoint(Point2D thePoint) { 
    int weight = 0;

    for (int i = 0; i < visited.size(); i++) {
      if (visited[i].position == thePoint) weight = visited[i].weight;
    }

    return weight;
}

////find vertex with smallest value
//int Agent::FindShortestDistance(int distances[], bool tSet[], int graphSize) {
//
// //  //create a min value
// //int minimum = INT_MAX, ind;
// //
// //for (int i = 0; i < graphSize; i++) {
// //  if (tSet[i] == false && distances[i] <= minimum) {
// //    minimum = distances[i];
// //    ind = i;
// //  }
// //}
// //return ind;
//}

void Agent::Dijkstra(std::vector<Point2D> graph, int source, int graphSize) {

}