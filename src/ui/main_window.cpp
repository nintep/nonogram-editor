#include "main_window.h"

#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  std::vector<std::vector<bool>> nonogramData = {
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

  Nonogram *nonogram = new Nonogram(nonogramData);

  scene = new NonogramScene(this);
  // scene->resetGrid(50, 20);
  scene->setNonogram(*nonogram);

  view = new NonogramView(scene, this);
  view->resetViewToCenter();

  setCentralWidget(view);

  QToolBar *toolbar = addToolBar("toolbar");
  QAction *open = toolbar->addAction("Open");
  QAction *save = toolbar->addAction("Save");
  QAction *saveAs = toolbar->addAction("Save As");
}