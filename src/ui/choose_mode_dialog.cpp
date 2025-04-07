#include "choose_mode_dialog.h"

#include <QLabel>

ChooseModeDialog::ChooseModeDialog(QWidget *parent) : QMessageBox(parent) {
  setWindowTitle("Choose Mode");

  setInformativeText(
      "To solve a nonogram, choose 'Solve'. To create or edit one, choose "
      "'Create'.");
  solveButton = addButton(tr("Solve"), QMessageBox::ActionRole);
  editButton = addButton(tr("Create"), QMessageBox::ActionRole);

  // Set the width of the message box
  findChild<QLabel *>("qt_msgbox_label")->setFixedWidth(300);

  // Center the message box relative to the main window
  QRect mainWindowGeometry = parentWidget()->geometry();
  QPoint centerPosition = mainWindowGeometry.center();
  move(centerPosition - QPoint(width() / 2, height() / 2));
}

void ChooseModeDialog::show() {
  exec();

  if ((QPushButton *)clickedButton() == solveButton) {
    emit modeSelected(MODE_SOLVE);
  } else if ((QPushButton *)clickedButton() == editButton) {
    emit modeSelected(MODE_EDIT);
  }
}