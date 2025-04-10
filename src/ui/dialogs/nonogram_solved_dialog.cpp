#include "nonogram_solved_dialog.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

NonogramSolvedDialog::NonogramSolvedDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle("Nice work");

  QVBoxLayout *verticalLayout = new QVBoxLayout(this);

  QLabel *description = new QLabel("The nonogram is solved correctly!", this);
  verticalLayout->addWidget(description);

  acceptButton = new QPushButton("Ok", this);
  connect(acceptButton, &QPushButton::clicked, this,
          &NonogramSolvedDialog::acceptButtonClicked);
  verticalLayout->addSpacerItem(
      new QSpacerItem(0, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
  verticalLayout->addWidget(acceptButton);

  // Center the dialog relative to the main window
  QRect mainWindowGeometry = parentWidget()->geometry();
  QPoint centerPosition = mainWindowGeometry.center();
  move(centerPosition - QPoint(width() / 2, height() / 2));
}

void NonogramSolvedDialog::acceptButtonClicked() {
  acceptSelected();
  accept();
}

void NonogramSolvedDialog::show() { exec(); }