#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QColorDialog>
#include <QMessageBox>

#include "Lines.h"

#include "Research.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    int drawer_height = ui->PainterWidget->height();
    int drawer_width = ui->PainterWidget->width();

    painter.setPen(QPen(Qt::black, 3));

    pix_map = QPixmap(drawer_width, drawer_height);
//    pix_map.fill(QColor(255, 255, 255, ));

    pix_map.fill(Qt::transparent);

    painter.begin(&pix_map);

//    draw_requested = true;

    background_color = Qt::white;

    QPalette palette;
    palette.setColor(ui->BackgroundColorLabel->backgroundRole(), Qt::white);
    ui->BackgroundColorLabel->setPalette(palette);
    ui->PainterWidget->setPalette(palette);

    palette.setColor(ui->BackgroundColorLabel->backgroundRole(), Qt::black);
    ui->LineColorLabel->setPalette(palette);
    line_color = Qt::black;

    ui->DDACheck->setChecked(true);
    line_drawer = Lines::dda;
}

MainWindow::~MainWindow() {
    delete ui;
}

void
MainWindow::paintEvent(QPaintEvent *event) {
    if (draw_requested) {
        ui->PainterWidget->setPixmap(pix_map);

        draw_requested = false;
    }
}

void
MainWindow::on_DrawSegmentButton_clicked() {
    Point point_1(ui->Point1XInput->value(), ui->Point1YInput->value());
    Point point_2(ui->Point2XInput->value(), ui->Point2YInput->value());

    line_drawer(painter, point_1, point_2);

    draw_requested = true;
    update();
}

#include <cmath>
#define PI acos(-1.0)

void
MainWindow::range_draw(QPainter &painter, const Point &center, int radius, int angle) {
    double t = 0.0;
    double delta = angle * PI / 180.0;

    for (int i = 0; i < 360 / angle; i++) {
        double x = center.get_x() + radius * cos(t);
        double y = center.get_y() - radius * sin(t);

        Point radial(int(round(x)), int(round(y)));
        line_drawer(painter, center, radial);

        t += delta;
    }
}

void
MainWindow::on_DrawRangeButton_clicked() {
    int radius = ui->RangeRadiusInput->value();
    int angle = ui->RangeAngleInput->value();

    if (angle == 0) {
        QMessageBox::critical(nullptr, "Ошибка", "Нулевой угол");
        ui->RangeAngleInput->setValue(1);
        return;
    }

    Point center(ui->PainterWidget->width() / 2, ui->PainterWidget->height() / 2);
    range_draw(painter, center, radius, angle);

    draw_requested = true;
    update();
}

void
MainWindow::on_ClearScreenButton_clicked() {

    pix_map.fill(Qt::transparent);
    draw_requested = true;
    update();
}


void
MainWindow::on_ResearchStepsButton_clicked() {
    Research::steps_research("steps_research.txt");
    std::system("./show_steps.sh");
}


void
MainWindow::on_ResearchTimeButton_clicked() {
    QColor color = Qt::transparent;
    Research::time_research(painter, color, "time_research.txt");
    std::system("./show_time.sh");
}


void
MainWindow::on_DDACheck_clicked() {
    line_drawer = Lines::dda;
}


void
MainWindow::on_BresenhamRealCheck_clicked() {
    line_drawer = Lines::bresenham_real;
}


void
MainWindow::on_BresenhamIntegerCheck_clicked() {
    line_drawer = Lines::bresenham_int;

}


void
MainWindow::on_BresenhamNoStepsCheck_clicked() {
    line_drawer = Lines::bresenham_smooth;
}


void
MainWindow::on_WuCheck_clicked() {
    line_drawer = Lines::wu;

}


void
MainWindow::on_LibraryCheck_clicked() {
    line_drawer = Lines::library;

}

void
MainWindow::on_LineColorButton_clicked() {
    line_color = QColorDialog::getColor();

    QPalette palette;
    palette.setColor(ui->LineColorLabel->backgroundRole(), line_color);
    ui->LineColorLabel->setPalette(palette);

    painter.setPen(line_color);
}


void
MainWindow::on_BackgroundColorButton_clicked() {
    background_color = QColorDialog::getColor();

    QPalette palette;
    palette.setColor(ui->BackgroundColorLabel->backgroundRole(), background_color);
    ui->BackgroundColorLabel->setPalette(palette);

    ui->PainterWidget->setPalette(palette);
}

