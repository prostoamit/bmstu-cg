#ifndef BIRD_H
#define BIRD_H

#include "FigureContainer.h"

class Bird : public FigureContainer {
protected:

public:
    Bird();
    ~Bird();

    void to_default();
};

#endif //BIRD_H
