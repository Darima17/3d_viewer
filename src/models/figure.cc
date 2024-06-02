#include "figure.h"

using namespace s21;

void FigureFacade::download_figure(const std::string& filename,
                                   ConcreteFigureBuilder& builder) {
  std::ifstream fin(filename);
  if (fin.is_open()) {
    read_figure(fin, builder);
    fin.close();
  }
}

void FigureFacade::move(double dx, double dy, double dz) {
  center.move(dx, dy, dz);
  points.move(dx, dy, dz);
  double value = (dz > 0.0) ? (dz + 1) : (-1 / (dz - 1));
  scale(value, value, value);
}

void FigureFacade::scale(double kx, double ky, double kz) {
  points.scale(center, kx, ky, kz);
}

void FigureFacade::rotate(double angle_x, double angle_y, double angle_z) {
  points.rotate(center, angle_x, angle_y, angle_z);
}

void FigureFacade::save_figure(const std::string& filename) {
  std::ofstream fout(filename);
  if (fout.is_open()) {
    points.save_all_points(fout);
    edges.save_all_edges(fout);
    faces.save_all_faces(fout);
    fout.close();
  }
}

void FigureFacade::read_figure(std::ifstream& fin,
                               ConcreteFigureBuilder& builder) {
  std::string line;

  Edges* edges = new Edges();

  Points* points = new Points();

  Faces* faces = new Faces();

  while (std::getline(fin, line)) {
    if (line.substr(0, 2) == "v ") {
      Point vertex;
      read_vertex(vertex, line);
      points->append_point(vertex);
    } else if (line.substr(0, 2) == "f ") {
      Face face;
      read_face(face, line);
      faces->append_face(face);
    }
  }
  builder.build_faces(*faces);
  builder.build_points(*points);
  builder.build_points_table();

  for (size_t i = 0; i < faces->array_faces.size(); ++i) {
    face_to_edges(faces->array_faces[i], *edges);
  }
  builder.build_edges(*edges);
}

void FigureFacade::read_vertex(Point& point, const std::string& line) {
  std::istringstream iss(line);
  std::string v;
  iss >> v >> point.x_ >> point.y_ >> point.z_;
}

void FigureFacade::read_face(Face& face, const std::string& line) {
  std::istringstream iss(line);
  std::string token;
  int num_tokens = 0;
  while (iss >> token) {
    if (num_tokens > 0) {
      int point_index;
      std::istringstream(token) >> point_index;
      face.push_back(point_index);
    }
    num_tokens++;
  }
}

void FigureFacade::face_to_edges(const Face& face, Edges& edges) {
  for (size_t i = 0; i < face.size(); ++i) {
    Edge edge;
    edge.first = face[i];
    edge.second = face[(i + 1) % face.size()];
    if (!exist_edge(edge)) {
      edges.append_edge(edge);
    }
  }
}

bool FigureFacade::exist_edge(const Edge& edge) {
  if (static_cast<size_t>(edge.first) < points.points_table.size() &&
      static_cast<size_t>(edge.second) <
          points.points_table[edge.first].size()) {
    return points.points_table[edge.first][edge.second] == 1;
  } else {
    return false;
  }
}

void ConcreteFigureBuilder::build_points_table() {
  for (size_t i = 0; i < figure.edges.array_edges.size(); ++i) {
    if (static_cast<size_t>(figure.edges.array_edges[i].first) <
            figure.points.points_table.size() &&
        static_cast<size_t>(figure.edges.array_edges[i].second) <
            figure.points.points_table[figure.edges.array_edges[i].first]
                .size()) {
      figure.points.points_table[figure.edges.array_edges[i].first]
                                [figure.edges.array_edges[i].second] = 1;
      figure.points.points_table[figure.edges.array_edges[i].second]
                                [figure.edges.array_edges[i].first] = 1;
    } else {
      return;
    }
  }
}