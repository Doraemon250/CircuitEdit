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
    double x = GetStart().x;
    double y = GetStart().y;

    double widthRect = 20;   // 矩形宽度
    double height = 40;      // 总高度
    double radius = height / 2; // 半圆半径

    // 左矩形左上角和右下角
    double rectLeft = x - widthRect - radius;
    double rectRight = x - radius;
    double rectTop = y - height / 2;
    double rectBottom = y + height / 2;

    wxGraphicsPath path = gc->CreatePath();

    // 1️⃣ 绘制矩形
    path.MoveToPoint(rectLeft, rectTop);
    path.AddLineToPoint(rectRight, rectTop);
    path.AddLineToPoint(rectLeft, rectTop);
    path.AddLineToPoint(rectLeft, rectBottom);
    path.AddLineToPoint(rectRight, rectBottom); // 闭合矩形

    // 2️⃣ 绘制半圆并闭合路径
    path.MoveToPoint(rectRight, rectTop);            // 半圆上边起点
    path.AddArc(rectRight + radius, y, radius, -M_PI / 2, M_PI / 2, true); // 半圆凸向右
    path.AddLineToPoint(rectRight, rectBottom);      // 下边点回到矩形状

    // 绘制路径
    gc->StrokePath(path);

    // 3️⃣ 输入线（两条）
    gc->StrokeLine(rectLeft - 20, y - 10, rectLeft, y - 10);
    gc->StrokeLine(rectLeft - 20, y + 10, rectLeft, y + 10);

    // 4️⃣ 输出线（半圆右侧）
    // 输出线从半圆最右侧延伸
    double outputStartX = rectRight + 2 * radius; // 半圆最右侧 x 坐标
    gc->StrokeLine(outputStartX, y, outputStartX + 20, y);

}


