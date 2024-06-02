#include "momento.h"

#include <QCoreApplication>
#include <QDebug>
#include <QDir>

namespace s21 {
MomentoSettings::MomentoSettings() {
  //настройки по умолчвнию
  vertex_color.setGreenF(1.0f);
  edge_color.setGreenF(0.5f);
  vertex_size = edge_size = 3;
  vertex_type = 0;  //отсутствует, круг, квадрат
  edge_type = 0;    //сплошная, пунктирная
  projection = 0;  //проекция параллельная 0 и центральная 1
  info_box = "";
  src_path = current_path();
  prevScale = 1.0f;
}

std::string MomentoSettings::current_path() {
  std::string str = QCoreApplication::applicationDirPath().toStdString();
  std::size_t found = str.find("/src/");
  std::string result = str.substr(0, found + 5);
  return result;
}
}  // namespace s21
