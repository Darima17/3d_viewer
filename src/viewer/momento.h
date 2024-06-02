#ifndef CPP4_3DVIEWER_V2_0_SRC_VIEW_MOMENTO_H
#define CPP4_3DVIEWER_V2_0_SRC_VIEW_MOMENTO_H

#include <QColor>
#include <iostream>

namespace s21 {
/**
 * @brief Класс MomentoSettings - это класс, который используется для хранения
 * настроек приложения 3D Viewer.
 *
 * Эти настройки включают в себя цвета фона,
 * вершин и ребер, тип вершин и ребер, тип линий и размер линий, ... .
 */

class MomentoSettings {
 public:
  /**
   * @brief Конструктор по умолчанию.
   */
  MomentoSettings();
  /**
   * @brief Деструктор.
   */
  ~MomentoSettings() = default;
  /**
   * @param backgrColor Цвет фона в формате QColor.
   * @param vertex_color Цвет вершин в формате QColor.
   * @param edge_color Цвет ребер в формате QColor.
   * @param vertex_size Размер вершин.
   * @param edge_size Размер ребер.
   * @param vertex_type Тип вершин.
   * @param edge_type Тип ребер.
   * @param projection Тип проекции.
   * @param src_path Путь к исходному файлу.
   * @param prevTranslateX Предыдущее смещение по оси X.
   * @param prevTranslateY Предыдущее смещение по оси Y.
   * @param prevTranslateZ Предыдущее смещение по оси Z.
   * @param prevRotateX Предыдущее вращение по оси X.
   * @param prevRotateY Предыдущее вращение по оси Y.
   * @param prevRotateZ Предыдущее вращение по оси Z.
   * @param prevScale Предыдущее масштабирование.
   * @param num_of_v Количество вершин.
   * @param num_of_f Количество граней.
   * @param file_name Название исходного файла.
   * @param file_path Путь к исходному файлу.
   * @param info_box Информационная строка.
   */
  QColor backgrColor;    ///< Цвет фона
  QColor vertex_color;   ///< Цвет вершин
  QColor edge_color;     ///< Цвет ребер
  float vertex_size;     ///< Размер вершин
  float edge_size;       ///< Размер ребер
  int vertex_type;       ///< Тип вершин
  int edge_type;         ///< Тип ребер
  int projection;        ///< Тип проекции
  std::string src_path;  ///< Путь к исходному файлу
  double prevTranslateX;  ///< Предыдущее смещение по оси X
  double prevTranslateY;  ///< Предыдущее смещение по оси Y
  double prevTranslateZ;  ///< Предыдущее смещение по оси Z
  double prevRotateX;  ///< Предыдущее вращение по оси X
  double prevRotateY;  ///< Предыдущее вращение по оси Y
  double prevRotateZ;  ///< Предыдущее вращение по оси Z
  double prevScale;    ///< Предыдущее масштабирование
  int num_of_v;        ///< Количество вершин
  int num_of_f;        ///< Количество граней
  QString file_name;   ///< Название исходного файла
  QString file_path;   ///< Путь к исходному файлу
  QString info_box;    ///< Информационное окно
  /** @brief Получить текущий путь.
   *  @return текущий путь.
   */
  std::string current_path();
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_VIEW_MOMENTO_H
