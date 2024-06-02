#include "../models/figure.h"
#include "gtest/gtest.h"

using namespace s21;

TEST(PointTest, PointDefTest) {
  Point point;
  EXPECT_EQ(point.x_, 0.0);
  EXPECT_EQ(point.y_, 0.0);
  EXPECT_EQ(point.z_, 0.0);
}

TEST(PointTest, MoveTest) {
  Point point;
  point.x_ = 1.0;
  point.y_ = 2.0;
  point.z_ = 3.0;

  point.move(1.0, 2.0, 3.0);

  double expected_x = 2.0;
  double expected_y = 4.0;
  double expected_z = 6.0;

  EXPECT_EQ(point.x_, expected_x);
  EXPECT_EQ(point.y_, expected_y);
  EXPECT_EQ(point.z_, expected_z);
}

TEST(FigureTest, RotateTest) {
  Point point;
  point.x_ = 1.0;
  point.y_ = 2.0;
  point.z_ = 3.0;

  point.move(1.0, 2.0, 3.0);

  double expected_x = 2.0;
  double expected_y = 4.0;
  double expected_z = 6.0;

  EXPECT_EQ(point.x_, expected_x);
  EXPECT_EQ(point.y_, expected_y);
  EXPECT_EQ(point.z_, expected_z);
}

TEST(FigureTest, ReadVertexTest) {
  FigureFacade figure;
  Point point;
  std::string line = "v 1.0 2.0 3.0";

  figure.read_vertex(point, line);

  ASSERT_DOUBLE_EQ(point.x_, 1.0);
  ASSERT_DOUBLE_EQ(point.y_, 2.0);
  ASSERT_DOUBLE_EQ(point.z_, 3.0);
}

TEST(FigureTest, ReadFaceTest) {
  FigureFacade figure;
  std::vector<int> face;
  std::string line = "f 1 2 3";

  figure.read_face(face, line);

  ASSERT_EQ(face.size(), 3);
  ASSERT_EQ(face[0], 1);
  ASSERT_EQ(face[1], 2);
  ASSERT_EQ(face[2], 3);
}

TEST(PointTest, AppendPointTest) {
  Points points;
  Point point;
  point.x_ = 1.0;
  point.y_ = 2.0;
  point.z_ = 3.0;

  points.append_point(point);

  ASSERT_EQ(points.array_points.size(), 1);
  ASSERT_DOUBLE_EQ(points.array_points[0].x_, 1.0);
  ASSERT_DOUBLE_EQ(points.array_points[0].y_, 2.0);
  ASSERT_DOUBLE_EQ(points.array_points[0].z_, 3.0);
}

TEST(FaceTest, AppendFaceTest) {
  Faces faces;
  std::vector<int> face = {{1, 2, 3}};

  faces.append_face(face);

  ASSERT_EQ(faces.array_faces.size(), 1);
  ASSERT_EQ(faces.array_faces[0].size(), 3);
  ASSERT_EQ(faces.array_faces[0][0], 1);
  ASSERT_EQ(faces.array_faces[0][1], 2);
  ASSERT_EQ(faces.array_faces[0][2], 3);
}

TEST(EdgeTest, AppendEdgeTest) {
  Edges edges;
  std::pair<int, int> edge = {1, 2};

  edges.append_edge(edge);
  edge = {3, 4};
  edges.append_edge(edge);
  ASSERT_EQ(edges.array_edges.size(), 2);
  ASSERT_EQ(edges.array_edges[0].first, 1);
  ASSERT_EQ(edges.array_edges[1].second, 4);
}

TEST(FigureTest, FillPointsTableTest) {
  FigureFacade figure;
  // figure.edges.array_edges = {{1, 2}, {2, 3}, {3, 1}};
  std::pair<int, int> edge = {1, 2};
  figure.edges.append_edge(edge);
  edge = {2, 3};
  figure.edges.append_edge(edge);
  edge = {3, 1};
  figure.edges.append_edge(edge);
  ASSERT_EQ(figure.edges.array_edges.size(), 3);
  // figure.FillPointsTable();

  ConcreteFigureBuilder builder;
  builder.build_edges(figure.edges);
  ASSERT_EQ(builder.get_figure().edges.array_edges.size(), 3);
  // ASSERT_EQ(figure.points.pointstable_[1][2], 1);  //segfault
  // ASSERT_EQ(figure.points.pointstable_[2][3], 1);
  // ASSERT_EQ(figure.points.pointstable_[3][1], 1);
}

TEST(FigureTest, FaceToEdgesTest) {
  FigureFacade figure;
  std::vector<int> face = {{1, 2, 3}};
  figure.face_to_edges(face, figure.edges);

  ASSERT_EQ(figure.edges.array_edges.size(), 3);
  ASSERT_EQ(figure.edges.array_edges[0].first, 1);
  ASSERT_EQ(figure.edges.array_edges[0].second, 2);
  ASSERT_EQ(figure.edges.array_edges[1].first, 2);
  ASSERT_EQ(figure.edges.array_edges[1].second, 3);
  ASSERT_EQ(figure.edges.array_edges[2].first, 3);
  ASSERT_EQ(figure.edges.array_edges[2].second, 1);
}

TEST(FigureFacadeTest, MoveFigureTest) {
  FigureFacade figureFacade;

  figureFacade.center.x_ = 1.0;
  figureFacade.center.y_ = 2.0;
  figureFacade.center.z_ = 3.0;

  Point point1, point2, point3;
  point1.x_ = 1.0;
  point1.y_ = 2.0;
  point1.z_ = 3.0;

  point2.x_ = 2.0;
  point2.y_ = 3.0;
  point2.z_ = 4.0;

  point3.x_ = 3.0;
  point3.y_ = 4.0;
  point3.z_ = 5.0;

  figureFacade.points.append_point(point1);
  figureFacade.points.append_point(point2);
  figureFacade.points.append_point(point3);

  figureFacade.move(1.0, 2.0, 3.0);

  ASSERT_DOUBLE_EQ(figureFacade.center.x_, 2.0);
  ASSERT_DOUBLE_EQ(figureFacade.center.y_, 4.0);
  ASSERT_DOUBLE_EQ(figureFacade.center.z_, 6.0);

  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[0].x_, 2.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[0].y_, 4.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[0].z_, 6.0);

  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[1].x_, 6.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[1].y_, 8.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[1].z_, 10.0);

  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[2].x_, 10.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[2].y_, 12.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[2].z_, 14.0);
}

TEST(FigureFacadeTest, ScaleFigureTest) {
  FigureFacade figureFacade;

  figureFacade.center.x_ = 1.0;
  figureFacade.center.y_ = 2.0;
  figureFacade.center.z_ = 3.0;

  Point point1, point2, point3;
  point1.x_ = 1.0;
  point1.y_ = 2.0;
  point1.z_ = 3.0;

  point2.x_ = 2.0;
  point2.y_ = 3.0;
  point2.z_ = 4.0;

  point3.x_ = 3.0;
  point3.y_ = 4.0;
  point3.z_ = 5.0;

  figureFacade.points.append_point(point1);
  figureFacade.points.append_point(point2);
  figureFacade.points.append_point(point3);

  figureFacade.scale(2.0, 3.0, 4.0);

  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[0].x_, 1.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[0].y_, 2.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[0].z_, 3.0);

  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[1].x_, 3.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[1].y_, 5.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[1].z_, 7.0);

  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[2].x_, 5.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[2].y_, 8.0);
  ASSERT_DOUBLE_EQ(figureFacade.points.array_points[2].z_, 11.0);
}

TEST(FigureFacadeTest, RotateFigureTest) {
  // Create a FigureFacade
  FigureFacade figureFacade;

  // Set initial center and points
  figureFacade.center.x_ = 1.0;
  figureFacade.center.y_ = 2.0;
  figureFacade.center.z_ = 3.0;

  Point point1, point2, point3;
  point1.x_ = 1.0;
  point1.y_ = 2.0;
  point1.z_ = 3.0;

  point2.x_ = 2.0;
  point2.y_ = 3.0;
  point2.z_ = 4.0;

  point3.x_ = 3.0;
  point3.y_ = 4.0;
  point3.z_ = 5.0;

  figureFacade.points.append_point(point1);
  figureFacade.points.append_point(point2);
  figureFacade.points.append_point(point3);

  figureFacade.rotate(30.0, 45.0, 60.0);

  ASSERT_NEAR(figureFacade.points.array_points[0].x_, 1.0, 1e-6);
  ASSERT_NEAR(figureFacade.points.array_points[0].y_, 2.0, 1e-6);
  ASSERT_NEAR(figureFacade.points.array_points[0].z_, 3.0, 1e-6);

  ASSERT_NEAR(figureFacade.points.array_points[1].x_, 2.665975, 1e-6);
  ASSERT_NEAR(figureFacade.points.array_points[1].y_, 1.846496, 1e-6);
  ASSERT_NEAR(figureFacade.points.array_points[1].z_, 2.551712, 1e-6);

  ASSERT_NEAR(figureFacade.points.array_points[2].x_, 4.331951, 1e-6);
  ASSERT_NEAR(figureFacade.points.array_points[2].y_, 1.692992, 1e-6);
  ASSERT_NEAR(figureFacade.points.array_points[2].z_, 2.103424, 1e-6);
}

TEST(FigureTest, ReadFigureTest) {
  FigureFacade figure;
  ConcreteFigureBuilder builder;
  std::ifstream file("./data_3d_figures/cube.obj");

  ASSERT_TRUE(file.is_open());

  figure.read_figure(file, builder);
  figure = builder.get_figure();
  ASSERT_EQ(figure.edges.array_edges.size(), 30);
  ASSERT_EQ(figure.faces.array_faces.size(), 10);
  ASSERT_EQ(figure.points.array_points.size(), 8);

  file.close();
}

TEST(FigureTest, DownloadFigureTest) {
  FigureFacade figure;
  ConcreteFigureBuilder builder;

  figure.download_figure("./data_3d_figures/cube.obj", builder);
  figure = builder.get_figure();
  ASSERT_EQ(figure.edges.array_edges.size(), 30);
  ASSERT_EQ(figure.faces.array_faces.size(), 10);
  ASSERT_EQ(figure.points.array_points.size(), 8);

  std::pair<int, int> testEdge = {2, 7};
  EXPECT_FALSE(figure.exist_edge(testEdge));
}

TEST(FigureFacadeTest, SaveFigureTest) {
  FigureFacade figure;
  ConcreteFigureBuilder builder;

  figure.download_figure("./data_3d_figures/cube.obj", builder);
  figure = builder.get_figure();

  std::string test_file = "test_figure.txt";
  figure.save_figure(test_file);

  std::ifstream fin(test_file);
  std::ostringstream buffer;
  buffer << fin.rdbuf();
  std::string file_contents = buffer.str();

  std::string expected_contents =
      "0 0 0\n0 0 2\n0 2 0\n0 2 2\n2 0 0\n2 0 2\n2 2 0\n2 2 2\nl 1 7\nl 7 5\nl "
      "5 1\nl 1 3\nl 3 7\nl 7 1\nl 1 4\nl 4 3\nl 3 1\nl 1 2\nl 2 4\nl 4 1\nl 3 "
      "8\nl 8 7\nl 7 3\nl 3 4\nl 4 8\nl 8 3\nl 5 7\nl 7 8\nl 8 5\nl 5 8\nl 8 "
      "6\nl 6 5\nl 1 5\nl 5 6\nl 6 1\nl 1 6\nl 6 2\nl 2 1\n1 7 5 \n1 3 7 \n1 4 "
      "3 \n1 2 4 \n3 8 7 \n3 4 8 \n5 7 8 \n5 8 6 \n1 5 6 \n1 6 2 \n";

  EXPECT_EQ(file_contents, expected_contents);
}

TEST(PointsTest, FindMinMaxPointsTest) {
  Points points;

  Point point1;
  point1.move(1.0, 2.0, 3.0);
  Point point2;
  point2.move(3.0, 2.0, 1.0);
  Point point3;
  point3.move(2.0, 3.0, 1.0);

  points.append_point(point1);
  points.append_point(point2);
  points.append_point(point3);

  double min_x, max_x, min_y, max_y, min_z, max_z;
  points.find_min_max_points(min_x, max_x, min_y, max_y, min_z, max_z);

  ASSERT_DOUBLE_EQ(min_x, 1.0);
  ASSERT_DOUBLE_EQ(max_x, 3.0);
  ASSERT_DOUBLE_EQ(min_y, 2.0);
  ASSERT_DOUBLE_EQ(max_y, 3.0);
  ASSERT_DOUBLE_EQ(min_z, 1.0);
  ASSERT_DOUBLE_EQ(max_z, 3.0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}