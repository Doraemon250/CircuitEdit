#include "Shape.h"

void Line::drawSelf(wxGraphicsContext* gc) const {
    gc->StrokeLine(GetStart().x, GetStart().y, GetStart().x, GetEnd().y);
    gc->StrokeLine(GetStart().x, GetEnd().y, GetEnd().x, GetEnd().y);
}

void ComponentNot::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 30;        // 门宽度
    double height = 40;       // 门高度
    double circleRadius = 5;  // 小圆圈半径

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    wxGraphicsPath path = gc->CreatePath();

    // 绘制三角形形状（与缓冲门相同）
    path.MoveToPoint(leftX, topY);        // 左上角
    path.AddLineToPoint(rightX, y);       // 右侧中心
    path.AddLineToPoint(leftX, bottomY);  // 左下角
    path.CloseSubpath();                  // 闭合三角形

    // 绘制门主体
    gc->StrokePath(path);

    // 绘制输出端的小圆圈（表示取反）
    double circleCenterX = rightX + circleRadius; // 圆圈中心在三角形右侧
    wxGraphicsPath circlePath = gc->CreatePath();
    circlePath.AddCircle(circleCenterX, y, circleRadius);
    gc->StrokePath(circlePath);

    // 输入线（从左侧中心接入）
    gc->StrokeLine(x - width - 20, y, leftX, y);

    // 输出线（从小圆圈右侧延伸）
    gc->StrokeLine(circleCenterX + circleRadius, y, circleCenterX + circleRadius + 20, y);
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


void ComponentOr::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 40;        // 门宽度
    double height = 40;       // 门高度

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    wxGraphicsPath path = gc->CreatePath();

    // 从顶部左侧开始
    path.MoveToPoint(leftX, topY);

    // 第一条曲线：左侧小曲度曲线（从左上到左下）
    path.AddQuadCurveToPoint(
        leftX + width * 0.2, y,  // 控制点
        leftX, bottomY           // 终点（底部左侧）
    );

    // 第二条曲线：右侧下半部分大曲度曲线（从左下到右中）
    path.AddQuadCurveToPoint(
        leftX + width * 0.8, bottomY - height * 0.2,  // 控制点
        rightX, y                                     // 终点（右侧中心）
    );

    // 第三条曲线：右侧上半部分大曲度曲线（从右中到右上）
    path.AddQuadCurveToPoint(
        leftX + width * 0.8, topY + height * 0.2,  // 控制点
        leftX, topY                                // 终点（顶部左侧）
    );

    // 闭合路径
    path.CloseSubpath();

    // 绘制门主体
    gc->StrokePath(path);

    // 输入线（两条，从左侧接入）
    gc->StrokeLine(leftX - 20, y - 10, leftX+3, y - 10);
    gc->StrokeLine(leftX - 20, y + 10, leftX+3, y + 10);

    // 输出线（从右侧中心引出）
    gc->StrokeLine(rightX, y, rightX + 20, y);
}

void ComponentBuffer::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 30;        // 门宽度
    double height = 40;       // 门高度

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    wxGraphicsPath path = gc->CreatePath();

    // 绘制三角形形状（缓冲门的标准表示）
    path.MoveToPoint(leftX, topY);        // 左上角
    path.AddLineToPoint(rightX, y);       // 右侧中心
    path.AddLineToPoint(leftX, bottomY);  // 左下角
    path.CloseSubpath();                  // 闭合三角形

    // 绘制门主体
    gc->StrokePath(path);

    // 输入线（从左侧中心接入）
    gc->StrokeLine(x - width - 20, y, leftX, y);

    // 输出线（从右侧中心引出）
    gc->StrokeLine(rightX, y, rightX + 20, y);
}



void ComponentNAnd::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double widthRect = 20;   // 矩形宽度
    double height = 40;      // 总高度
    double radius = height / 2; // 半圆半径
    double circleRadius = 5; // 小圆圈半径

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

    //  绘制输出端的小圆圈（表示取反）
    double circleCenterX = rectRight + 2.3 * radius; // 圆圈中心在半圆最右侧
    wxGraphicsPath circlePath = gc->CreatePath();
    circlePath.AddCircle(circleCenterX, y, circleRadius);
    gc->StrokePath(circlePath);


    // 3️⃣ 输入线（两条）
    gc->StrokeLine(rectLeft - 20, y - 10, rectLeft, y - 10);
    gc->StrokeLine(rectLeft - 20, y + 10, rectLeft, y + 10);

    // 4️⃣ 输出线（半圆右侧）
    // 输出线从半圆最右侧延伸
    double outputStartX = rectRight + 2.6 * radius; // 半圆最右侧 x 坐标
    gc->StrokeLine(outputStartX, y, outputStartX + 20, y);

}

void ComponentNOr::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 40;        // 门宽度
    double height = 40;       // 门高度
    double circleRadius = 5;  // 小圆圈半径

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    wxGraphicsPath path = gc->CreatePath();

    // 从顶部左侧开始
    path.MoveToPoint(leftX, topY);

    // 第一条曲线：左侧小曲度曲线（从左上到左下）
    path.AddQuadCurveToPoint(
        leftX + width * 0.2, y,  // 控制点
        leftX, bottomY           // 终点（底部左侧）
    );

    // 第二条曲线：右侧下半部分大曲度曲线（从左下到右中）
    path.AddQuadCurveToPoint(
        leftX + width * 0.8, bottomY - height * 0.2,  // 控制点
        rightX, y                                     // 终点（右侧中心）
    );

    // 第三条曲线：右侧上半部分大曲度曲线（从右中到右上）
    path.AddQuadCurveToPoint(
        leftX + width * 0.8, topY + height * 0.2,  // 控制点
        leftX, topY                                // 终点（顶部左侧）
    );

    // 闭合路径
    path.CloseSubpath();

    // 绘制门主体
    gc->StrokePath(path);

    // 绘制输出端的小圆圈（表示取反）
    double circleCenterX = rightX + circleRadius; // 圆圈中心在门右侧稍微靠外
    wxGraphicsPath circlePath = gc->CreatePath();
    circlePath.AddCircle(circleCenterX, y, circleRadius);
    gc->StrokePath(circlePath);

    // 输入线（两条，从左侧接入）
    gc->StrokeLine(leftX - 20, y - 10, leftX + 3, y - 10);
    gc->StrokeLine(leftX - 20, y + 10, leftX + 3, y + 10);

    // 输出线（从小圆圈右侧延伸）
    gc->StrokeLine(circleCenterX + circleRadius, y, circleCenterX + circleRadius + 20, y);
}

void ComponentXOr::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 40;        // 门宽度
    double height = 40;       // 门高度

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    wxGraphicsPath path = gc->CreatePath();

    // 从顶部左侧开始
    path.MoveToPoint(leftX, topY);

    // 第一条曲线：左侧小曲度曲线（从左上到左下）
    path.AddQuadCurveToPoint(
        leftX + width * 0.2, y,  // 控制点
        leftX, bottomY           // 终点（底部左侧）
    );

    // 第二条曲线：右侧下半部分大曲度曲线（从左下到右中）
    path.AddQuadCurveToPoint(
        leftX + width * 0.8, bottomY - height * 0.2,  // 控制点
        rightX, y                                     // 终点（右侧中心）
    );

    // 第三条曲线：右侧上半部分大曲度曲线（从右中到右上）
    path.AddQuadCurveToPoint(
        leftX + width * 0.8, topY + height * 0.2,  // 控制点
        leftX, topY                                // 终点（顶部左侧）
    );

    // 闭合路径
    path.CloseSubpath();

    // 绘制门主体
    gc->StrokePath(path);

    // 绘制异或门特有的左侧弧线
    wxGraphicsPath arcPath = gc->CreatePath();
    double arcLeftX = leftX - 5; // 弧线在门主体的左侧
    arcPath.MoveToPoint(arcLeftX, topY);
    arcPath.AddQuadCurveToPoint(
        arcLeftX + width * 0.2, y,  // 控制点
        arcLeftX, bottomY  // 终点
    );
    gc->StrokePath(arcPath);

    // 输入线（两条，从左侧接入，连接到弧线左侧）
    gc->StrokeLine(arcLeftX - 12, y - 10, arcLeftX+2, y - 10);
    gc->StrokeLine(arcLeftX - 12, y + 10, arcLeftX+2, y + 10);

    // 输出线（从右侧中心引出）
    gc->StrokeLine(rightX, y, rightX + 20, y);
}

void ComponentXNOr::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 40;        // 门宽度
    double height = 40;       // 门高度

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标
    double circleRadius = 5;  // 小圆圈半径

    wxGraphicsPath path = gc->CreatePath();

    // 从顶部左侧开始
    path.MoveToPoint(leftX, topY);

    // 第一条曲线：左侧小曲度曲线（从左上到左下）
    path.AddQuadCurveToPoint(
        leftX + width * 0.2, y,  // 控制点
        leftX, bottomY           // 终点（底部左侧）
    );

    // 第二条曲线：右侧下半部分大曲度曲线（从左下到右中）
    path.AddQuadCurveToPoint(
        leftX + width * 0.8, bottomY - height * 0.2,  // 控制点
        rightX, y                                     // 终点（右侧中心）
    );

    // 第三条曲线：右侧上半部分大曲度曲线（从右中到右上）
    path.AddQuadCurveToPoint(
        leftX + width * 0.8, topY + height * 0.2,  // 控制点
        leftX, topY                                // 终点（顶部左侧）
    );

    // 闭合路径
    path.CloseSubpath();

    // 绘制门主体
    gc->StrokePath(path);

    // 绘制异或门特有的左侧弧线
    wxGraphicsPath arcPath = gc->CreatePath();
    double arcLeftX = leftX - 5; // 弧线在门主体的左侧
    arcPath.MoveToPoint(arcLeftX, topY);
    arcPath.AddQuadCurveToPoint(
        arcLeftX + width * 0.2, y,  // 控制点
        arcLeftX, bottomY  // 终点
    );
    gc->StrokePath(arcPath);

    // 绘制输出端的小圆圈（表示取反）
    double circleCenterX = rightX + circleRadius; // 圆圈中心在门右侧稍微靠外
    wxGraphicsPath circlePath = gc->CreatePath();
    circlePath.AddCircle(circleCenterX, y, circleRadius);
    gc->StrokePath(circlePath);

    // 输入线（两条，从左侧接入，连接到弧线左侧）
    gc->StrokeLine(arcLeftX - 12, y - 10, arcLeftX + 2, y - 10);
    gc->StrokeLine(arcLeftX - 12, y + 10, arcLeftX + 2, y + 10);

    // 输出线（从小圆圈右侧延伸）
    gc->StrokeLine(circleCenterX + circleRadius, y, circleCenterX + circleRadius + 20, y);
}

void ComponentOddParity::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 50;        // 门宽度
    double height = 50;       // 门高度

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    // 绘制矩形门体
    wxGraphicsPath path = gc->CreatePath();
    path.AddRectangle(leftX, topY, width, height);
    gc->StrokePath(path);

    // 在矩形中心绘制"奇"字或"ODD"标识
    gc->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD), wxColour(0, 0, 0));
    gc->DrawText("2k+1", x - 15, y - 8); // 或者使用 "奇" 

    // 输入线（多条，从左侧接入）
    // 可以根据需要调整输入线的数量和位置
    gc->StrokeLine(leftX - 20, y - 15, leftX, y - 15);
    gc->StrokeLine(leftX - 20, y + 15, leftX, y + 15);

    // 输出线（从右侧中心引出）
    gc->StrokeLine(rightX, y, rightX + 20, y);
}

void ComponentEvenParity::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 50;        // 门宽度
    double height = 50;       // 门高度

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    // 绘制矩形门体
    wxGraphicsPath path = gc->CreatePath();
    path.AddRectangle(leftX, topY, width, height);
    gc->StrokePath(path);

    // 在矩形中心绘制"偶"字或"EVEN"标识
    gc->SetFont(wxFont(12, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD), wxColour(0, 0, 0));
    gc->DrawText("2k", x - 15, y - 8); // 或者使用 "偶" 

    // 输入线（多条，从左侧接入）
    // 可以根据需要调整输入线的数量和位置
    gc->StrokeLine(leftX - 20, y - 15, leftX, y - 15);
    gc->StrokeLine(leftX - 20, y + 15, leftX, y + 15);

    // 输出线（从右侧中心引出）
    gc->StrokeLine(rightX, y, rightX + 20, y);
}

void ComponentControlledBuffer::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 30;        // 门宽度
    double height = 40;       // 门高度

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    wxGraphicsPath path = gc->CreatePath();

    // 绘制三角形形状（缓冲门的标准表示）
    path.MoveToPoint(leftX, topY);        // 左上角
    path.AddLineToPoint(rightX, y);       // 右侧中心
    path.AddLineToPoint(leftX, bottomY);  // 左下角
    path.CloseSubpath();                  // 闭合三角形

    // 绘制门主体
    gc->StrokePath(path);

    // 绘制控制线（从顶部接入）
    double controlY = topY - 10; // 控制线在门上方
    gc->StrokeLine(x, controlY+20, x, controlY);

    // 在控制线末端绘制小三角形或箭头表示控制
    wxGraphicsPath controlPath = gc->CreatePath();
    controlPath.MoveToPoint(x, controlY);
    controlPath.AddLineToPoint(x - 5, controlY - 3);
    controlPath.AddLineToPoint(x - 5, controlY + 3);
    controlPath.CloseSubpath();
   

    // 输入线（从左侧中心接入）
    gc->StrokeLine(leftX - 20, y, leftX, y);

    // 输出线（从右侧中心引出）
    gc->StrokeLine(rightX, y, rightX + 20, y);
}

void ComponentControlledInvertor::drawSelf(wxGraphicsContext* gc) const {
    double x = GetStart().x;
    double y = GetStart().y;

    double width = 30;        // 门宽度
    double height = 40;       // 门高度
    double circleRadius = 5;  // 小圆圈半径

    // 关键点坐标计算
    double leftX = x - width / 2;     // 左侧边界
    double rightX = x + width / 2;    // 右侧边界
    double topY = y - height / 2;     // 顶部Y坐标
    double bottomY = y + height / 2;  // 底部Y坐标

    wxGraphicsPath path = gc->CreatePath();

    // 绘制三角形形状（与缓冲门相同）
    path.MoveToPoint(leftX, topY);        // 左上角
    path.AddLineToPoint(rightX, y);       // 右侧中心
    path.AddLineToPoint(leftX, bottomY);  // 左下角
    path.CloseSubpath();                  // 闭合三角形

    // 绘制门主体
    gc->StrokePath(path);

    // 绘制输出端的小圆圈（表示取反）
    double circleCenterX = rightX + circleRadius; // 圆圈中心在三角形右侧
    wxGraphicsPath circlePath = gc->CreatePath();
    circlePath.AddCircle(circleCenterX, y, circleRadius);
    gc->StrokePath(circlePath);

    // 输入线（从左侧中心接入）
    gc->StrokeLine(x - width - 20, y, leftX, y);

    // 输出线（从小圆圈右侧延伸）
    gc->StrokeLine(circleCenterX + circleRadius, y, circleCenterX + circleRadius + 20, y);
    // 绘制控制线（从顶部接入）
    double controlY =y - 30; // 控制线在门上方
    gc->StrokeLine(x, controlY + 20, x, controlY);
}
