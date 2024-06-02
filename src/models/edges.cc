#include "edges.h"

using namespace s21;

void Edges::append_edge(Edge edge) { array_edges.push_back(edge); }

void Edges::save_all_edges(std::ofstream& fout) {
  for (const auto& edge : array_edges) {
    fout << "l " << edge.first << " " << edge.second << "\n";
  }
}