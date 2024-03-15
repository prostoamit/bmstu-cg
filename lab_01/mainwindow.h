#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSignalMapper>
#include <QGraphicsScene>
#include <QGraphicsItem>

#include "points.h"
#include "circle.h"
#include "triangle.h"
#include "solution.h"
#include "scale.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_PointInputButton_clicked();

    void on_PointsDeleteAllButton_clicked();

    void on_PointDeleteButton_clicked();

    void on_SolutionButton_clicked();

    void on_SolutionClearButton_clicked();

    void on_SwitchViewButton_clicked();

    void on_PointXInput_returnPressed();

    void on_PointYInput_returnPressed();

    void on_PointDeleteInput_returnPressed();

    void on_pushButton_clicked();

    void on_PointXInput_editingFinished();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *solution_scene;

    GraphicPoints points;
    GraphicsTriangle triangle;
    GraphicsCircle circumcirle;

    Solution solution;

    Scale scale;

    void point_input_error_handler();
    void point_delete_error_handler();
    void not_enough_points_error_handler();
    void no_triangle_error_handler();
    void point_edit_error_handler();

};
#endif // MAINWINDOW_H
