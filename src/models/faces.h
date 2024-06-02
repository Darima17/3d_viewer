#ifndef CPP4_3DVIEWER_V_2_0_SRC_MODELS_FACES_H
#define CPP4_3DVIEWER_V_2_0_SRC_MODELS_FACES_H

#include "points.h"

/**
 * @brief Класс Faces представляет собой коллекцию граней, составленных из
 * индексов точек в трехмерном пространстве.
 */
namespace s21 {
class Faces {
 public:
  using Face =
      std::vector<int>;  // < Тип для представления грани (индексы точек).

  /**
   * @brief Конструктор по умолчанию для Faces.
   */
  Faces() = default;

  /**
   * @brief Деструктор для Faces.
   */
  ~Faces() = default;

  /**
   * @brief Добавить грань в коллекцию.
   * @param face_ Грань для добавления (последовательность индексов точек).
   */
  void append_face(Face face_);

  /**
   * @brief Сохранить все грани в выходной файловый поток.
   * @param fout Выходной файловый поток для сохранения граней.
   */
  void save_all_faces(std::ofstream &fout);

  std::vector<Face> array_faces;  // < Массив граней.

  // Метод для получения всех граней
  std::vector<Face> get_faces() const { return array_faces; }

 private:
  Face face_;  // < Вспомогательное поле для сохранения текущей грани.

  /**
   * @brief Сохранить одну грань в выходной файловый поток.
   * @param face_ Грань для сохранения.
   * @param fout Выходной файловый поток.
   */
  void save_face(const Face &face_, std::ofstream &fout);
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V_2_0_SRC_MODELS_FACES_H