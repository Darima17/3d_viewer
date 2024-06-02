#include "points.h"

using namespace s21;

void Points::move(double dx, double dy, double dz) {
  for (auto& point : array_points) {
    point.move(dx, dy, dz);
  }
}

void Points::rotate(const Point& r_center, double angle_x, double angle_y,
                    double angle_z) {
  for (auto& point : array_points) {
    point.rotate(r_center, angle_x, angle_y, angle_z);
  }
}

void Points::scale(const Point& s_center, double kx, double ky, double kz) {
  for (auto& point : array_points) {
    point.scale(s_center, kx, ky, kz);
  }
}

void Points::save_all_points(std::ofstream& fout) {
  for (const auto& point : array_points) {
    fout << point.x_ << " " << point.y_ << " " << point.z_ << "\n";
  }
}

void Points::append_point(Point point) { array_points.push_back(point); }

void Points::find_min_max_points(double& min_x, double& max_x, double& min_y,
                                 double& max_y, double& min_z, double& max_z) {
  if (array_points.empty()) return;

  min_x = max_x = array_points[0].x_;
  min_y = max_y = array_points[0].y_;
  min_z = max_z = array_points[0].z_;

  for (const auto& point : array_points) {
    min_x = std::min(min_x, point.x_);
    max_x = std::max(max_x, point.x_);

    min_y = std::min(min_y, point.y_);
    max_y = std::max(max_y, point.y_);

    min_z = std::min(min_z, point.z_);
    max_z = std::max(max_z, point.z_);
  }
}