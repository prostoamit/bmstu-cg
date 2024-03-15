#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "triangle.h"
#include "circle.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "lab_01_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}

#ifdef NOTDEF
int main()
{
    Triangle triangle({0,0}, {0,1}, {1,0});
//    Circle result = triangle.circumcirle();
    double area = triangle.area();

    printf("%.6lf\n", area);

    return 0;
}
#endif
