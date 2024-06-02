#ifndef CPP4_3DVIEWER_V_2_0_SRC_MODELS_POINT_H
#define CPP4_3DVIEWER_V_2_0_SRC_MODELS_POINT_H

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>

/**
 * @brief Класс Point представляет трехмерную точку с возможностью перемещения,
 * вращения и масштабирования.
 *
 */
namespace s21 {
class Point {
 public:
  /**
   * @brief Конструктор по умолчанию для Point.
   */
  Point() : x_(0.0), y_(0.0), z_(0.0){};

  /**
   * @brief Переместить точку в трехмерном пространстве на указанные смещения.
   * @param dx Смещение по оси x.
   * @param dy Смещение по оси y.
   * @param dz Смещение по оси z.
   */
  void move(double dx, double dy, double dz);

  /**
   * @brief Вращать точку вокруг указанного центра в трехмерном пространстве.
   * @param r_center Центр вращения.
   * @param angle_x Угол вращения вокруг оси x.
   * @param angle_y Угол вращения вокруг оси y.
   * @param angle_z Угол вращения вокруг оси z.
   */
  void rotate(const Point &r_center, double angle_x, double angle_y,
              double angle_z);

  /**
   * @brief Масштабировать точку относительно указанного центра в трехмерном
   * пространстве.
   * @param s_center Центр масштабирования.
   * @param kx Масштабный коэффициент по оси x.
   * @param ky Масштабный коэффициент по оси y.
   * @param kz Масштабный коэффициент по оси z.
   */
  void scale(const Point &s_center, double kx, double ky, double kz);

  /**
   * @brief Сохранить координаты точки в выходной файловый поток.
   * @param fout Выходной файловый поток для сохранения координат точки.
   * @return True, если сохранение успешно, false в противном случае.
   */
  bool save_point(std::ofstream &fout) const;

  double x_;  // < X-координата точки.
  double y_;  // < Y-координата точки.
  double z_;  // < Z-координата точки.

 private:
  /**
   * @brief Преобразовать угол из градусов в радианы.
   * @param angle Угол в градусах.
   * @return Угол в радианах.
   */
  static double to_radians(const double angle);

  /**
   * @brief Вращать точку вокруг оси x.
   * @param r_center Центр вращения.
   * @param angle Угол вращения вокруг оси x.
   */
  void rotate_x(const Point &r_center, const double angle);

  /**
   * @brief Вращать точку вокруг оси y.
   * @param r_center Центр вращения.
   * @param angle Угол вращения вокруг оси y.
   */
  void rotate_y(const Point &r_center, const double angle);

  /**
   * @brief Вращать точку вокруг оси z.
   * @param r_center Центр вращения.
   * @param angle Угол вращения вокруг оси z.
   */
  void rotate_z(const Point &r_center, const double angle);
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V_2_0_SRC_MODELS_POINT_H