#include "faces.h"

using namespace s21;

void Faces::append_face(Face face_) { array_faces.push_back(face_); }

void Faces::save_all_faces(std::ofstream& fout) {
  for (const auto& face : array_faces) {
    save_face(face, fout);
  }
}

void Faces::save_face(const Face& face, std::ofstream& fout) {
  for (const auto& point : face) {
    fout << point << " ";
  }
  fout << "\n";
}