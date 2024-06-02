#include "mainwindow.h"

#include "ui_mainwindow.h"

namespace s21 {

Mainwindow::Mainwindow(QWidget *parent)
    : QDialog(parent), ui_(new Ui::Mainwindow) {
  ui_->setupUi(this);
  ui_->widget->setSettings(&Settings);
  save_settings = new QSettings("Proj", "3DViewer", this);
  load_setting();
  connect(ui_->horizontalSlider_scale, &QSlider::valueChanged, this,
          &Mainwindow::onSliderValueChanged_scale);
  connect(ui_->horizontalSlider_translate_x, &QSlider::valueChanged, this,
          &Mainwindow::onSliderValueChanged_translate_x);
  connect(ui_->horizontalSlider_translate_y, &QSlider::valueChanged, this,
          &Mainwindow::onSliderValueChanged_translate_y);
  connect(ui_->horizontalSlider_translate_z, &QSlider::valueChanged, this,
          &Mainwindow::onSliderValueChanged_translate_z);
  connect(ui_->horizontalSlider_rotate_x, &QSlider::valueChanged, this,
          &Mainwindow::onSliderValueChanged_rotate_x);
  connect(ui_->horizontalSlider_rotate_y, &QSlider::valueChanged, this,
          &Mainwindow::onSliderValueChanged_rotate_y);
  connect(ui_->horizontalSlider_rotate_z, &QSlider::valueChanged, this,
          &Mainwindow::onSliderValueChanged_rotate_z);
}

Mainwindow::~Mainwindow() {
  save_setting();
  delete ui_;
}

void Mainwindow::save_setting() {
  save_settings->setValue("backgrColor", Settings.backgrColor);
  save_settings->setValue("vertex_color", Settings.vertex_color);
  save_settings->setValue("edge_color", Settings.edge_color);
  save_settings->setValue("projection", Settings.projection);
  save_settings->setValue("vertex_size", Settings.vertex_size);
  save_settings->setValue("vertex_type", Settings.vertex_type);
  save_settings->setValue("edge_size", Settings.edge_size);
  save_settings->setValue("edge_type", Settings.edge_type);
}

void Mainwindow::load_setting() {
  Settings.backgrColor = save_settings->value("backgrColor").value<QColor>();
  Settings.vertex_color = save_settings->value("vertex_color").value<QColor>();
  Settings.edge_color = save_settings->value("edge_color").value<QColor>();
  Settings.projection = save_settings->value("projection").toInt();
  init_projection_currentIndexChanged(Settings.projection);
  Settings.vertex_size = save_settings->value("vertex_size").toFloat();
  init_vetex_size_valueChanged(Settings.vertex_size);
  Settings.edge_size = save_settings->value("edge_size").toFloat();
  init_thickness_valueChanged(Settings.edge_size);
  Settings.vertex_type = save_settings->value("vertex_type").toInt();
  init_vertex_type_currentIndexChanged(Settings.vertex_type);
  Settings.edge_type = save_settings->value("edge_type").toInt();
  init_edge_type_currentIndexChanged(Settings.edge_type);
  ui_->horizontalSlider_translate_x->setValue(0);
  ui_->horizontalSlider_translate_y->setValue(0);
  ui_->horizontalSlider_translate_z->setValue(0);
  ui_->horizontalSlider_rotate_x->setValue(0);
  ui_->horizontalSlider_rotate_y->setValue(0);
  ui_->horizontalSlider_rotate_z->setValue(0);
  ui_->horizontalSlider_scale->setValue(10);
}

void Mainwindow::on_projection_currentIndexChanged(int index) {
  Settings.projection = index;
  ui_->widget->update();
}

void Mainwindow::init_projection_currentIndexChanged(int index) {
  ui_->projection->setCurrentIndex(index);
}

void Mainwindow::on_file_add_clicked() {
  QString file_path = QFileDialog::getOpenFileName(
      this, "Add file", QString::fromStdString(Settings.src_path) + "obj_file",
      "*.obj");
  if (file_path.isEmpty()) {
    // User canceled the file dialog, do nothing
    return;
  }
  QFileInfo file_info(file_path);
  Settings.file_name = file_info.fileName();
  Settings.file_path = file_path;
  ui_->widget->ModelSet();
  ui_->info_box->setText("Name: " + Settings.file_name);
  ui_->info_box->setText(ui_->info_box->toPlainText() +
                         "\nVertices: " + QString::number(Settings.num_of_v) +
                         "\nFaces: " + QString::number(Settings.num_of_f));
  Settings.info_box = ui_->info_box->toPlainText();
  ui_->widget->update();
}

void Mainwindow::on_setBackgr_clicked() {
  QColorDialog *dialog = new QColorDialog(this);
  dialog->show();
  QObject::connect(dialog, &QDialog::accepted, [=]() {
    Settings.backgrColor = dialog->currentColor();
    ui_->widget->update();
  });
}

void Mainwindow::on_setEdg_clicked() {
  QColorDialog *dialog = new QColorDialog(this);
  dialog->show();
  QObject::connect(dialog, &QDialog::accepted, [=]() {
    Settings.edge_color = dialog->currentColor();
    ui_->widget->update();
  });
}

void Mainwindow::on_setVert_clicked() {
  QColorDialog *dialog = new QColorDialog(this);
  dialog->show();
  QObject::connect(dialog, &QDialog::accepted, [=]() {
    Settings.vertex_color = dialog->currentColor();
    ui_->widget->update();
  });
}

void Mainwindow::on_edge_thickness_valueChanged(int value) {
  Settings.edge_size = value;
  ui_->widget->update();
}

void Mainwindow::on_vetex_size_valueChanged(int value) {
  Settings.vertex_size = value;
  ui_->widget->update();
}

void Mainwindow::on_edge_type_currentIndexChanged(int index) {
  Settings.edge_type = index;
  ui_->widget->update();
}

void Mainwindow::on_vertex_type_currentIndexChanged(int index) {
  Settings.vertex_type = index;
  ui_->widget->update();
}
void Mainwindow::init_thickness_valueChanged(int value) {
  ui_->edge_thickness->setValue(value);
}

void Mainwindow::init_vetex_size_valueChanged(int value) {
  ui_->vetex_size->setValue(value);
}

void Mainwindow::init_edge_type_currentIndexChanged(int value) {
  ui_->edge_type->setCurrentIndex(value);
}

void Mainwindow::init_vertex_type_currentIndexChanged(int value) {
  ui_->vertex_type->setCurrentIndex(value);
}

void Mainwindow::onSliderValueChanged_translate_x(int value) {
  double doub_value = value / 10;
  ui_->label_value_translate_x->setText(QString::number(value));
  double offset = doub_value - Settings.prevTranslateX;
  Settings.prevTranslateX = doub_value;
  ui_->widget->controller_.Set_move(offset, 0, 0);
  ui_->widget->update();
}

void Mainwindow::onSliderValueChanged_translate_y(int value) {
  double doub_value = value / 10;
  ui_->label_value_translate_y->setText(QString::number(value));
  double offset = doub_value - Settings.prevTranslateY;
  Settings.prevTranslateY = doub_value;
  ui_->widget->controller_.Set_move(0, offset, 0);
  ui_->widget->update();
}

void Mainwindow::onSliderValueChanged_translate_z(int value) {
  double doub_value = value / 10;
  ui_->label_value_translate_z->setText(QString::number(value));
  double offset = doub_value - Settings.prevTranslateZ;
  Settings.prevTranslateZ = doub_value;
  ui_->widget->controller_.Set_move(0, 0, offset);
  ui_->widget->update();
}

void Mainwindow::onSliderValueChanged_rotate_x(int value) {
  ui_->label_value_rotate_x->setText(QString::number(value));
  double offset = value - Settings.prevRotateX;
  ui_->widget->controller_.Set_rotate(offset, 0, 0);
  Settings.prevRotateX = value;
  ui_->widget->update();
}

void Mainwindow::onSliderValueChanged_rotate_y(int value) {
  ui_->label_value_rotate_y->setText(QString::number(value));
  double offset = value - Settings.prevRotateY;
  ui_->widget->controller_.Set_rotate(0, offset, 0);
  Settings.prevRotateY = value;
  ui_->widget->update();
}

void Mainwindow::onSliderValueChanged_rotate_z(int value) {
  ui_->label_value_rotate_z->setText(QString::number(value));
  double offset = value - Settings.prevRotateZ;
  ui_->widget->controller_.Set_rotate(0, 0, offset);
  Settings.prevRotateZ = value;
  ui_->widget->update();
}

void Mainwindow::onSliderValueChanged_scale(int value) {
  double doub_value = value / 10.0f;
  ui_->label_value_scale->setText(QString::number(doub_value));
  double new_value = doub_value / Settings.prevScale;
  Settings.prevScale = doub_value;
  ui_->widget->controller_.Set_scale(new_value);
  ui_->widget->update();
}

void Mainwindow::on_screen_clicked() { ui_->widget->screenshot(); }

void Mainwindow::on_gif_clicked() { ui_->widget->gif(); }

void Mainwindow::on_pushButton_pressed() {
  ui_->horizontalSlider_translate_x->setValue(0);
  ui_->horizontalSlider_translate_y->setValue(0);
  ui_->horizontalSlider_translate_z->setValue(0);
  ui_->horizontalSlider_rotate_x->setValue(0);
  ui_->horizontalSlider_rotate_y->setValue(0);
  ui_->horizontalSlider_rotate_z->setValue(0);
  ui_->horizontalSlider_scale->setValue(10);
  ui_->widget->ModelSet();
}

}  // namespace s21
