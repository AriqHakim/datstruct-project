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
        pNode vertexList = hari->vertex;
        if (isEmpty(searchByKode(vertexList, pNew->data.kode)))
        {
            for_each(vertexList, [&pNew](const pNode &p)
                     {
                         insertFirst(pNew->edge, p);
                         insertFirst(p->edge, pNew);
                         pNew->totaledge++;
                         p->totaledge++;
                     });
            Hari::addVertex(hari, pNew);
        }
        else
        {
            return;
        }
    }

    pNode searchBiggestNotColored(graph head)
    {
        if (isEmpty(head.adjacencyList))
            return nullptr;

        pNode biggest = head.adjacencyList;
        for_each(head.adjacencyList, [&biggest](const pNode &p)
                 {
                     if (p->totaledge > biggest->totaledge && p->data.color == 7)
                     {
                         biggest = p;
                     }
                 });

        return biggest;
    }

    bool isColored(graph head)
    {
        for_each(head.adjacencyList, [](const pNode &p)
                 {
                     if (p->data.color == 7)
                     {
                         return false;
                     }
                 });
        return true;
    }

    //Welsch-Powell algoorithm
    void colorIt(graph &head, int &firstColor)
    {
        pNode temp = searchBiggestNotColored(head);
        temp->data.color = firstColor;
        firstColor++;
        for_each(head.adjacencyList, [&temp, &firstColor](const pNode &p)
                 {
                     if (isEmpty(searchByKode(temp->edge, p->data.kode)))
                     {
                         p->data.color = firstColor;
                     }
                 });
        if (isColored(head))
        {
            return;
        }
        else
        {
            colorIt(head, firstColor);
        }
    }
} // nasmespace graph