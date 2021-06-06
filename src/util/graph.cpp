#include "jadwal.cpp"
#include <functional>
#include <iostream>

namespace Graph
{
    struct graph
    {
        pNode adjacencyList;
    };

    graph inisiasiGraph(){
        graph g;
        g.adjacencyList = nullptr;
        return g;
    }

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

    bool isColored(pNode p)
    {
        return (p->data.color == 7) ? false : true;
    }

    bool isGraphColored(graph head)
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
        //firstColor++;
        for_each(head.adjacencyList, [&head, &temp, &firstColor](const pNode &p)
                 {
                     pNode curr = searchByKode(temp->edge, p->data.kode);
                     if (isEmpty(curr) && !isColored(curr))
                     {
                         p->data.color = firstColor;
                     }
                 });
        if (isGraphColored(head))
        {
            return;
        }
        else
        {
            firstColor++;
            colorIt(head, firstColor);
        }
    }

    void printGraph(graph head){
        int count = 1;
        for_each(head.adjacencyList, [&count](const pNode &p){
             std::cout << "| " << std::setw(3) << std::setfill(' ')<<std::left << count << "| ";
             changeColor(p->data.color);
             std::cout << std::setw(15) <<std::setfill(' ') << std::left << p->data.nama;
             changeColor(7);
             std::cout << "| " << std::setw(15) <<std::setfill(' ') << std::left << p->data.kode
                    << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[0]
                    << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[1]
                    << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[2]
                    << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[3]
                    << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[4] << "| \n";
            count++;
        });
    }
} // nasmespace graph