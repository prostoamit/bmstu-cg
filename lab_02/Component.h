//
// Created by woprpp on 3/11/24.
//

#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <list>

#include "Transformations.h"
#include "Vector.h"
#include "Matrix.h"
#include "SimplePoint.h"

class Component {
protected:
    Component *parent_;

public:
    virtual ~Component();

    void set_parent(Component *parent) { this->parent_ = parent; };

    Component *get_parent() const { return this->parent_; };
    virtual void add(Component*);
    virtual void remove(Component*);
    virtual bool is_composite() const { return false; };

    virtual int move(Transformations::move_deltas&) = 0;
    virtual int scale(SimplePoint center, Transformations::scale_coeffs&) = 0;
    virtual int rotate(SimplePoint center, Transformations::rotate_angle&) = 0;
};

#endif //COMPOSITE_H
