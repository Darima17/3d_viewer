#ifndef CPP4_3DVIEWER_V_2_0_SRC_MODELS_POINTS_H
#define CPP4_3DVIEWER_V_2_0_SRC_MODELS_POINTS_H

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>

#include "point.h"

/**
 * @brief Класс Points представляет собой коллекцию трехмерных точек с
 * возможностью перемещения, вращения и масштабирования.
 */
namespace s21 {
class Points {
 public:
  /**
   * @brief Конструктор по умолчанию для Points.
   */
  Points() = default;

  /**
   * @brief Деструктор для Points.
   */
  ~Points() = default;

  /**
   * @brief Переместить все точки в трехмерном пространстве на указанные
   * смещения.
   * @param dx Смещение по оси x.
   * @param dy Смещение по оси y.
   * @param dz Смещение по оси z.
   */
  void move(double dx, double dy, double dz);

  /**
   * @brief Вращать все точки вокруг указанного центра в трехмерном
   * пространстве.
   * @param r_center Центр вращения.
   * @param angle_x Угол вращения вокруг оси x.
   * @param angle_y Угол вращения вокруг оси y.
   * @param angle_z Угол вращения вокруг оси z.
   */
  void rotate(const Point &r_center, double angle_x, double angle_y,
              double angle_z);

  /**
   * @brief Масштабировать все точки относительно указанного центра в трехмерном
   * пространстве.
   * @param s_center Центр масштабирования.
   * @param kx Масштабный коэффициент по оси x.
   * @param ky Масштабный коэффициент по оси y.
   * @param kz Масштабный коэффициент по оси z.
   */
  void scale(const Point &s_center, double kx, double ky, double kz);

  /**
   * @brief Сохранить координаты всех точек в выходной файловый поток.
   * @param fout Выходной файловый поток для сохранения координат всех точек.
   */
  void save_all_points(std::ofstream &fout);

  /**
   * @brief Добавить точку в коллекцию точек.
   * @param point Точка для добавления.
   */
  void append_point(Point point);

  /**
   * @brief Найти минимальные и максимальные координаты точек по осям x, y, z.
   * @param min_x Минимальная координата по оси x.
   * @param max_x Максимальная координата по оси x.
   * @param min_y Минимальная координата по оси y.
   * @param max_y Максимальная координата по оси y.
   * @param min_z Минимальная координата по оси z.
   * @param max_z Максимальная координата по оси z.
   */
  void find_min_max_points(double &min_x, double &max_x, double &min_y,
                           double &max_y, double &min_z, double &max_z);

  // Метод для получения всех точек
  std::vector<Point> get_points() const { return array_points; }

  std::vector<std::vector<int>>
      points_table;  // < Таблица точек (не используется).
  std::vector<Point> array_points;  // < Массив трехмерных точек.
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V_2_0_SRC_MODELS_POINTS_H
