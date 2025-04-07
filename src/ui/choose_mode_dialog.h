#pragma once

#include <QMessageBox>
#include <QPushButton>

enum editorMode { MODE_SELECT_MODE, MODE_EDIT, MODE_SOLVE };

class ChooseModeDialog : public QMessageBox {
  Q_OBJECT

 public:
  ChooseModeDialog(QWidget *parent = nullptr);
  void show();

 signals:
  void modeSelected(editorMode mode);

 private:
  QPushButton *solveButton;
  QPushButton *editButton;
};