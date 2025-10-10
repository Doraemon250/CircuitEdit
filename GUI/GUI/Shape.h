#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>

enum class GateType {
    AND,
    OR,
    NOT
};

class Shape
{
protected:
    wxPoint startPos;
    wxPoint endPos;
    int Thickness;
    wxColour Color;
    wxColour brushColor;
    wxString ShapeType;
public:
    Shape() : Thickness(2), Color(*wxBLACK) {}
    virtual ~Shape() {}

    wxPoint GetStart() const { return startPos; }
    wxPoint GetEnd() const { return endPos; }
    int GetThickness() const { return Thickness; }
    wxColour GetColor() const { return Color; }
    wxColour GetBrushColor() const { return brushColor; }
    wxString GetType() const { return ShapeType; }

    virtual void drawSelf(wxGraphicsContext* gc) const = 0;
};

// 新增 LogicGate 父类
class LogicGate : public Shape
{
protected:
    GateType type;
public:
    LogicGate(const wxPoint& pos, GateType t) : Shape(), type(t)
    {
        startPos = pos;
    }
    GateType GetGateType() const { return type; }

    // 不实现 drawSelf，由具体门类实现
};

// 具体门类
class ComponentAnd : public LogicGate
{
public:
    ComponentAnd(const wxPoint& pos) : LogicGate(pos, GateType::AND) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentNot : public LogicGate
{
public:
    ComponentNot(const wxPoint& pos) : LogicGate(pos, GateType::NOT) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentOr : public LogicGate
{
public:
    ComponentOr(const wxPoint& pos) : LogicGate(pos, GateType::OR) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};




class Line : public Shape
{

public:
    Line(const wxPoint& start, const wxPoint& end) : Shape()
    {
        this->startPos = start; this->endPos = end;
    }
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};