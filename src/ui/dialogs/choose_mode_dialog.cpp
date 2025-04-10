#include "choose_mode_dialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

ChooseModeDialog::ChooseModeDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Choose mode");

  QVBoxLayout *verticalLayout = new QVBoxLayout(this);

  QLabel *description = new QLabel(
      "To solve a nonogram, choose 'Solve'. To create or edit one, choose "
      "'Create'",
      this);
  verticalLayout->addWidget(description);

  QHBoxLayout *horizontalLayout = new QHBoxLayout(this);

  solveButton = new QPushButton("Solve", this);
  connect(solveButton, &QPushButton::clicked, this,
          &ChooseModeDialog::solveButtonClicked);
  horizontalLayout->addWidget(solveButton);

  editButton = new QPushButton("Create", this);
  connect(editButton, &QPushButton::clicked, this,
          &ChooseModeDialog::editButtonClicked);
  horizontalLayout->addWidget(editButton);

  verticalLayout->addSpacerItem(
      new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));

  verticalLayout->addLayout(horizontalLayout);

  // Center the dialog relative to the main window
  QRect mainWindowGeometry = parentWidget()->geometry();
  QPoint centerPosition = mainWindowGeometry.center();
  move(centerPosition - QPoint(width() / 2, height() / 2));
}

void ChooseModeDialog::solveButtonClicked() {
  accept();
  emit modeSelected(MODE_SOLVE);
}
void ChooseModeDialog::editButtonClicked() {
  accept();
  emit modeSelected(MODE_EDIT);
}

void ChooseModeDialog::show() { exec(); }