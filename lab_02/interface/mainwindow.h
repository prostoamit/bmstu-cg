#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "Bird.h"
#include "Ellipse.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);

private slots:
    void on_TransformationCenterToFigureCenterButton_clicked();

    void on_TransformationCenterButton_clicked();

    void on_RotationButton_clicked();

    void on_ScaleButton_clicked();

    void on_MoveButton_clicked();

    void on_StepBackButton_clicked();

    void on_ResetButton_clicked();

private:
    Ui::MainWindow *ui;

    Bird bird;
    Bird save;

    QPixmap pix_map;

    Point transformation_center;

    Ellipse transformation_center_visual_point;
    void set_transformation_visual_point();

    void set_figure_center();

};
#endif // MAINWINDOW_H
