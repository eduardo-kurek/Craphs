#pragma once

#include <cstdint>
#include <forward_list>
#include "graphs/imp/GraphImp.h"
#include "edges/IEdge.h"
#include "utils/IPrintable.h"

template <EdgeType T>
class IGraph : public IPrintable {

private:
    bool IsValidVertex(uint32_t v) const;

protected:
    const uint32_t vertices;
    uint32_t edges;
    GraphImp<T>* graphImp;

    explicit IGraph(uint32_t vertices, GraphImp<T>* graphImp) : vertices(vertices), edges(0), graphImp(graphImp){}
    virtual ~IGraph() = default;

public:
    uint32_t V() const;
    uint32_t E() const;
    uint32_t Degree(uint32_t v) const;
    uint32_t MaxDegree() const;
    double AverageDegree() const;
    void CheckVertex(uint32_t v) const;
    const std::forward_list<T>& Adj(uint32_t v) const;
    std::ostream& Print(std::ostream& stream) const override;
    virtual void AddEdge(T&& edge) = 0;
    virtual bool IsConnected(uint32_t v, uint32_t w) const = 0;

};