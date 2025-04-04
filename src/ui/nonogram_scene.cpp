#include "nonogram_scene.h"

NonogramScene::NonogramScene(QWidget *parent) : QGraphicsScene(parent) {
  setSceneRect(QRectF(0, 0, sceneWidth, sceneHeight));
  lineColor = Qt::black;
  emptyCellColor = Qt::white;
  cellSize = 50.0f;
}

void NonogramScene::setLineColor(const QColor &color) { lineColor = color; }

void NonogramScene::ResetGrid(int width, int height) {
  clear();

  QPointF center = sceneRect().center();
  float xOffset = (sceneWidth - width * cellSize) / 2;
  float yOffset = (sceneHeight - height * cellSize) / 2;

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      addRect(i * cellSize + xOffset, j * cellSize + yOffset, cellSize,
              cellSize, QPen(lineColor), QBrush(emptyCellColor));
    }
  }
}