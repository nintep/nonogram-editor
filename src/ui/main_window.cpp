#include "main_window.h"

#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QToolBar *toolbar = addToolBar("toolbar");
  QAction *newAction = toolbar->addAction("New");
  QAction *openAction = toolbar->addAction("Open");
  QAction *saveAction = toolbar->addAction("Save");
  QAction *saveAsAction = toolbar->addAction("Save As");

  connect(newAction, &QAction::triggered, this,
          &MainWindow::showChooseSizeDialog);

  currentMode = MODE_SELECT_MODE;

  scene = new NonogramScene(this);
  scene->resetGrid(20, 20);

  view = new NonogramView(scene, this);
  view->resetViewToCenter();

  QTimer::singleShot(20, this, &MainWindow::showChooseModeDialog);

  /* std::vector<std::vector<bool>> nonogramData = {
      {true, true, true, false, true},    {false, false, false, true, false},
      {false, true, false, true, false},  {false, false, false, true, false},
      {false, true, true, true, false},   {false, true, false, true, false},
      {false, true, true, true, false},   {false, true, false, true, false},
      {false, true, false, true, false},  {false, true, false, false, false},
      {false, false, true, false, false}, {false, true, true, true, false},
      {false, false, false, true, true},  {false, true, true, true, false},
      {false, true, false, true, true},   {false, true, false, true, false},
      {false, true, false, true, true},   {false, true, false, true, false},
      {true, false, true, false, true}};

  Nonogram *nonogram = new Nonogram(nonogramData); */

  setCentralWidget(view);
}

void MainWindow::showChooseModeDialog() {
  ChooseModeDialog dialog(this);
  bool connected = connect(&dialog, &ChooseModeDialog::modeSelected, this,
                           &MainWindow::setMode);
  dialog.show();
}

void MainWindow::showChooseSizeDialog() {
  ChooseSizeDialog dialog(this);
  bool connected = connect(&dialog, &ChooseSizeDialog::sizeSelected, this,
                           &MainWindow::setSize);
  dialog.show();
}

void MainWindow::setMode(editorMode mode) {
  printf("Choose mode");
  if (mode == MODE_SOLVE) {
    printf("Solve mode selected\n");
    currentMode == MODE_SOLVE;
  } else if (mode == MODE_EDIT) {
    printf("Edit mode selected\n");
    currentMode == MODE_EDIT;
    showChooseSizeDialog();
  }
}

void MainWindow::setSize(int width, int height) {
  printf("Choose size %d x %d\n", width, height);
  // TODO: move size validation to the dialog
  int clampedWidth = std::max(2, std::min(width, 50));
  int clampedHeight = std::max(2, std::min(height, 50));
  scene->resetGrid(clampedWidth, clampedHeight);
  view->resetViewToCenter();
}