#pragma once

#include <QGraphicsItemGroup>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QWidget>
#include <vector>

#include "../../core/nonogram.h"
#include "../editor_mode.h"
#include "nonogram_cell.h"

class NonogramScene : public QGraphicsScene {
  Q_OBJECT

 public:
  NonogramScene(QWidget *parent = nullptr);
  void resetGrid(int width, int height);
  void setNonogram(Nonogram &nonogram);
  Nonogram *getNonogram() { return nonogram; };
  void setMode(editorMode mode);

 signals:
  void nonogramSolved();

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
  editorMode currentMode;

  Nonogram *nonogram;
  Nonogram *solveState;

  QGraphicsItemGroup *cellsGroup;
  QGraphicsItemGroup *hintsGroup;

  void setVisibleCells(Nonogram &nonogram);
  void setVisibleHints(Nonogram &nonogram);

  void createCellAtPosition(int x, int y, bool value);
  void handleMousePressed(QPointF scenePos, Qt::MouseButtons buttons);

  float getXOffset() const {
    return (sceneWidth - nonogram->getWidth() * cellSize) / 2;
  }
  float getYOffset() const {
    return (sceneHeight - nonogram->getHeight() * cellSize) / 2;
  }
};