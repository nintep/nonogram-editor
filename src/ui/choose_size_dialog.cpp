#include "choose_size_dialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

ChooseSizeDialog::ChooseSizeDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Choose Nonogram Size");

  QVBoxLayout *verticalLayout = new QVBoxLayout(this);

  QLabel *description =
      new QLabel("Give the width and height of your nonogram.");
  description->setWordWrap(false);
  verticalLayout->addWidget(description);

  // Set up width input
  QHBoxLayout *inputWidthLayout = new QHBoxLayout();
  QLabel *widthLabel = new QLabel("Width:", this);
  QSpinBox *widthInput = new QSpinBox(this);
  inputWidthLayout->addWidget(widthLabel);
  inputWidthLayout->addWidget(widthInput);
  verticalLayout->addLayout(inputWidthLayout);
  widthInput->setRange(2, 100);
  widthInput->setValue(10);
  connect(widthInput, qOverload<int>(&QSpinBox::valueChanged), this,
          &ChooseSizeDialog::setWidth);

  // Set up height input
  QHBoxLayout *inputHeightLayout = new QHBoxLayout();
  QLabel *heightLabel = new QLabel("Height:", this);
  QSpinBox *heightInput = new QSpinBox(this);
  inputHeightLayout->addWidget(heightLabel);
  inputHeightLayout->addWidget(heightInput);
  verticalLayout->addLayout(inputHeightLayout);
  heightInput->setRange(2, 100);
  heightInput->setValue(10);
  connect(heightInput, qOverload<int>(&QSpinBox::valueChanged), this,
          &ChooseSizeDialog::setHeight);

  submitButton = new QPushButton("Submit", this);
  verticalLayout->addWidget(submitButton);
  connect(submitButton, &QPushButton::clicked, this,
          &ChooseSizeDialog::submitButtonClicked);

  // Center the dialog relative to the main window
  QRect mainWindowGeometry = parentWidget()->geometry();
  QPoint centerPosition = mainWindowGeometry.center();
  move(centerPosition - QPoint(width() / 2, height() / 2));
}

void ChooseSizeDialog::submitButtonClicked() {
  emit sizeSelected(gridWidth, gridHeight);
  accept();
}

void ChooseSizeDialog::show() { exec(); }