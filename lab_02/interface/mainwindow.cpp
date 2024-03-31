#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QPainterPath>
#include <QString>
#include <QMessageBox>

#include <cmath>

#include "Bird.h"

#include "Drawer.h"

#include "Ellipse.h"

#define EPS 1e-5

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow), transformation_center_visual_point(Point(0.0, 0.0), 1, 1) {
    ui->setupUi(this);

    int drawer_height = ui->DrawLabel->height();
    int drawer_width = ui->DrawLabel->width();

    pix_map = QPixmap(drawer_width, drawer_height);
    pix_map.fill(Qt::white);

    bird.scale(bird.center(), 8, 8);
    transformation_center = bird.center();

    set_transformation_visual_point();

    save = bird;

    ui->FigureCenterXLabel->setText(QString::asprintf("%.2lf", bird.center().get_x()));
    ui->FigureCenterYLabel->setText(QString::asprintf("%.2lf", bird.center().get_y()));

    ui->TransformationCenterXInput->setValue(transformation_center.get_x());
    ui->TransformationCenterYInput->setValue(transformation_center.get_y());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    pix_map.fill(Qt::white);

    QPainter painter(&pix_map);
    painter.setPen(QPen(Qt::black, 3));

    Drawer::draw_figure(painter, ui->DrawLabel->height(), ui->DrawLabel->width(), &bird);

    painter.setPen(QPen(Qt::red, 3));
    Drawer::draw_figure(painter, ui->DrawLabel->height(), ui->DrawLabel->width(), &transformation_center_visual_point);
    painter.setPen(QPen(Qt::black, 3));

    ui->DrawLabel->setPixmap(pix_map);
}


void
MainWindow::set_transformation_visual_point() {
    Point tcvpc = transformation_center_visual_point.center();
    transformation_center_visual_point.move(-tcvpc.get_x(), -tcvpc.get_y());
    transformation_center_visual_point.move(transformation_center.get_x(), transformation_center.get_y());
}

void MainWindow::set_figure_center() {
    ui->FigureCenterXLabel->setText(QString::asprintf("%.2lf", bird.center().get_x()));
    ui->FigureCenterYLabel->setText(QString::asprintf("%.2lf", bird.center().get_y()));
}

void MainWindow::on_TransformationCenterToFigureCenterButton_clicked()
{
    transformation_center = bird.center();
    set_transformation_visual_point();

    ui->TransformationCenterXInput->setValue(transformation_center.get_x());
    ui->TransformationCenterYInput->setValue(transformation_center.get_y());
}


void MainWindow::on_TransformationCenterButton_clicked()
{
    transformation_center = Point(
            ui->TransformationCenterXInput->value(),
            ui->TransformationCenterYInput->value()
            );

    set_transformation_visual_point();
}


void MainWindow::on_RotationButton_clicked()
{
    save = bird;

    double angle = ui->RotationAngleInput->value();

    bird.rotate(transformation_center, angle);

    set_figure_center();
}


void MainWindow::on_ScaleButton_clicked()
{
    save = bird;

    double kx = ui->ScalekXInput->value();
    double ky = ui->ScalekYInput->value();

    if (abs(kx) < EPS) {
        QMessageBox::critical(NULL, "Ошибка", "Нулевой коэффициент масштабирования по X.");
        ui->ScalekXInput->setValue(1.0);
        ui->ScalekYInput->setValue(1.0);
        return;
    }

    if (abs(ky) < EPS) {
        QMessageBox::critical(NULL, "Ошибка", "Нулевой коэффициент масштабирования по Y.");
        ui->ScalekXInput->setValue(1.0);
        ui->ScalekYInput->setValue(1.0);
        return;
    }

    bird.scale(transformation_center, kx, ky);

    set_figure_center();
}


void MainWindow::on_MoveButton_clicked()
{
    save = bird;

    double dx = ui->MovedXInput->value();
    double dy = ui->MovedYInput->value();

    bird.move(dx, dy);

    set_figure_center();
}


void MainWindow::on_StepBackButton_clicked()
{
    bird = save;
}

void MainWindow::on_ResetButton_clicked()
{
    bird.to_default();

    int drawer_height = ui->DrawLabel->height();
    int drawer_width = ui->DrawLabel->width();

    bird.scale(bird.center(), 8, 8);

    transformation_center = bird.center();
    save = bird;
    set_transformation_visual_point();

    ui->FigureCenterXLabel->setText(QString::asprintf("%.2lf", bird.center().get_x()));
    ui->FigureCenterYLabel->setText(QString::asprintf("%.2lf", bird.center().get_y()));

    ui->TransformationCenterXInput->setValue(transformation_center.get_x());
    ui->TransformationCenterYInput->setValue(transformation_center.get_y());
}

