#include "point.h"

using namespace s21;

double Point::to_radians(const double angle) { return angle * (M_PI / 180); }

void Point::rotate_x(const Point& r_center, const double angle) {
  double r_cos = std::cos(to_radians(angle));
  double r_sin = std::sin(to_radians(angle));
  double y = y_;

  y_ = (y_ - r_center.y_) * r_cos + (z_ - r_center.z_) * r_sin + r_center.y_;
  z_ = -(y - r_center.y_) * r_sin + (z_ - r_center.z_) * r_cos + r_center.z_;
}

void Point::rotate_y(const Point& r_center, const double angle) {
  double r_cos = std::cos(to_radians(angle));
  double r_sin = std::sin(to_radians(angle));
  double x = x_;

  x_ = (x_ - r_center.x_) * r_cos + (z_ - r_center.z_) * r_sin + r_center.x_;
  z_ = -(x - r_center.x_) * r_sin + (z_ - r_center.z_) * r_cos + r_center.z_;
}

void Point::rotate_z(const Point& r_center, const double angle) {
  double r_cos = std::cos(to_radians(angle));
  double r_sin = std::sin(to_radians(angle));
  double x = x_;

  x_ = (x_ - r_center.x_) * r_cos + (y_ - r_center.y_) * r_sin + r_center.x_;
  y_ = -(x - r_center.x_) * r_sin + (y_ - r_center.y_) * r_cos + r_center.y_;
}

void Point::move(double dx, double dy, double dz) {
  x_ += dx;
  y_ += dy;
  z_ += dz;
}

void Point::rotate(const Point& r_center, double angle_x, double angle_y,
                   double angle_z) {
  rotate_x(r_center, angle_x);
  rotate_y(r_center, angle_y);
  rotate_z(r_center, angle_z);
}

void Point::scale(const Point& s_center, double kx, double ky, double kz) {
  x_ = (x_ - s_center.x_) * kx + s_center.x_;
  y_ = (y_ - s_center.y_) * ky + s_center.y_;
  z_ = (z_ - s_center.z_) * kz + s_center.z_;
}

bool Point::save_point(std::ofstream& fout) const {
  if (!fout) return false;
  fout << "v " << x_ << " " << -y_ << " " << z_ << "\n";
  return true;
}
