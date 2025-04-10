#pragma once

#include <QFileDialog>
#include <QMainWindow>
#include <QToolBar>

#include "../core/nonogram.h"
#include "../io/io_manager.h"
#include "choose_mode_dialog.h"
#include "choose_size_dialog.h"
#include "editor_mode.h"
#include "nonogram/nonogram_scene.h"
#include "nonogram/nonogram_view.h"

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
  void showSaveAsDialog();
  void showLoadDialog();
  void saveButtonPressed();
  void saveToFile(const QString &filename);
  void loadFromFile(const QString &filename);

  void enterEditMode();
  void enterSolveMode();
  QToolBar *toolBar;

  editorMode currentMode;
  NonogramScene *scene;
  NonogramView *view;
  QString latestNonogramFilePath{""};
};