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

  connect(saveAsAction, &QAction::triggered, this,
          &MainWindow::showSaveAsDialog);

  connect(openAction, &QAction::triggered, this, &MainWindow::showLoadDialog);

  currentMode = MODE_SELECT_MODE;

  scene = new NonogramScene(this);
  scene->resetGrid(20, 20);

  view = new NonogramView(scene, this);
  view->resetViewToCenter();

  // Short delay before open mode dialog
  QTimer::singleShot(20, this, &MainWindow::showChooseModeDialog);
  setCentralWidget(view);
}

void MainWindow::saveToFile(const QString &filename) {
  if (filename.isEmpty()) {
    return;
  }

  printf("Saving to file: %s\n", filename.toStdString().c_str());
  Nonogram *nonogram = scene->getNonogram();
  if (IOManager::saveNonogramTofile(filename, nonogram)) {
    printf("File saved successfully\n");
  } else {
    printf("Failed to save file\n");
  }
}

void MainWindow::loadFromFile(const QString &filename) {
  if (filename.isEmpty()) {
    return;
  }

  Nonogram *nonogram = scene->getNonogram();
  if (IOManager::loadNonogramFromFile(filename, nonogram)) {
    printf("File loaded successfully\n");
    scene->setNonogram(*nonogram);
    view->resetViewToCenter();
  } else {
    printf("Failed to load file\n");
  }
}

void MainWindow::showChooseModeDialog() {
  ChooseModeDialog dialog(this);
  connect(&dialog, &ChooseModeDialog::modeSelected, this, &MainWindow::setMode);
  dialog.show();
}

void MainWindow::showChooseSizeDialog() {
  ChooseSizeDialog dialog(this);
  connect(&dialog, &ChooseSizeDialog::sizeSelected, this, &MainWindow::setSize);
  dialog.show();
}

void MainWindow::showSaveAsDialog() {
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::AnyFile);
  dialog.setNameFilter("Nonogram files (*.nono);;All files (*)");
  dialog.setDefaultSuffix("nono");
  dialog.setAcceptMode(QFileDialog::AcceptSave);

  connect(&dialog, &QFileDialog::fileSelected, this, &MainWindow::saveToFile);

  dialog.exec();
}

void MainWindow::showLoadDialog() {
  QFileDialog dialog(this);
  dialog.setFileMode(QFileDialog::ExistingFiles);
  dialog.setNameFilter("Nonogram files (*.nono)");
  dialog.setDefaultSuffix("nono");
  dialog.setAcceptMode(QFileDialog::AcceptOpen);

  connect(&dialog, &QFileDialog::fileSelected, this, &MainWindow::loadFromFile);

  dialog.exec();
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