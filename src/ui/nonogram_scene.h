#pragma once

#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QWidget>

#include "../core/nonogram.h"

class NonogramScene : public QGraphicsScene {
  Q_OBJECT

 public:
  explicit NonogramScene(QWidget *parent = nullptr);
  void resetGrid(int width, int height);
  void setNonogram(Nonogram &nonogram);

 private:
  int sceneWidth = 5000;
  int sceneHeight = 5000;
  int gridWidth;
  int gridHeight;
  float cellSize;
  QColor lineColor;
  QColor emptyCellColor;
  QColor filledCellColor;

  float getXOffset() const { return (sceneWidth - gridWidth * cellSize) / 2; }
  float getYOffset() const { return (sceneHeight - gridHeight * cellSize) / 2; }
};