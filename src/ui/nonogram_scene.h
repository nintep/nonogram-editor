#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QWidget>
#include <vector>

#include "../core/nonogram.h"
#include "nonogram_cell.h"

class NonogramScene : public QGraphicsScene {
  Q_OBJECT

 public:
  NonogramScene(QWidget *parent = nullptr);
  void resetGrid(int width, int height);
  void setNonogram(Nonogram &nonogram);

 protected:
  void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
  void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;

 private:
  int sceneWidth = 5000;
  int sceneHeight = 5000;
  float cellSize;
  QColor lineColor;
  QColor emptyCellColor;
  QColor filledCellColor;
  Nonogram *nonogram;
  void createCellAtPosition(int x, int y, bool value);
  void handleMousePressed(QPointF scenePos, Qt::MouseButtons buttons);

  float getXOffset() const {
    return (sceneWidth - nonogram->getWidth() * cellSize) / 2;
  }
  float getYOffset() const {
    return (sceneHeight - nonogram->getHeight() * cellSize) / 2;
  }
};