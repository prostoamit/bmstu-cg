#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "points.h"
#include "point.h"

#include <QDebug>
#include <QMessageBox>

#include <string>
#include <regex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PointsTable->setColumnCount(2);
    ui->PointsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    QGraphicsScene *scene =  new QGraphicsScene(this);
    scene->setSceneRect(0.0, 0.0, ui->Graphics->rect().width(), ui->Graphics->rect().height());

    QGraphicsScene *solution_scene = new QGraphicsScene(this);
    solution_scene->setSceneRect(0.0, 0.0, ui->Graphics->rect().width(), ui->Graphics->rect().height());

    this->solution.scene = solution_scene;
    this->solution.view = ui->Graphics;
    this->solution.text = ui->SolutionText;
    this->solution.scale.view = ui->Graphics;
    this->solution.scale.scene = this->solution.scene;

    this->points.scene = scene;
    this->points.view =  ui->Graphics;

    this->scale.scene = this->points.scene;
    this->scale.view = ui->Graphics;

    ui->Graphics->setScene(scene);
    ui->Graphics->setAlignment(Qt::AlignLeft | Qt::AlignTop);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool
is_fpn(std::string &string)
{
    std::regex FPNRegex("[+-]?[0-9]+(.[0-9]+([eE][+-]?[0-9]+)?|([eE][+-]?[0-9]+))?");
    return std::regex_match(string, FPNRegex);
}

bool
is_int(std::string &string)
{
    std::regex INTRegex("[+-]?[0-9]+");
    return std::regex_match(string, INTRegex);
}

void
table_add_point(QTableWidget *table, Point point)
{
    int rows_count = table->rowCount();
    table->insertRow(rows_count);

    QTableWidgetItem *x_cell = new QTableWidgetItem(QString::fromStdString(std::to_string(point.x)));
    x_cell->setFlags(x_cell->flags() ^ Qt::ItemIsEditable);
    table->setItem(rows_count, 0, x_cell);


    QTableWidgetItem *y_cell = new QTableWidgetItem(QString::fromStdString(std::to_string(point.y)));
    y_cell->setFlags(y_cell->flags() ^ Qt::ItemIsEditable);
    table->setItem(rows_count, 1, y_cell);


//    table->setCellWidget(rows_count, 0, new QLabel);
//    table->setCellWidget(rows_count, 1, new QLabel);

//    double x_value = point.x;
//    std::string x_stdstring = std::to_string(x_value);
//    ((QLineEdit *)table->cellWidget(rows_count, 0))->setText(QString::fromStdString(x_stdstring));

//    double y_value = point.y;
//    std::string y_stdstring = std::to_string(y_value);
//    ((QLineEdit *)table->cellWidget(rows_count, 1))->setText(QString::fromStdString(y_stdstring));
}

void
MainWindow::point_input_error_handler()
{
    QMessageBox::warning(this, "Ошибка ввода", "Ошибка при вводе точки.");
    ui->PointXInput->setValue(0.0);
    ui->PointYInput->setValue(0.0);
}

void
MainWindow::point_delete_error_handler()
{
    QMessageBox::warning(this, "Ошибка ввода", "Ошибка при вводе позиции.");
    ui->PointDeleteInput->setValue(1);
}

void
MainWindow::not_enough_points_error_handler()
{
    QMessageBox::warning(this, "Ошибка решения", "Недостаточно точек для построение треугольника.");
}


void
MainWindow::no_triangle_error_handler()
{
    QMessageBox::warning(this, "Ошибка решения", "Среди сочетаний трёх точек не был найден треугольник.");
    ui->Graphics->setScene(this->points.scene);
}

void
MainWindow::point_edit_error_handler()
{
    QMessageBox::warning(this, "Ошибка ввода", "Ошибка при вводе позиции.");
    ui->Graphics->setScene(this->points.scene);
}

void
MainWindow::on_PointInputButton_clicked()
{
    double x_value = ui->PointXInput->value();
    double y_value = ui->PointYInput->value();
    Point point = {x_value, y_value};

    table_add_point(ui->PointsTable, point);
    this->points.push_back(point);

    this->scale.clear();
    this->scale.set_params(this->points.scope());
    this->scale.draw();

    ui->PointXInput->setValue(0.0);
    ui->PointYInput->setValue(0.0);

    ui->Graphics->setScene(this->points.scene);
    ui->SolutionText->setText(ui->SolutionText->toPlainText() + "\nДобавлена точка x: " +
                            QString::fromStdString(std::to_string(x_value)) + "\ty: " +
                              QString::fromStdString(std::to_string(y_value)) + ".\n");

    ui->PointXInput->setFocus();
}


void
MainWindow::on_PointsDeleteAllButton_clicked()
{
    for (std::size_t i = 0; i < this->points.size(); i++)
        ui->PointsTable->removeRow(0);
    this->points.clear();
    ui->PointsTable->setRowCount(0);


    this->scale.clear();
    this->scale.set_params(this->points.scope());
    this->scale.draw();


    ui->SolutionText->setText(ui->SolutionText->toPlainText() + "\nУдалены все точки.");

    ui->Graphics->setScene(this->points.scene);
    this->solution.scene->clear();
}


void
MainWindow::on_PointDeleteButton_clicked()
{
    std::size_t position = ui->PointDeleteInput->value();
    if (position <= 0 || position > this->points.size())
    {
        point_delete_error_handler();
        ui->PointXInput->setFocus();
        return;
    }

    ui->SolutionText->setText(ui->SolutionText->toPlainText() + "\nУдалена точка x: " +
                              QString::fromStdString(std::to_string(this->points.get_point(position - 1).x)) + "\ty: " +
                              QString::fromStdString(std::to_string(this->points.get_point(position - 1).y)) + ".\n");

    this->points.remove(position - 1);
    ui->PointsTable->removeRow((int)(position - 1));

    this->scale.clear();
    this->scale.set_params(this->points.scope());
    this->scale.draw();

    ui->Graphics->setScene(this->points.scene);
    ui->PointXInput->setFocus();
}


void
MainWindow::on_SolutionButton_clicked()
{
    if (this->points.size() < 3)
    {
        not_enough_points_error_handler();
        return;
    }

    if (this->solution.draw(this->points) != 0)
    {
        this->no_triangle_error_handler();
        return;
    }
    ui->Graphics->setScene(this->solution.scene);
}


void MainWindow::on_SolutionClearButton_clicked()
{
    ui->SolutionText->clear();
}

void MainWindow::on_SwitchViewButton_clicked()
{
    if (ui->Graphics->scene() == this->points.scene)
        ui->Graphics->setScene(this->solution.scene);
    else
        ui->Graphics->setScene(this->points.scene);
}


void MainWindow::on_PointXInput_returnPressed()
{
    this->on_PointInputButton_clicked();
}


void MainWindow::on_PointYInput_returnPressed()
{
    this->on_PointInputButton_clicked();
}


void MainWindow::on_PointDeleteInput_returnPressed()
{
    this->on_PointDeleteButton_clicked();
}

void
table_edit_point(QTableWidget *table, int n, Point point)
{
    table->item(n, 0)->setText(QString::fromStdString(std::to_string(point.x)));
    table->item(n, 1)->setText(QString::fromStdString(std::to_string(point.y)));
}
void MainWindow::on_pushButton_clicked()
{
    int position = ui->PointEditPositionInput->value();
    if (position <= 0 || position > this->points.size())
    {
        point_edit_error_handler();
        ui->PointEditPositionInput->setFocus();
        return;
    }

    double x_value = ui->PointEdirXInput->value();
    double y_value = ui->PointEditYInput->value();

    this->points.edit_point(position - 1, {x_value, y_value});
    table_edit_point(ui->PointsTable, position - 1, {x_value, y_value});

    this->scale.clear();
    this->scale.set_params(this->points.scope());
    this->scale.draw();

    ui->Graphics->setScene(this->points.scene);

    ui->SolutionText->setText(ui->SolutionText->toPlainText() + "\nТочка 1 заменена на x: " +
                              QString::fromStdString(std::to_string(x_value)) + "\ty: " +
                              QString::fromStdString(std::to_string(y_value)) + ".\n");
}


void MainWindow::on_PointXInput_editingFinished()
{
    return;
}

