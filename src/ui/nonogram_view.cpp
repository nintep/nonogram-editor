#include "nonogram_view.h"

#include <QScrollBar>
#include <QWheelEvent>

NonogramView::NonogramView(NonogramScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent) {
  lastMousePos = QPointF(0, 0);
}

void NonogramView::showEvent(QShowEvent *event) {
  QGraphicsView::showEvent(event);
  resetViewToCenter();
}

void NonogramView::resetViewToCenter() {
  QRectF boundingRect = scene()->itemsBoundingRect();
  fitInView(boundingRect, Qt::KeepAspectRatio);
}

void NonogramView::wheelEvent(QWheelEvent *event) {
  if (event->angleDelta().y() > 0) {
    scale(1.2, 1.2);
  } else {
    scale(0.8, 0.8);
  }
}

void NonogramView::mousePressEvent(QMouseEvent *event) {
  if (event->button() == Qt::MiddleButton) {
    isDragging = true;
    lastMousePos = event->pos();
  } else {
    QGraphicsView::mousePressEvent(event);
  }
}

void NonogramView::mouseReleaseEvent(QMouseEvent *event) {
  if (event->button() == Qt::MiddleButton) {
    isDragging = false;
    lastMousePos = event->pos();
  } else {
    QGraphicsView::mousePressEvent(event);
  }
}

void NonogramView::mouseMoveEvent(QMouseEvent *event) {
  if (isDragging) {
    QPointF delta = event->pos() - lastMousePos;
    horizontalScrollBar()->setValue(horizontalScrollBar()->value() - delta.x());
    verticalScrollBar()->setValue(verticalScrollBar()->value() - delta.y());
  }

  lastMousePos = event->pos();
}