#pragma once

#include <QDialog>
#include <QPushButton>

class ChooseSizeDialog : public QDialog {
  Q_OBJECT

 public:
  ChooseSizeDialog(QWidget *parent = nullptr);
  void show();

 signals:
  void sizeSelected(int width, int height);

 private:
  QPushButton *submitButton;
  void setWidth(int width) { this->gridWidth = width; }
  void setHeight(int height) { this->gridHeight = height; }
  void submitButtonClicked();
  int gridWidth;
  int gridHeight;
};