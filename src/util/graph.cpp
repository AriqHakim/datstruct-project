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

    void addEdge(graph &head, pNode &pNew, Hari::pDayNode &hari)
    {
        pNode vertexList = hari->vertex;
        if (isEmpty(searchByKode(vertexList, pNew->data.kode)))
        {
            pNode temp = vertexList;
            while(temp != nullptr){
                pNode inGraph = searchByKode(head.adjacencyList, temp->data.kode);
                if(isEmpty(searchByKode(pNew->edge, temp->data.kode)) && isEmpty(searchByKode(temp->edge, pNew->data.kode))){
                    insertFirst(pNew->edge, createNode(temp->data));
                    insertFirst(inGraph->edge, createNode(pNew->data));
                    pNew->totaledge++;
                    inGraph->totaledge++;
                }
                temp = temp->next;
            }
            Hari::addVertex(hari, pNew);
        }
        else
        {
            return;
        }
    }

    void swapData(pNode &a, pNode &b){
        pNode temp = new Node;
        temp -> data = a->data;
        temp -> status = a->status;
        temp -> edge = a-> edge;
        temp ->totaledge = a -> totaledge;

        a -> data = b->data;
        a -> status = b->status;
        a -> edge = b-> edge;
        a ->totaledge = b -> totaledge;

        b -> data = temp -> data;
        b -> status = temp->status;
        b -> edge = temp -> edge;
        b ->totaledge = temp -> totaledge;
    }

    void sortGraph(graph &head){
        pNode temp = head.adjacencyList;
        while (!isEmpty(temp)) {
            pNode max = temp;
            pNode r = temp->next;
            while (!isEmpty(r)) {
                if (r->totaledge > max->totaledge)
                    max = r;
                r = r->next;
            }
            swapData(temp, max);
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
                     if (p->totaledge > biggest->totaledge && p->status.kelas == '0')
                     {
                         biggest = p;
                     }
                 });

        return biggest;
    }

    bool isColored(pNode p)
    {
        return p->status.colored;
    }

    bool isGraphColored(graph head)
    {
        for_each(head.adjacencyList, [](const pNode &p)
                 {
                     if (!p->status.colored)
                     {
                         return false;
                     }
                 });
        return true;
    }

    //Welsch-Powell algoorithm
    void colorIt(graph &head, char Class)
    {
        pNode temp = searchBiggestNotColored(head);
        temp->status.kelas = Class;
        for_each(head.adjacencyList, [&head, &temp, &Class](pNode &p)
                 {
                     pNode curr = searchByKode(temp->edge, p->data.kode);
                     if (isEmpty(curr) && !isColored(curr))
                     {
                         p->status.kelas = Class;
                     }
                 });
        if (true)
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
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->status.jadwal[0]
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->status.jadwal[1]
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->status.jadwal[2]
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->status.jadwal[3]
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->status.jadwal[4] 
                        << "| " << std::setw(7) <<std::setfill(' ') << std::left << p->status.kelas << "| \n";
                std::cout << "+" << std::setw(5) << std::setfill('-') << std::right 
                      << "+" << std::setw(17) << std::setfill('-') << std::right
                      << "+" << std::setw(17) << std::setfill('-') << std::right 
                      << "+" << std::setw(9) << std::setfill('-') << std::right 
                      << "+" << std::setw(9) << std::setfill('-') << std::right 
                      << "+" << std::setw(9) << std::setfill('-') << std::right 
                      << "+" << std::setw(9) << std::setfill('-') << std::right 
                      << "+" << std::setw(9) << std::setfill('-') << std::right 
                      << "+" << std::setw(10) << std::setfill('-') << std::right << "+\n";
                count++;
            });
        } else {
            std::cout << "Graph Kosong!\n";
        }
    }
} // nasmespace graph