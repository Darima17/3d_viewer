#ifndef CPP4_3DVIEWER_V2_0_SRC_VIEW_GLVIEWER_H
#define CPP4_3DVIEWER_V2_0_SRC_VIEW_GLVIEWER_H

#include <QMainWindow>

#include "../controller/controller.h"
#include "momento.h"

#ifdef __APPLE__  // Проверка для macOS
#include <gl.h>
#elif __linux__  // Проверка для Linux
#include <GL/gl.h>
#endif
#include <QFileDialog>
#include <QImage>
#include <QImageWriter>
#include <QMessageBox>
#include <QOpenGLFramebufferObject>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QTimer>
#include <QWheelEvent>
#include <QWidget>
#include <iostream>

#include "gifUtils/qgifimage.h"

namespace s21 {

/**
 * @brief Класс glViewer -  наследующийся от QOpenGLWidget и реализующий
 * QOpenGLFunctions, используемый для отрисовки трехмерной сцены с помощью
 * OpenGL.
 *
 * glViewer является виджетным классом, который используется для отображения
 * трехмерной сцены. Он наследуется от QOpenGLWidget, что дает ему возможность
 * использовать методы OpenGL и функции QOpenGLFunctions. QOpenGLWidget является
 * виджетным классом, который может создать свою собственную контекст OpenGL и
 * взаимодействовать с ним.
 *
 * glViewer также использует MomentoSettings для управления настройками сцены и
 * FigureFacade для управления трехмерной сценой.
 *
 */

class glViewer : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT

 private:
  /**
   * @brief MomentoSettings - настройки сцены.
   */
  MomentoSettings *Settings;
  QGifImage *gif_;
  QTimer *timer_;
  FigureFacade figure;

 public:
  Controller controller_;
  const char *file_path;
  glViewer(QWidget *parent = Q_NULLPTR);
  /**
   * @brief initializeGL - инициализация OpenGL.
   */
  void initializeGL() override;
  /**
   * @brief resizeGL - изменение размеров OpenGL.
   * @param w - ширина окна
   * @param h - высота окна
   */
  void resizeGL(int w, int h) override;
  /**
   * @brief paintGL - отрисовка OpenGL.
   */
  void paintGL() override;
  /**
   * @brief vertex - отрисовка вершин.
   */
  void vertex();
  /**
   * @brief edge - отрисовка ребер.
   */
  void edge();
  /**
   * @brief setSettings - установка настройки сцены.
   * @param newSettings - настройки сцены.
   */
  void setSettings(MomentoSettings *newSettings);
  /**
   * @brief screenshot - создание скриншота.
   */
  void screenshot();
  /**
   * @brief ModelSet - установка настройки сцены.
   */
  void ModelSet();
  /**
   * @brief gif - создание gif.
   */
  void gif();
  /**
   * @brief MakeGif - создание gif.
   */
  void MakeGif();
};
}  // namespace s21
#endif  // CPP4_3DVIEWER_V2_0_SRC_VIEW_GLVIEWER_H
