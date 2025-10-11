#pragma once
#include <wx/wx.h>
#include <wx/graphics.h>

enum class GateType {
    AND,
    OR,
    NOT,
    BUFFER,
    NAND,
    NOR,
    XOR,
    XNOR,
    ODD_PARITY,
    EVEN_PARITY,
    CONTROLLED_BUFFER,
    CONTROLLED_INVERTOR
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
    virtual std::vector<wxPoint> GetIuputLocation(wxGraphicsContext* gc) const = 0;
    virtual wxPoint GetOutputLocation(wxGraphicsContext* gc) const = 0;

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

class ComponentBuffer : public LogicGate
{
public:
    ComponentBuffer(const wxPoint& pos) : LogicGate(pos, GateType::BUFFER) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentNAnd : public LogicGate
{
public:
    ComponentNAnd(const wxPoint& pos) : LogicGate(pos, GateType::NAND) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentNOr : public LogicGate
{
public:
    ComponentNOr(const wxPoint& pos) : LogicGate(pos, GateType::NOR) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentXOr : public LogicGate
{
public:
    ComponentXOr(const wxPoint& pos) : LogicGate(pos, GateType::XOR) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentXNOr : public LogicGate
{
public:
    ComponentXNOr(const wxPoint& pos) : LogicGate(pos, GateType::XNOR) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentOddParity : public LogicGate
{
public:
    ComponentOddParity(const wxPoint& pos) : LogicGate(pos, GateType::ODD_PARITY) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentEvenParity : public LogicGate
{
public:
    ComponentEvenParity(const wxPoint& pos) : LogicGate(pos, GateType::EVEN_PARITY) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentControlledBuffer : public LogicGate
{
public:
    ComponentControlledBuffer(const wxPoint& pos) : LogicGate(pos, GateType::CONTROLLED_BUFFER) {}
    virtual void drawSelf(wxGraphicsContext* gc) const override;
};

class ComponentControlledInvertor : public LogicGate
{
public:
    ComponentControlledInvertor(const wxPoint& pos) : LogicGate(pos, GateType::CONTROLLED_INVERTOR) {}
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