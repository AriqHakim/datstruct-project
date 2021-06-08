#include "jadwal.cpp"
#include <functional>
#include <iostream>
#include <iomanip>

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

    void insertNode(graph& head, pNode pNew)
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
                         insertFirst(pNew->edge, createNode(p->data));
                         insertFirst(p->edge, createNode(pNew->data));
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

    void swapDdata(pNode &a, pNode &b){
        pNode temp = new Node;
        temp -> data = a->data;
        temp -> edge = a-> edge;
        temp ->totaledge = a -> totaledge;

        a -> data = b->data;
        a -> edge = b-> edge;
        a ->totaledge = b -> totaledge;

        b -> data = a->data;
        b -> edge = a-> edge;
        b ->totaledge = a -> totaledge;
    }

    void sortGraph(graph &head){
        pNode temp = head.adjacencyList;
        while (temp) {
            pNode max = temp;
            pNode r = temp->next;
            while (r) {
            if (max->totaledge > r->totaledge)
                max = r;
            r = r->next;
            }
            swapDdata(temp, max);
            temp = temp->next;
        }
    }

    pNode searchBiggestNotColored(graph head)
    {
        if (isEmpty(head.adjacencyList))
            return nullptr;

        pNode biggest = head.adjacencyList;
        for_each(head.adjacencyList, [&biggest](const pNode &p)
                 {
                     if (p->totaledge > biggest->totaledge && p->data.kelas == '0')
                     {
                         biggest = p;
                     }
                 });

        return biggest;
    }

    bool isColored(pNode p)
    {
        return (p->data.kelas == '0') ? false : true;
    }

    bool isGraphColored(graph head)
    {
        for_each(head.adjacencyList, [](const pNode &p)
                 {
                     if (p->data.kelas == '0')
                     {
                         return false;
                     }
                 });
        return true;
    }

    //Welsch-Powell algoorithm
    void colorIt(graph &head, char &Class)
    {
        pNode temp = searchBiggestNotColored(head);
        temp->data.kelas = Class;
        //Class++;
        for_each(head.adjacencyList, [&head, &temp, &Class](const pNode &p)
                 {
                     pNode curr = searchByKode(temp->edge, p->data.kode);
                     if (isEmpty(curr) && !isColored(curr))
                     {
                         p->data.kelas = Class;
                     }
                 });
        if (isGraphColored(head))
        {
            return;
        }
        else
        {
            Class++;
            colorIt(head, Class);
        }
    }

    void printGraph(graph head){
        int count = 1;
        if(!isEmpty(head.adjacencyList)){
            for_each(head.adjacencyList, [&count](const pNode &p){
                std::cout << "| " << std::setw(3) << std::setfill(' ')<<std::left << count ;
                std::cout << "| "<< std::setw(15) <<std::setfill(' ') << std::left << p->data.nama
                        << "| " << std::setw(15) <<std::setfill(' ') << std::left << p->data.kode
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[0]
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[1]
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[2]
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[3]
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.status[4] 
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->data.kelas << "| \n";
                count++;
            });
        } else {
            std::cout << "Graph Kosong!\n";
        }
    }
} // nasmespace graph