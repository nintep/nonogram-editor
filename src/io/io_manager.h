#pragma once

#include <QFile>
#include <QString>
#include <QTextStream>
#include <string>
#include <vector>

#include "../core/nonogram.h"

class IOManager {
 public:
  static bool saveNonogramTofile(const QString &filename, Nonogram *nonogram);
  static bool loadNonogramFromFile(const QString &filename, Nonogram *nonogram);
};