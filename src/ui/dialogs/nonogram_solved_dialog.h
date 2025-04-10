#pragma once

#include <QMessageBox>
#include <QPushButton>

#include "../editor_mode.h"

class NonogramSolvedDialog : public QDialog {
  Q_OBJECT

 public:
  NonogramSolvedDialog(QWidget* parent = nullptr);
  void show();

 signals:
  void acceptSelected();

 private:
  void acceptButtonClicked();
  QPushButton* acceptButton;
};