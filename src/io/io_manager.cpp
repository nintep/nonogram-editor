#include "io_manager.h"

bool IOManager::saveNonogramTofile(const QString &filename,
                                   Nonogram *nonogram) {
  QFile file(filename);

  try {
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
      return false;
    }

    QTextStream out(&file);
    out << "#nonogram_editor\n";
    out << "#version_1.0\n";

    out << nonogram->getWidth() << " " << nonogram->getHeight() << "\n";

    for (int i = 0; i < nonogram->getHeight(); ++i) {
      for (int j = 0; j < nonogram->getWidth(); ++j) {
        out << (nonogram->getCell(j, i) ? "1" : "0") << " ";
      }
      out << "\n";
    }

    file.close();
    return true;

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return false;
  }
}

bool IOManager::loadNonogramFromFile(const QString &filename,
                                     Nonogram *nonogram) {
  QFile file(filename);

  try {
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
      return false;
    }

    QTextStream in(&file);
    QString header;
    in >> header;

    if (header != "#nonogram_editor") {
      return false;
    }

    QString version;
    in >> version;

    if (version != "#version_1.0") {
      return false;
    }

    int width, height;
    in >> width >> height;

    std::vector<std::vector<bool>> nonogramData(
        height, std::vector<bool>(width, false));

    for (int i = 0; i < height; ++i) {
      for (int j = 0; j < width; ++j) {
        int cellValue;
        in >> cellValue;
        nonogramData[i][j] = (cellValue == 1);
      }
    }

    nonogram->setData(nonogramData);

    file.close();
    return true;

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return false;
  }
}