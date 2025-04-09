#include "nonogram_scene.h"

NonogramScene::NonogramScene(QWidget *parent) : QGraphicsScene(parent) {
  setSceneRect(QRectF(0, 0, sceneWidth, sceneHeight));
  lineColor = Qt::black;
  emptyCellColor = Qt::white;
  filledCellColor = Qt::black;
  cellSize = 50.0f;

  // Initialize a default nonogram
  setNonogram(*new Nonogram(
      std::vector<std::vector<bool>>(10, std::vector<bool>(10, false))));
}

void NonogramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  handleMousePressed(mouseEvent->scenePos(), mouseEvent->buttons());
}

void NonogramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
  if (mouseEvent->buttons() == Qt::NoButton) {
    return;
  }
  handleMousePressed(mouseEvent->scenePos(), mouseEvent->buttons());
}

void NonogramScene::handleMousePressed(QPointF scenePos,
                                       Qt::MouseButtons buttons) {
  if (nonogram == nullptr) {
    return;
  }

  // Check if trying to paint cells
  if (buttons != Qt::LeftButton && buttons != Qt::RightButton) {
    return;
  }

  // Check if the mouse is over a cell
  QGraphicsItem *item = itemAt(scenePos, QTransform());
  if (item) {
    NonogramCell *cell = dynamic_cast<NonogramCell *>(item);
    if (cell) {
      bool cellTargetValue = (buttons == Qt::LeftButton) ? true : false;

      // Update nonogram if cell's target value is different
      if (nonogram->getCell(cell->getX(), cell->getY()) != cellTargetValue) {
        nonogram->setCell(cell->getX(), cell->getY(), cellTargetValue);
        setNonogram(*nonogram);
      }
    }
  }
}

void NonogramScene::resetGrid(int width, int height) {
  clear();

  // Create a new empty nonogram
  std::vector<std::vector<bool>> nonogramData(height,
                                              std::vector<bool>(width, false));
  nonogram = new Nonogram(nonogramData);

  for (int j = 0; j < height; j++) {
    for (int i = 0; i < width; i++) {
      createCellAtPosition(i, j, false);
    }
  }
}

void NonogramScene::setNonogram(Nonogram &nonogram) {
  int gridWidth = nonogram.getWidth();
  int gridHeight = nonogram.getHeight();

  clear();

  this->nonogram = &nonogram;

  float xOffset = getXOffset();
  float yOffset = getYOffset();

  // Draw nonogram grid
  for (int j = 0; j < gridHeight; j++) {
    for (int i = 0; i < gridWidth; i++) {
      createCellAtPosition(i, j, nonogram.getCell(i, j));
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

void NonogramScene::createCellAtPosition(int x, int y, bool value) {
  // printf("Draw cell at (%d, %d) with value %d\n", x, y, value);
  float xOffset = getXOffset();
  float yOffset = getYOffset();

  NonogramCell *cell = new NonogramCell(x, y);

  cell->setRect(x * cellSize + xOffset, y * cellSize + yOffset, cellSize,
                cellSize);
  cell->setPen(QPen(lineColor));
  cell->setCellColor(value ? filledCellColor : emptyCellColor);

  this->addItem(cell);
}