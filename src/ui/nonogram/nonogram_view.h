#pragma once

#include <QGraphicsView>

#include "nonogram_scene.h"

class NonogramView : public QGraphicsView {
  Q_OBJECT

 public:
  NonogramView(NonogramScene *scene, QWidget *parent = nullptr);
  void resetViewToCenter();

 protected:
  void wheelEvent(QWheelEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseReleaseEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override;
  void showEvent(QShowEvent *event) override;

 private:
  NonogramScene *nonogramScene;
  bool isDragging = false;
  QPointF lastMousePos;
  float defaultViewPadding = 60.0f;
};