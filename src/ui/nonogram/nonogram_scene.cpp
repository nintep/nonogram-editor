#include "nonogram_scene.h"

NonogramScene::NonogramScene(QWidget *parent) : QGraphicsScene(parent) {
  setSceneRect(QRectF(0, 0, sceneWidth, sceneHeight));
  lineColor = Qt::black;
  emptyCellColor = Qt::white;
  filledCellColor = Qt::black;
  cellSize = 50.0f;

  cellsGroup = new QGraphicsItemGroup();
  hintsGroup = new QGraphicsItemGroup();
  this->addItem(cellsGroup);
  this->addItem(hintsGroup);

  // Initialize a default grid size
  resetGrid(10, 10);
}

void NonogramScene::setMode(editorMode mode) {
  if (currentMode == mode) {
    return;
  }

  if (mode == MODE_SOLVE) {
    // Initialize empty solve state
    solveState = new Nonogram(std::vector<std::vector<bool>>(
        nonogram->getHeight(), std::vector<bool>(nonogram->getWidth(), false)));

    setVisibleCells(*solveState);

    currentMode = MODE_SOLVE;
    return;
  }

  if (mode == MODE_EDIT) {
    if (currentMode == MODE_SOLVE) {
      // Discard current solve state
      if (solveState != nullptr) {
        delete solveState;
        solveState = nullptr;
      }
    }

    setVisibleCells(*nonogram);
    setVisibleHints(*nonogram);

    currentMode = MODE_EDIT;
    return;
  }
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
  foreach (QGraphicsItem *item, cellsGroup->childItems()) {
    if (item->contains(item->mapFromScene(scenePos))) {
      NonogramCell *cell = dynamic_cast<NonogramCell *>(item);
      if (cell) {
        bool cellTargetValue = (buttons == Qt::LeftButton) ? true : false;

        if (currentMode == MODE_SOLVE) {
          // Update solve state
          if (solveState->getCell(cell->getX(), cell->getY()) !=
              cellTargetValue) {
            solveState->setCell(cell->getX(), cell->getY(), cellTargetValue);
            setVisibleCells(*solveState);
          }
        } else if (currentMode == MODE_EDIT) {
          // Update nonogram
          if (nonogram->getCell(cell->getX(), cell->getY()) !=
              cellTargetValue) {
            nonogram->setCell(cell->getX(), cell->getY(), cellTargetValue);
            setVisibleCells(*nonogram);
            setVisibleHints(*nonogram);
          }
        }
        break;
      }
    }
  }
}

void NonogramScene::resetGrid(int width, int height) {
  // Delete the old nonogram
  if (nonogram != nullptr) {
    delete nonogram;
    nonogram = nullptr;
  }

  // Create a new empty nonogram
  std::vector<std::vector<bool>> nonogramData(height,
                                              std::vector<bool>(width, false));
  nonogram = new Nonogram(nonogramData);

  setVisibleCells(*nonogram);
  setVisibleHints(*nonogram);
}

void NonogramScene::setNonogram(Nonogram &nonogram) {
  // Delete the old nonogram
  if (this->nonogram != nullptr && this->nonogram != &nonogram) {
    delete this->nonogram;
  }

  this->nonogram = &nonogram;
  setVisibleCells(nonogram);
  setVisibleHints(nonogram);
}

void NonogramScene::createCellAtPosition(int x, int y, bool value) {
  float xOffset = getXOffset();
  float yOffset = getYOffset();

  NonogramCell *cell = new NonogramCell(x, y);

  cell->setRect(x * cellSize + xOffset, y * cellSize + yOffset, cellSize,
                cellSize);
  cell->setPen(QPen(lineColor));
  cell->setCellColor(value ? filledCellColor : emptyCellColor);

  cellsGroup->addToGroup(cell);
}

void NonogramScene::setVisibleCells(Nonogram &nonogram) {
  // Destroy existing cells
  QList<QGraphicsItem *> items = cellsGroup->childItems();
  foreach (QGraphicsItem *item, items) {
    cellsGroup->removeFromGroup(item);
    delete item;
  }

  // Draw nonogram grid
  for (int j = 0; j < nonogram.getHeight(); j++) {
    for (int i = 0; i < nonogram.getWidth(); i++) {
      createCellAtPosition(i, j, nonogram.getCell(i, j));
    }
  }
}

void NonogramScene::setVisibleHints(Nonogram &nonogram) {
  // Destroy existing hint
  QList<QGraphicsItem *> items = hintsGroup->childItems();
  foreach (QGraphicsItem *item, items) {
    hintsGroup->removeFromGroup(item);
    delete item;
  }

  int gridWidth = nonogram.getWidth();
  int gridHeight = nonogram.getHeight();
  float xOffset = getXOffset();
  float yOffset = getYOffset();

  // Draw row hints
  for (int j = 0; j < gridHeight; j++) {
    const auto rowHints = nonogram.getRowHints()[j];
    for (int k = 0; k < rowHints.size(); k++) {
      QGraphicsTextItem *item =
          addText(QString::number(rowHints[k]), QFont("Arial", cellSize / 2));

      QPointF hintPos(xOffset - (rowHints.size() - k) * cellSize,
                      j * cellSize + yOffset);
      item->setPos(hintPos);
      hintsGroup->addToGroup(item);
    }
  }

  // Draw column hints
  for (int i = 0; i < gridWidth; i++) {
    const auto colHints = nonogram.getColHints()[i];
    for (int k = 0; k < colHints.size(); k++) {
      QGraphicsTextItem *item =
          addText(QString::number(colHints[k]), QFont("Arial", cellSize / 2));

      QPointF hintPos(i * cellSize + xOffset + cellSize / 6,
                      yOffset - (colHints.size() - k) * cellSize);
      item->setPos(hintPos);
      hintsGroup->addToGroup(item);
    }
  }
}
