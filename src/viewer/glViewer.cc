#include "glViewer.h"

namespace s21 {

glViewer::glViewer(QWidget* parent)
    : QOpenGLWidget(parent), gif_(nullptr), timer_(new QTimer) {}

void glViewer::initializeGL() {
  initializeOpenGLFunctions();
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void glViewer::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void glViewer::paintGL() {
  if (Settings == nullptr) {
    return;
  }

  // Set background color
  auto& bgColor = Settings->backgrColor;
  glClearColor(bgColor.redF(), bgColor.greenF(), bgColor.blueF(),
               bgColor.alphaF());

  // Clear color and depth buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Set projection matrix
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set camera position
  double maxXYZ = 0.00001 + controller_.maxXYZ;
  if (!Settings->projection) {
    glOrtho(-maxXYZ * 1.1, maxXYZ * 1.1, -maxXYZ * 1.1, maxXYZ * 1.1,
            -maxXYZ * 1.1,
            maxXYZ * 5);  // Orthographic projection
  } else {
    double f = 60.0 * M_PI / 180;
    double H = maxXYZ / (2 * tan(f / 2));
    glFrustum(-maxXYZ, maxXYZ, -maxXYZ, maxXYZ, H,
              maxXYZ * 20);  // Perspective projection
    glTranslatef(0, 0, -H * 3);
  }

  std::vector<double> vertices = controller_.GetVertices();
  if (!vertices.empty()) {
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, vertices.data());
    edge();
    vertex();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
}

void glViewer::edge() {
  glLineWidth(Settings->edge_size);
  glColor3f(Settings->edge_color.redF(), Settings->edge_color.greenF(),
            Settings->edge_color.blueF());
  auto edgeType = Settings->edge_type;

  if (edgeType) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x1010);  // Line stipple
  } else {
    glDisable(GL_LINE_STIPPLE);
  }

  // Отрисовка ребер (линий)
  glBegin(GL_LINES);
  FigureFacade model = controller_.getModel();
  for (size_t i = 0; i < model.edges.array_edges.size(); i++) {
    int v1 = model.edges.array_edges[i].first - 1;
    int v2 = model.edges.array_edges[i].second - 1;
    glVertex3f(model.points.array_points[v1].x_,
               model.points.array_points[v1].y_,
               model.points.array_points[v1].z_);
    glVertex3f(model.points.array_points[v2].x_,
               model.points.array_points[v2].y_,
               model.points.array_points[v2].z_);
  }
  glEnd();
}

void glViewer::vertex() {
  if (Settings->num_of_v == 0) {
    return;
  }
  auto& vertexColor = Settings->vertex_color;
  glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
  glPointSize(Settings->vertex_size);
  auto vertexType = Settings->vertex_type;
  if (vertexType != 2) {
    if (vertexType) {
      glDisable(GL_POINT_SMOOTH);  // Disable point smoothing
    } else {
      glEnable(GL_POINT_SMOOTH);  // Enable point smoothing
    }
    glDrawArrays(GL_POINTS, 0, Settings->num_of_v);
  }
  glEnd();
}

void glViewer::setSettings(MomentoSettings* newSettings) {
  Settings = newSettings;
}

void glViewer::screenshot() {
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glReadBuffer(GL_FRONT);
  std::vector<uint8_t> pixels(width() * height() * 3);
  QRect rect = geometry();
  const int barHeight = 27;
  glReadPixels(rect.x(), rect.y() + barHeight, rect.width(),
               rect.height() - barHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE,
               pixels.data());
  QImage image(pixels.data(), rect.width(), rect.height() - barHeight,
               rect.width() * 3, QImage::Format_RGB888);
  QString filePath = QFileDialog::getSaveFileName(
      this, "Save Screenshot", "screen.png", "PNG Image (*.png)");
  // Сохранение изображения в файл
  QImageWriter writer(filePath);
  writer.write(std::move(image).mirrored().rgbSwapped());
  if (!filePath.isEmpty()) {
    image.save(filePath);
  }
}

void glViewer::ModelSet() {
  std::string path = Settings->file_path.toStdString();
  if (path != "") {
    controller_.SetModel(path);
    Settings->num_of_v = controller_.get_num_v();
    Settings->num_of_f = controller_.get_num_f();
  }
}

void glViewer::gif() {
  gif_ = new QGifImage;
  timer_ = new QTimer(this);
  connect(timer_, &QTimer::timeout, this, &glViewer::MakeGif);
  gif_->setDefaultDelay(100);
  timer_->start(100);
}

void glViewer::MakeGif() {
  QImage frame = grabFramebuffer();
  gif_->addFrame(frame.scaled(640, 480), 0);
  if (gif_->frameCount() == 50) {
    timer_->stop();
    QString gif_path = QFileDialog::getSaveFileName(
        this, ("Save as GIF"), "image.gif", "GIF Image Files (*.gif)");
    gif_->save(gif_path);
    delete timer_;
    delete gif_;
  }
}

}  // namespace s21
