#pragma once

#include <QMainWindow>

#include "../core/nonogram.h"
#include "choose_mode_dialog.h"
#include "choose_size_dialog.h"
#include "nonogram_scene.h"
#include "nonogram_view.h"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);

 public slots:
  void setMode(editorMode mode);
  void setSize(int width, int height);

 private:
  void showChooseModeDialog();
  void showChooseSizeDialog();
  editorMode currentMode;
  NonogramScene *scene;
  NonogramView *view;
};