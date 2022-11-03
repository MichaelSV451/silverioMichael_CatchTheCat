#ifndef HUNTANDKILL_H
#define HUNTANDKILL_H

#include "../MazeGeneratorBase.h"
#include "Point2D.h"
#include <map>
#include <vector>

class HuntAndKill : public MazeGeneratorBase {
 private:
  std::string myName = "Hunt and Kill"; 
  int rowIndex;
  int colIndex;
  std::vector<Point2D> huntIndex;
  std::vector<Point2D> stack;
  std::map<int, std::map<int, bool>> visited;  // naive. not optimal
  Point2D randomStartPoint(World* world);
  std::vector<Point2D> getVisitables(World* w, const Point2D& p);
  bool hasStarted = false;
  bool isHunting = false;
  void Hunt(World* world);

 public:
  HuntAndKill() = default;
  std::string GetName() override { return myName; };
  bool Step(World* world) override;
  void Clear(World* world) override;
};

#endif  // HUNTANDKILL_H