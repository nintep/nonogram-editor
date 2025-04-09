#include "choose_size_dialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QVBoxLayout>

ChooseSizeDialog::ChooseSizeDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Create nonogram");

  gridHeight = 10;
  gridWidth = 10;

  QVBoxLayout *verticalLayout = new QVBoxLayout(this);

  QLabel *createTitle = new QLabel("Create a new nonogram:", this);
  createTitle->setStyleSheet("font-weight: bold; font-size: 16px;");
  verticalLayout->addWidget(createTitle);
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
  widthInput->setRange(2, 50);
  widthInput->setValue(gridWidth);
  connect(widthInput, qOverload<int>(&QSpinBox::valueChanged), this,
          &ChooseSizeDialog::setWidth);

  // Set up height input
  QHBoxLayout *inputHeightLayout = new QHBoxLayout();
  QLabel *heightLabel = new QLabel("Height:", this);
  QSpinBox *heightInput = new QSpinBox(this);
  inputHeightLayout->addWidget(heightLabel);
  inputHeightLayout->addWidget(heightInput);
  verticalLayout->addLayout(inputHeightLayout);
  heightInput->setRange(2, 50);
  heightInput->setValue(gridHeight);
  connect(heightInput, qOverload<int>(&QSpinBox::valueChanged), this,
          &ChooseSizeDialog::setHeight);

  submitButton = new QPushButton("Create", this);
  connect(submitButton, &QPushButton::clicked, this,
          &ChooseSizeDialog::submitButtonClicked);
  verticalLayout->addWidget(submitButton);

  verticalLayout->addSpacerItem(
      new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

  QLabel *openTitle = new QLabel("Edit an existing nonogram:", this);
  openTitle->setStyleSheet("font-weight: bold; font-size: 16px;");
  openButton = new QPushButton("Open", this);
  connect(openButton, &QPushButton::clicked, this,
          &ChooseSizeDialog::openButtonClicked);
  verticalLayout->addWidget(openTitle);
  verticalLayout->addWidget(openButton);

  // Center the dialog relative to the main window
  QRect mainWindowGeometry = parentWidget()->geometry();
  QPoint centerPosition = mainWindowGeometry.center();
  move(centerPosition - QPoint(width() / 2, height() / 2));
}

void ChooseSizeDialog::submitButtonClicked() {
  emit sizeSelected(gridWidth, gridHeight);
  accept();
}

void ChooseSizeDialog::openButtonClicked() {
  emit openSelected();
  accept();
}

void ChooseSizeDialog::show() { exec(); }