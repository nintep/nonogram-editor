#pragma once

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGuiApplication>
#include <QPen>

class NonogramCell : public QGraphicsRectItem {
 public:
  NonogramCell(int x, int y, QGraphicsItem *parent = nullptr)
      : QGraphicsRectItem(parent), x(x), y(y) {}
  void setCellColor(QColor color) { setBrush(QBrush(color)); }
  int getX() const { return x; }
  int getY() const { return y; }

 private:
  int x;
  int y;
};