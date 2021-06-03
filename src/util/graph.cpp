#include "jadwal.cpp"
#include <functional>

namespace Graph
{
    struct graph
    {
        pNode adjacencyList;
    };

    void insertNode(graph head, pNode pNew)
    {
        insertFirst(head.adjacencyList, pNew);
    }

    void addEdge(graph &head, pNode pNew, Hari::pDayNode &hari)
    {
        pNode curr = hari->vertex;
        if (isEmpty(searchByKode(hari->vertex, pNew->data.kode)))
        {
            for_each(hari->vertex, [&pNew](const pNode &p)
                     {
                         insertFirst(pNew->edge, p);
                         insertFirst(p->edge, pNew);
                     });
            Hari::addVertex(hari, pNew);
        }
        else
        {
            return;
        }
    }
} // nasmespace graph