#ifndef CPP4_3DVIEWER_V_2_0_SRC_MODELS_FIGURE_H
#define CPP4_3DVIEWER_V_2_0_SRC_MODELS_FIGURE_H

#include "edges.h"
#include "faces.h"
#include "point.h"
#include "points.h"
namespace s21 {
class ConcreteFigureBuilder;

/**
 * @brief Класс FigureFacade представляет трехмерную фигуру и предоставляет
 * методы для её конструирования и взаимодействия.
 */
class FigureFacade {
 public:
  using Edge =
      std::pair<int, int>;  // < Тип для представления ребра (индексы точек).
  using Face = std::vector<int>;  // < Тип для представления грани
  // (последовательность индексов точек).

  /**
   * @brief Конструктор по умолчанию для FigureFacade.
   */
  FigureFacade() = default;

  /**
   * @brief Деструктор для FigureFacade.
   */
  ~FigureFacade() = default;

  /**
   * @brief Загрузить трехмерную фигуру из файла.
   * @param filename Имя файла с описанием фигуры.
   * @param builder Экземпляр ConcreteFigureBuilder для пошагового
   * конструирования фигуры.
   */
  void download_figure(const std::string &filename,
                       ConcreteFigureBuilder &builder);

  /**
   * @brief Переместить фигуру в трехмерном пространстве.
   * @param dx Смещение по оси x.
   * @param dy Смещение по оси y.
   * @param dz Смещение по оси z.
   */
  void move(double dx, double dy, double dz);

  /**
   * @brief Масштабировать фигуру в трехмерном пространстве.
   * @param kx Масштабный коэффициент по оси x.
   * @param ky Масштабный коэффициент по оси y.
   * @param kz Масштабный коэффициент по оси z.
   */
  void scale(double kx, double ky, double kz);

  /**
   * @brief Вращать фигуру в трехмерном пространстве.
   * @param angle_x Угол вращения вокруг оси x.
   * @param angle_y Угол вращения вокруг оси y.
   * @param angle_z Угол вращения вокруг оси z.
   */
  void rotate(double angle_x, double angle_y, double angle_z);

  /**
   * @brief Сохранить трехмерную фигуру в файл.
   * @param filename Имя файла для сохранения фигуры.
   */
  void save_figure(const std::string &filename);

  Point center;   // < Центр фигуры.
  Points points;  // < Точки фигуры.
  Edges edges;    // < Ребра фигуры.
  Faces faces;    // < Грани фигуры.

  /**
   * @brief Чтение данных о фигуре из файла и построение её с использованием
   * ConcreteFigureBuilder.
   * @param fin Входной файловый поток.
   * @param builder Экземпляр ConcreteFigureBuilder для пошагового
   * конструирования фигуры.
   */
  void read_figure(std::ifstream &fin, ConcreteFigureBuilder &builder);

  /**
   * @brief Чтение координат вершины из строки файла и создание экземпляра
   * Point.
   * @param point Экземпляр Point для сохранения координат вершины.
   * @param line Строка из файла с координатами вершины.
   */
  void read_vertex(Point &point, const std::string &line);

  /**
   * @brief Чтение данных о грани из строки файла.
   * @param face Последовательность индексов точек, составляющих грань.
   * @param line Строка из файла с данными о грани.
   */
  void read_face(Face &face, const std::string &line);

  /**
   * @brief Преобразование грани в рёбра и добавление их в коллекцию рёбер.
   * @param face Грань для преобразования.
   * @param edges Коллекция рёбер для добавления.
   */
  void face_to_edges(const Face &face, Edges &edges);

  /**
   * @brief Проверка существования ребра в коллекции рёбер.
   * @param edge Ребро для проверки.
   * @return true, если ребро уже существует, false в противном случае.
   */
  bool exist_edge(const Edge &edge);
};

/**
 * @brief Класс ConcreteFigureBuilder предоставляет реализацию интерфейса
 * FigureBuilder для конструирования трехмерной фигуры.
 */
class ConcreteFigureBuilder {
 private:
  FigureFacade figure;  // < Экземпляр класса FigureFacade для пошагового
  // конструирования трехмерной фигуры.

 public:
  /**
   * @brief Построить центр фигуры.
   * @param center Точка, являющаяся центром фигуры.
   */
  void build_center(const Point &center) { figure.center = center; }

  /**
   * @brief Построить точки фигуры.
   * @param points Коллекция точек, составляющих фигуру.
   */
  void build_points(const Points &points) { figure.points = points; }

  /**
   * @brief Построить ребра фигуры.
   * @param edges Коллекция ребер, соединяющих точки фигуры.
   */
  void build_edges(const Edges &edges) { figure.edges = edges; }

  /**
   * @brief Построить грани фигуры.
   * @param faces Коллекция граней, образующих поверхность фигуры.
   */
  void build_faces(const Faces &faces) { figure.faces = faces; }

  /**
   * @brief Построить таблицу точек фигуры, основываясь на ребрах фигуры.
   */
  void build_points_table();

  /**
   * @brief Получить построенную фигуру.
   * @return Экземпляр класса FigureFacade, представляющий трехмерную фигуру.
   */
  FigureFacade get_figure() { return figure; }
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V_2_0_SRC_MODELS_FIGURE_H
