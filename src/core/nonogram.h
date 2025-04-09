#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>

class Nonogram {
 public:
  Nonogram(std::vector<std::vector<bool>> nonogramData);
  void setCell(int x, int y, bool value);
  bool getCell(int x, int y) const;
  void setData(std::vector<std::vector<bool>> nonogramData);
  int getWidth() const { return width; }
  int getHeight() const { return height; }
  std::vector<std::vector<bool>> getCells() const { return cells; }
  std::vector<std::vector<int>> getRowHints() const { return rowHints; }
  std::vector<std::vector<int>> getColHints() const { return colHints; }
  void printNonogram() const;

 private:
  int width;
  int height;
  std::vector<std::vector<bool>> cells;
  std::vector<std::vector<int>> rowHints;
  std::vector<std::vector<int>> colHints;
  void calculateHints();
};