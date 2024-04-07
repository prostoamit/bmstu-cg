#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

#include "Lines.h"

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
    void on_DrawSegmentButton_clicked();

    void on_ClearScreenButton_clicked();

    void on_ResearchStepsButton_clicked();

    void on_ResearchTimeButton_clicked();

    void on_DDACheck_clicked();

    void on_BresenhamRealCheck_clicked();

    void on_BresenhamIntegerCheck_clicked();

    void on_BresenhamNoStepsCheck_clicked();

    void on_WuCheck_clicked();

    void on_LibraryCheck_clicked();

    void on_DrawRangeButton_clicked();

    void on_LineColorButton_clicked();

    void on_BackgroundColorButton_clicked();

private:
    Ui::MainWindow *ui;

    QPixmap pix_map;
    QPainter painter;

    void (*line_drawer) (QPainter&, const Point&, const Point&);

    bool draw_requested;

    void range_draw(QPainter &painter, const Point &center, int radius, int angle);

    QColor background_color;
    QColor line_color;
};
#endif // MAINWINDOW_H
