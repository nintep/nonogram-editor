#include "main_window.h"

#include <QLabel>
#include <QPushButton>
#include <QStatusBar>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  currentMode = MODE_SELECT_MODE;

  scene = new NonogramScene(this);
  view = new NonogramView(scene, this);
  view->resetViewToCenter();

  toolBar = addToolBar("Main Toolbar");
  statusBar();

  // Short delay before open mode dialog
  QTimer::singleShot(20, this, &MainWindow::showChooseModeDialog);
  setCentralWidget(view);
}

void MainWindow::saveToFile(const QString &filename) {
  if (filename.isEmpty()) {
    return;
  }

  Nonogram *nonogram = scene->getNonogram();
  if (IOManager::saveNonogramTofile(filename, nonogram)) {
    latestNonogramFilePath = filename;
    statusBar()->showMessage("File saved successfully", 2000);
  } else {
    statusBar()->showMessage("Failed to save file", 2000);
  }
}

void MainWindow::loadFromFile(const QString &filename) {
  if (filename.isEmpty()) {
    return;
  }

  Nonogram *nonogram = scene->getNonogram();
  if (IOManager::loadNonogramFromFile(filename, nonogram)) {
    scene->setNonogram(*nonogram);
    view->resetViewToCenter();

    latestNonogramFilePath = filename;
    statusBar()->showMessage("File loaded successfully", 2000);
  } else {
    statusBar()->showMessage("Failed to load file", 2000);
  }
}

void MainWindow::saveButtonPressed() {
  if (latestNonogramFilePath.isEmpty()) {
    showSaveAsDialog();
  } else {
    saveToFile(latestNonogramFilePath);
  }
}

void MainWindow::showChooseModeDialog() {
  ChooseModeDialog dialog(this);
  connect(&dialog, &ChooseModeDialog::modeSelected, this, &MainWindow::setMode);
  dialog.show();
}

void MainWindow::showChooseSizeDialog() {
  printf("Choose size dialog\n");
  ChooseSizeDialog dialog(this);
  connect(&dialog, &ChooseSizeDialog::sizeSelected, this, &MainWindow::setSize);
  connect(&dialog, &ChooseSizeDialog::openSelected, this,
          &MainWindow::showLoadDialog);
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
  if (mode == MODE_SOLVE) {
    enterSolveMode();
  } else if (mode == MODE_EDIT) {
    enterEditMode();
  }
}

void MainWindow::setSize(int width, int height) {
  // TODO: move size validation to the dialog
  int clampedWidth = std::max(2, std::min(width, 50));
  int clampedHeight = std::max(2, std::min(height, 50));
  scene->resetGrid(clampedWidth, clampedHeight);
  view->resetViewToCenter();
}

void MainWindow::enterEditMode() {
  if (currentMode == MODE_EDIT) {
    return;
  }

  // Set up edit mode toolbar
  toolBar->clear();
  QAction *newAction = toolBar->addAction("New");
  QAction *openAction = toolBar->addAction("Open");
  QAction *saveAction = toolBar->addAction("Save");
  QAction *saveAsAction = toolBar->addAction("Save As");

  QWidget *spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  toolBar->addWidget(spacer);

  QAction *solveAction = toolBar->addAction("Solve");

  connect(newAction, &QAction::triggered, this,
          &MainWindow::showChooseSizeDialog);

  connect(saveAction, &QAction::triggered, this,
          &MainWindow::saveButtonPressed);

  connect(saveAsAction, &QAction::triggered, this,
          &MainWindow::showSaveAsDialog);

  connect(openAction, &QAction::triggered, this, &MainWindow::showLoadDialog);
  connect(solveAction, &QAction::triggered, this, &MainWindow::enterSolveMode);

  if (currentMode == MODE_SELECT_MODE) {
    showChooseSizeDialog();
  }

  currentMode = MODE_EDIT;
  scene->setMode(MODE_EDIT);
}

void MainWindow::enterSolveMode() {
  if (currentMode == MODE_SOLVE) {
    return;
  }

  // Set up solve mode toolbar
  toolBar->clear();
  QAction *openAction = toolBar->addAction("Open");

  QWidget *spacer = new QWidget();
  spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  toolBar->addWidget(spacer);

  QAction *editAction = toolBar->addAction("Edit");

  connect(openAction, &QAction::triggered, this, &MainWindow::showLoadDialog);
  connect(editAction, &QAction::triggered, this, &MainWindow::enterEditMode);

  currentMode = MODE_SOLVE;
  scene->setMode(MODE_SOLVE);
}