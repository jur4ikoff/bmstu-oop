#pragma once
#include "TransformAction.h"
#include "Edge.h"
#include "Point.h"
#include "ModelStructure.h"
#include <vector>

class ListModelStructure : public ModelStructure
{
public:
    ListModelStructure();

    ~ListModelStructure() = default;
    virtual void Transform(const TransformAction &action);
    virtual std::shared_ptr<ModelStructure> Clone() const;

    virtual std::vector<Point> GetPoints() const;
    virtual std::vector<Edge> GetEdges() const;
    virtual std::vector<Face> GetFaces() const;
    virtual void AddPoint(const Point &point);
    virtual void AddEdge(const Edge &edge);
    virtual void AddFace(const Face &face);
    virtual void ClearPoints();
    virtual Point GetCenter() const;
    virtual void SetCenter(const Point &center);

protected:
    Point _center;

    std::vector<Point> _points;
    std::vector<Edge> _edges;
    std::vector<Face> _faces;
};
