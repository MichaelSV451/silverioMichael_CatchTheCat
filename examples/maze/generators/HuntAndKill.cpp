#include "HuntAndKill.h"
#include "../World.h"
#include "Random.h"
#include <climits>

bool HuntAndKill::Step(World* w) {

    //random start point
  if (stack.empty() && !hasStarted) {
      auto sideOver2 = w->GetSize() / 2;
      rowIndex = -sideOver2;
      colIndex = -sideOver2;
      hasStarted = true;
    auto point = randomStartPoint(w);
    if (point.x == INT_MAX && point.y == INT_MAX)
      return false;  // no empty space no fill
    stack.push_back(point);
    w->SetNodeColor(point, Color::Green.Dark());
  }

  if (stack.empty() && hasStarted) {
    auto sideOver2 = w->GetSize() / 2;
    std::cout << "Hunting" << std::endl;

    //loop through index of points,
    Point2D huntPoint = {rowIndex, colIndex};
    huntIndex.push_back(huntPoint);
    rowIndex++;
    if (rowIndex > sideOver2) {
      colIndex++;
      rowIndex = -sideOver2;
    }

    if (colIndex > sideOver2) {
      for (int i = 0; i < huntIndex.size(); i++) {
        w->SetNodeColor(huntIndex[i], Color::Black.Dark());
      }
      return false;
    }
    w->SetNodeColor(huntPoint, Color::Yellow.Dark());
    if (visited[huntPoint.y][huntPoint.x]) return true;
    else {
      for (int i = 0; i < huntIndex.size(); i++) {
        w->SetNodeColor(huntIndex[i], Color::Black.Dark());
      }
      stack.push_back(huntPoint);
      if (rowIndex = -sideOver2) {
        w->SetEast(huntPoint, false);
      } else {
        w->SetWest(huntPoint, false);
      }
      
      w->SetNodeColor(huntPoint, Color::Green.Dark());
    }
      
    

    //auto point = randomStartPoint(w);
    //if (point.x == INT_MAX && point.y == INT_MAX)
    //  return false;  // no empty space no fill
    //stack.push_back(point);
    //w->SetNodeColor(point, Color::Green.Dark());
  }

  // visit the current element
  auto current = stack.back();
  visited[current.y][current.x] = true;
  w->SetNodeColor(current, Color::Black.Dark());


  // check if we should go deeper
  std::vector<Point2D> visitables = getVisitables(w, current);

   // if we should not go deep, clear stack and start hunting
  if (visitables.empty()) {
    
    isHunting = true;
    huntIndex.clear();
    stack.clear();
    std::cout << "end of visitables" << std::endl;
    std::cout << hasStarted << std::endl;
    return true;
  } else {  // go deeper
    auto r = Random::Range(0, visitables.size() - 1);
    auto next = visitables[r];
    w->SetNodeColor(next, Color::Green);
    stack.push_back(next);
    auto delta = next - current;
    // remove walls
    if (delta.y == -1)  // north
      w->SetNorth(current, false);
    else if (delta.x == 1)  // east
      w->SetEast(current, false);
    else if (delta.y == 1)  // south
      w->SetSouth(current, false);
    else if (delta.x == -1)  // west
      w->SetWest(current, false);
    return true;
  }


  // // check if we need to find a new starting point
  // if (stack.empty()) {
  //   auto point = randomStartPoint(w);
  //   if (point.x == INT_MAX && point.y == INT_MAX)
  //     return false;  // no empty space no fill
  //   stack.push_back(point);
  //   w->SetNodeColor(point, Color::Red.Dark());
  // }
  // 
  // // visit the current element
  // auto current = stack.back();
  // visited[current.y][current.x] = true;
  // w->SetNodeColor(current, Color::Red.Dark());
  // 
  // // check if we should go deeper
  // std::vector<Point2D> visitables = getVisitables(w, current);
  // 
  // // if we should not go deep, pop one element from the stack
  // if (visitables.empty()) {
  //   stack.pop_back();
  //   w->SetNodeColor(current, Color::Black);
  //   return true;
  // } else {  // go deeper
  //   auto r = Random::Range(0, visitables.size() - 1);
  //   auto next = visitables[r];
  //   w->SetNodeColor(next, Color::Green);
  //   stack.push_back(next);
  //   auto delta = next - current;
  //   // remove walls
  //   if (delta.y == -1)  // north
  //     w->SetNorth(current, false);
  //   else if (delta.x == 1)  // east
  //     w->SetEast(current, false);
  //   else if (delta.y == 1)  // south
  //     w->SetSouth(current, false);
  //   else if (delta.x == -1)  // west
  //     w->SetWest(current, false);
  //   return true;
  // }
}
void HuntAndKill::Clear(World* world) {
  hasStarted = false;
  huntIndex.clear();
  visited.clear();
  stack.clear();
  auto sideOver2 = world->GetSize() / 2;

  for (int i = -sideOver2; i <= sideOver2; i++) {
    for (int j = -sideOver2; j <= sideOver2; j++) {
      visited[i][j] = false;
    }
  }
}

Point2D HuntAndKill::randomStartPoint(World* world) {
  auto sideOver2 = world->GetSize() / 2;

  for (int y = -sideOver2; y <= sideOver2; y++)
    for (int x = -sideOver2; x <= sideOver2; x++)
      if (!visited[y][x]) return {x, y};
  return {INT_MAX, INT_MAX};
}

void HuntAndKill::Hunt(World* world) { 

    auto sideOver2 = world->GetSize() / 2;

    if (visited[colIndex][rowIndex]) {
    huntIndex.push_back({colIndex, rowIndex});
    }

    colIndex++;
    if (colIndex > sideOver2) {
      colIndex = -sideOver2;
      rowIndex++;
    }

}


std::vector<Point2D> HuntAndKill::getVisitables(World* w,
                                                         const Point2D& p) {
  auto sideOver2 = w->GetSize() / 2;
  std::vector<Point2D> visitables;

  // todo: improve this
  // north
  if ((abs(p.x) <= sideOver2 &&
       abs(p.y - 1) <= sideOver2) &&  // should be inside the board
      !visited[p.y - 1][p.x] &&       // not visited yet
      w->GetNorth({p.x, p.y - 1}))    // has wall
    visitables.emplace_back(p.x, p.y - 1);
  // east
  if ((abs(p.x + 1) <= sideOver2 &&
       abs(p.y) <= sideOver2) &&    // should be inside the board
      !visited[p.y][p.x + 1] &&     // not visited yet
      w->GetNorth({p.x + 1, p.y}))  // has wall
    visitables.emplace_back(p.x + 1, p.y);
  // south
  if ((abs(p.x) <= sideOver2 &&
       abs(p.y + 1) <= sideOver2) &&  // should be inside the board
      !visited[p.y + 1][p.x] &&       // not visited yet
      w->GetNorth({p.x, p.y + 1}))    // has wall
    visitables.emplace_back(p.x, p.y + 1);
  // west
  if ((abs(p.x - 1) <= sideOver2 &&
       abs(p.y) <= sideOver2) &&    // should be inside the board
      !visited[p.y][p.x - 1] &&     // not visited yet
      w->GetNorth({p.x - 1, p.y}))  // has wall
    visitables.emplace_back(p.x - 1, p.y);

  return visitables;
}