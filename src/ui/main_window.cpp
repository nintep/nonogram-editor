#include "main_window.h"

#include <QToolBar>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  scene = new NonogramScene(this);
  scene->ResetGrid(50, 20);

  view = new NonogramView(scene, this);
  view->resetViewToCenter();

  setCentralWidget(view);
  setWindowTitle(tr("Nonogram Editor"));

  QToolBar *toolbar = addToolBar("toolbar");
  QAction *open = toolbar->addAction("Open");
  QAction *save = toolbar->addAction("Save");
  QAction *saveAs = toolbar->addAction("Save As");
}