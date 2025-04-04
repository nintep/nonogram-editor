#pragma once

#include <QGraphicsScene>
#include <QWidget>

class NonogramScene : public QGraphicsScene {
  Q_OBJECT

 public:
  explicit NonogramScene(QWidget *parent = nullptr);

  void setLineColor(const QColor &color);
  QColor getLineColor() const { return lineColor; }

  void ResetGrid(int width, int height);

 protected:
  /* void paintEvent(QPaintEvent *event) override;
  void wheelEvent(QWheelEvent *event) override;
  void mousePressEvent(QMouseEvent *event) override;
  void mouseMoveEvent(QMouseEvent *event) override; */

 private:
  int sceneWidth = 5000;
  int sceneHeight = 5000;
  float cellSize;
  QColor lineColor;
  QColor emptyCellColor;
};