#pragma once

#include <QMessageBox>
#include <QPushButton>

#include "../editor_mode.h"

class ChooseModeDialog : public QDialog {
  Q_OBJECT

 public:
  ChooseModeDialog(QWidget* parent = nullptr);
  void show();

 signals:
  void modeSelected(editorMode mode);

 private:
  QPushButton* solveButton;
  QPushButton* editButton;
  void solveButtonClicked();
  void editButtonClicked();
};