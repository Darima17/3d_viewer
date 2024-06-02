#ifndef CPP4_3DVIEWER_V2_0_SRC_VIEW_MAINWINDOW_H_
#define CPP4_3DVIEWER_V2_0_SRC_VIEW_MAINWINDOW_H_

#include <QColor>
#include <QColorDialog>
#include <QComboBox>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QMainWindow>
#include <QPalette>
#include <QSettings>
#include <QSlider>

#include "../models/figure.h"
#include "glViewer.h"
#include "momento.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Mainwindow;

}
QT_END_NAMESPACE

namespace s21 {

/**
 * @brief Класс Mainwindow - основное окно программы
 *
 * Этот класс представляет основное окно программы "3DViewer".
 * В нем содержится пользовательский интерфейс, который позволяет
 * пользователю настраивать и просматривать трехмерную сцену.
 *
 * Класс Mainwindow наследуется от класса QDialog, который
 * является частью библиотеки Qt для создания диалоговых окон.
 *
 * Основная часть класса состоит из метода инициализации окна
 * (Mainwindow::Mainwindow), который вызывается при создании
 * объекта Mainwindow. В методе инициализации окна создается
 * пользовательский интерфейс с помощью утилиты Qt Designer
 * (ui_->setupUi(this)).
 *
 * Класс использует настройки (Settings), которые хранятся в
 * объекте save_settings. Настройки загружаются при создании окна
 * и сохраняются при закрытии окна. В методе load_setting()
 * настройки читаются из QSettings и записываются в структуру
 * Settings. В методе save_setting() настройки из структуры
 *
 * Класс Mainwindow использует методы и сигналы для
 * обработки изменений настроек и отражения этих
 * изменений в трехмерной сцене. Такие методы и сигналы
 * как on_projection_currentIndexChanged(),
 * on_setBgrColor_clicked(), on_setVerColor_clicked() и
 * другие методы обработчиков сигналов.
 */

class Mainwindow : public QDialog {
  Q_OBJECT

 public:
  /**
   * @brief Конструктор для главного окна
   */
  explicit Mainwindow(QWidget *parent = nullptr);
  /**
   * @brief Деструктор
   */
  ~Mainwindow();

  /**
   * @brief Метод для инициализации настройок
   */
  MomentoSettings Settings;
  QSettings *save_settings;

  /**
   * @brief Методы для сохранения настройок
   */
  void save_setting();
  /**
   * @brief Метод для загрузки настройок
   */
  void load_setting();

 private slots:
  /**
   * @brief Слоты для обработки сигналов
   */
  void init_projection_currentIndexChanged(int index);
  void init_thickness_valueChanged(int value);
  void init_vetex_size_valueChanged(int value);
  void init_edge_type_currentIndexChanged(int value);
  void init_vertex_type_currentIndexChanged(int value);

  void on_setBackgr_clicked();
  void on_setEdg_clicked();
  void on_setVert_clicked();

  void on_edge_thickness_valueChanged(int value);
  void on_vetex_size_valueChanged(int value);
  void on_edge_type_currentIndexChanged(int index);
  void on_vertex_type_currentIndexChanged(int index);
  void on_projection_currentIndexChanged(int index);
  void on_file_add_clicked();

  void onSliderValueChanged_translate_x(int value);
  void onSliderValueChanged_translate_y(int value);
  void onSliderValueChanged_translate_z(int value);

  void onSliderValueChanged_rotate_x(int value);
  void onSliderValueChanged_rotate_y(int value);
  void onSliderValueChanged_rotate_z(int value);

  void onSliderValueChanged_scale(int value);
  void on_screen_clicked();
  void on_gif_clicked();
  void on_pushButton_pressed();

 private:
  Ui::Mainwindow *ui_;
};
}  // namespace s21

#endif  // CPP4_3DVIEWER_V2_0_SRC_VIEW_MAINWINDOW_H_
