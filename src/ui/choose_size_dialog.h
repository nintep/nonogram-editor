#pragma once

#include <QDialog>
#include <QPushButton>

class ChooseSizeDialog : public QDialog {
  Q_OBJECT

 public:
  ChooseSizeDialog(QWidget* parent = nullptr);
  void show();

 signals:
  void sizeSelected(int width, int height);
  void openSelected();

 private:
  QPushButton* submitButton;
  QPushButton* openButton;
  void setWidth(int width) { this->gridWidth = width; }
  void setHeight(int height) { this->gridHeight = height; }
  void submitButtonClicked();
  void openButtonClicked();
  int gridWidth;
  int gridHeight;
};