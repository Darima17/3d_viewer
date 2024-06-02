#ifndef CPP4_3DVIEWER_V_2_0_SRC_MODELS_EDGES_H
#define CPP4_3DVIEWER_V_2_0_SRC_MODELS_EDGES_H

#include <fstream>
#include <iostream>
#include <vector>

/**
 * @brief Класс Edges представляет коллекцию ребер, соединяющих точки в
 * трехмерном пространстве.
 */
namespace s21 {
class Edges {
 public:
  using Edge =
      std::pair<int, int>;  // < Тип для представления ребра (индексы точек).

  /**
   * @brief Конструктор по умолчанию для Edges.
   */
  Edges() = default;

  /**
   * @brief Деструктор для Edges.
   */
  ~Edges() = default;

  /**
   * @brief Добавить ребро в коллекцию.
   * @param edge Ребро для добавления (пара индексов точек).
   */
  void append_edge(Edge edge);

  /**
   * @brief Сохранить все ребра в выходной файловый поток.
   * @param fout Выходной файловый поток для сохранения ребер.
   */
  void save_all_edges(std::ofstream &fout);

  std::vector<Edge> get_edges() const { return array_edges; }

  std::vector<Edge> array_edges;  // < Массив ребер.
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V_2_0_SRC_MODELS_EDGES_H
