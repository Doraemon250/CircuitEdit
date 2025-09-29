#include "Shape.h"

void Line::drawSelf(wxGraphicsContext* gc) const {
    gc->StrokeLine(GetStart().x, GetStart().y, GetStart().x, GetEnd().y);
    gc->StrokeLine(GetStart().x, GetEnd().y, GetEnd().x, GetEnd().y);
}

void ComponentNot :: drawSelf(wxGraphicsContext* gc) const {
    gc->DrawEllipse(GetStart().x - 5, GetStart().y - 5, 10, 10);
    gc->StrokeLine(GetStart().x - 35, GetStart().y - 20, GetStart().x - 35, GetStart().y + 20);
    gc->StrokeLine(GetStart().x - 35, GetStart().y - 20, GetStart().x - 5, GetStart().y);
    gc->StrokeLine(GetStart().x - 35, GetStart().y + 20, GetStart().x - 5, GetStart().y);
}


void ComponentAnd::drawSelf(wxGraphicsContext* gc) const {
    gc->StrokeLine(GetStart().x - 40, GetStart().y - 20, GetStart().x - 40, GetStart().y);
}