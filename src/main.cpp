#include <QApplication>

#include "ui/main_window.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  MainWindow window;
  window.resize(600, 600);
  window.setWindowTitle("Nonogram Editor");
  window.show();

  return app.exec();
}