#pragma once

#include <QMainWindow>

#include "../core/nonogram.h"
#include "nonogram_scene.h"
#include "nonogram_view.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);

 private:
  NonogramScene *scene;
  NonogramView *view;
};