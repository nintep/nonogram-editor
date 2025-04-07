#include "nonogram_scene.h"

NonogramScene::NonogramScene(QWidget *parent) : QGraphicsScene(parent) {
  setSceneRect(QRectF(0, 0, sceneWidth, sceneHeight));
  lineColor = Qt::black;
  emptyCellColor = Qt::white;
  filledCellColor = Qt::black;
  cellSize = 50.0f;
}

void NonogramScene::resetGrid(int width, int height) {
  clear();

  gridWidth = width;
  gridHeight = height;

  float xOffset = getXOffset();
  float yOffset = getYOffset();

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      addRect(i * cellSize + xOffset, j * cellSize + yOffset, cellSize,
              cellSize, QPen(lineColor), QBrush(emptyCellColor));
    }
  }
}

void NonogramScene::setNonogram(Nonogram &nonogram) {
  clear();
  gridWidth = nonogram.getWidth();
  gridHeight = nonogram.getHeight();

  float xOffset = getXOffset();
  float yOffset = getYOffset();

  // Draw nonogram grid
  for (int j = 0; j < gridHeight; j++) {
    for (int i = 0; i < gridWidth; i++) {
      QColor cellColor =
          nonogram.getCell(i, j) ? filledCellColor : emptyCellColor;
      addRect(i * cellSize + xOffset, j * cellSize + yOffset, cellSize,
              cellSize, QPen(lineColor), QBrush(cellColor));
    }
  }

  // Draw row hints
  for (int j = 0; j < gridHeight; j++) {
    const auto rowHints = nonogram.getRowHints()[j];
    for (int k = 0; k < rowHints.size(); k++) {
      QPointF hintPos(xOffset - (rowHints.size() - k) * cellSize,
                      j * cellSize + yOffset);
      addText(QString::number(rowHints[k]), QFont("Arial", cellSize / 2))
          ->setPos(hintPos);
    }
  }

  // Draw column hints
  for (int i = 0; i < gridWidth; i++) {
    const auto colHints = nonogram.getColHints()[i];
    for (int k = 0; k < colHints.size(); k++) {
      QPointF hintPos(i * cellSize + xOffset + cellSize / 6,
                      yOffset - (colHints.size() - k) * cellSize);
      addText(QString::number(colHints[k]), QFont("Arial", cellSize / 2))
          ->setPos(hintPos);
    }
  }
}