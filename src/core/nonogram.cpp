#include "nonogram.h"

Nonogram::Nonogram(std::vector<std::vector<bool>> nonogramData) {
  setData(nonogramData);
}

void Nonogram::setData(std::vector<std::vector<bool>> nonogramData) {
  cells = nonogramData;

  if (cells.empty()) {
    throw std::invalid_argument("Nonogram data cannot be empty");
  }
  for (const auto &row : cells) {
    if (row.size() != cells[0].size()) {
      throw std::invalid_argument("All rows must have the same length");
    }
  }

  width = cells[0].size();
  height = cells.size();

  calculateHints();
}

bool Nonogram::getCell(int x, int y) const {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    throw std::out_of_range("Cell coordinates are out of range");
  }
  return cells[y][x];
}

void Nonogram::setCell(int x, int y, bool value) {
  if (x < 0 || x >= width || y < 0 || y >= height) {
    throw std::out_of_range("Cell coordinates are out of range");
  }
  cells[y][x] = value;
  calculateHints();
}

void Nonogram::calculateHints() {
  rowHints.clear();
  colHints.clear();

  rowHints.resize(cells.size());
  colHints.resize(cells[0].size());

  // Calculate row hints
  for (int j = 0; j < height; ++j) {
    int count = 0;
    for (int i = 0; i < width; ++i) {
      if (cells[j][i]) {
        count++;
      } else if (count > 0) {
        rowHints[j].push_back(count);
        count = 0;
      }
    }
    if (count > 0) {
      rowHints[j].push_back(count);
    }
  }

  // Calculate column hints
  for (int i = 0; i < width; ++i) {
    int count = 0;
    for (int j = 0; j < height; ++j) {
      if (cells[j][i]) {
        count++;
      } else if (count > 0) {
        colHints[i].push_back(count);
        count = 0;
      }
    }
    if (count > 0) {
      colHints[i].push_back(count);
    }
  }
}

bool Nonogram::equals(const Nonogram &other) const {
  if (width != other.getWidth() || height != other.getHeight()) {
    return false;
  }
  for (int j = 0; j < height; ++j) {
    for (int i = 0; i < width; ++i) {
      if (cells[j][i] != other.cells[j][i]) {
        return false;
      }
    }
  }
  return true;
}