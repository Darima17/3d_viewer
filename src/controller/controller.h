#ifndef CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
#define CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_

#include <cstdint>
#include <string>
#include <vector>

#include "../models/figure.h"
#include "../viewer/momento.h"

namespace s21 {

class Controller {
 public:
  static Controller &GetInstance() {
    static Controller instance;
    return instance;
  }
  Controller() = default;
  ~Controller() = default;
  Controller(const Controller &) = delete;
  Controller &operator=(const Controller &) = delete;

  double min_x, max_x, min_y, max_y, min_z, max_z, maxXYZ;
  // Установка модели
  void SetModel(std::string path) {
    ConcreteFigureBuilder builder;
    const char *p = path.c_str();
    model_.download_figure(p, builder);
    model_ = builder.get_figure();
    model_.points.find_min_max_points(min_x, max_x, min_y, max_y, min_z, max_z);
    double maxX = std::max(std::abs(max_x), std::abs(min_x));
    double maxY = std::max(std::abs(max_y), std::abs(min_y));
    double maxZ = std::max(std::abs(max_z), std::abs(min_z));
    maxXYZ = std::max(maxX, std::max(maxY, maxZ));
  }

  int get_num_v() { return GetVertices().size() / 3; }

  int get_num_f() { return GetFaces().size() / 3; }

  // Получить все вершины
  std::vector<double> GetVertices() {
    std::vector<Point> vertices = model_.points.get_points();
    std::vector<double> res;
    for (const auto &vertex : vertices) {
      res.push_back(vertex.x_);
      res.push_back(vertex.y_);
      res.push_back(vertex.z_);
    }
    return res;
  }

  // Получить все грани
  std::vector<unsigned int> GetFaces() {
    std::vector<FigureFacade::Face> faces = model_.faces.get_faces();
    std::vector<unsigned int> res;
    for (const auto &face : faces) {
      res.push_back((unsigned int)face[0]);
      res.push_back((unsigned int)face[1]);
      res.push_back((unsigned int)face[2]);
    }
    return res;
  }

  void Set_scale(double scale_k) { model_.scale(scale_k, scale_k, scale_k); }

  void Set_move(double dx, double dy, double dz) {
    double x = (std::abs(max_x), std::abs(min_x)) * dx;
    double y = (std::abs(max_y), std::abs(min_y)) * dy;
    double z = (std::abs(max_z), std::abs(min_z)) * dz;
    model_.move(x, y, z);
  }

  void Set_rotate(double angle_x, double angle_y, double angle_z) {
    model_.rotate(angle_x, angle_y, angle_z);
  }

  FigureFacade getModel() { return model_; }

 private:
  FigureFacade model_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_CONTROLLER_CONTROLLER_H_
