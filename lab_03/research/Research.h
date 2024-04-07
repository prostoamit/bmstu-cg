#ifndef RESEARCH_H
#define RESEARCH_H

#include <QPainter>
#include <QColor>

#include "Lines.h"

class Research {
public:
    static int time_research(QPainter &painter, QColor &color, char *filename);
    static int steps_research(char *filename);
};


#endif //RESEARCH_H
