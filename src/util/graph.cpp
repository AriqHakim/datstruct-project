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

    graph inisiasiGraph()
    {
        graph g;
        g.adjacencyList = nullptr;
        return g;
    }

    void insertNode(graph &head, pNode pNew)
    {
        insertFirst(head.adjacencyList, pNew);
    }

    void addEdge(graph &head, pNode &pNew, Hari::pDayNode &hari)
    {
        pNode vertexList = hari->vertex;
        if (isEmpty(searchByKode(vertexList, pNew->data.kode)))
        {
            pNode temp = vertexList;
            while (temp != nullptr)
            {
                pNode inGraph = searchByKode(head.adjacencyList, temp->data.kode);
                if (isEmpty(searchByKode(pNew->edge, temp->data.kode)) && isEmpty(searchByKode(temp->edge, pNew->data.kode)))
                {
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

    void swapData(pNode &a, pNode &b)
    {
        pNode temp = new Node;
        temp->data = a->data;
        temp->status = a->status;
        temp->edge = a->edge;
        temp->totaledge = a->totaledge;

        a->data = b->data;
        a->status = b->status;
        a->edge = b->edge;
        a->totaledge = b->totaledge;

        b->data = temp->data;
        b->status = temp->status;
        b->edge = temp->edge;
        b->totaledge = temp->totaledge;
    }

    //sort berdasarkan jumlah edge (tetangga)
    void sortGraph(graph &head)
    {
        pNode temp = head.adjacencyList;
        while (!isEmpty(temp))
        {
            pNode max = temp;
            pNode r = temp->next;
            while (!isEmpty(r))
            {
                if (r->totaledge > max->totaledge)
                    max = r;
                r = r->next;
            }
            swapData(temp, max);
            temp = temp->next;
        }
    }

    bool isColored(pNode p)
    {
        return p->status.colored;
    }

    bool isGraphColored(graph head)
    {
        for_each(head.adjacencyList, [](pNode &p)
                 {
                     if (!isColored(p))
                         return false;
                 });
        return true;
    }

    void setUncolored(graph &head)
    {
        for_each(head.adjacencyList, [](pNode &p)
                 {
                     p->status.colored = false;
                     p->status.kelas = '0';
                 });
    }

    pNode searchBiggestNotColored(graph head)
    {
        if (isEmpty(head.adjacencyList))
            return nullptr;

        pNode biggest = head.adjacencyList;
        for_each(head.adjacencyList, [&biggest](const pNode &p)
                 {
                     if (p->totaledge > biggest->totaledge && !isColored(p))
                     {
                         biggest = p;
                     }
                 });

        return biggest;
    }

    //untuk digunakan dalam welsh powell algorithm
    bool inList(graph head, pNode listVisited, pNode target)
    {
        pNode inGraph = nullptr;
        pNode edge = nullptr;
        pNode temp = listVisited;
        while (!isEmpty(temp))
        {
            inGraph = searchByKode(head.adjacencyList, temp->data.kode);
            edge = searchByKode(inGraph->edge, target->data.kode);
            if (!isEmpty(edge))
                return true;
            temp = temp->next;
        }
        return false;
    }

    //Welsch-Powell algoorithm
    // void colorIt(graph &head, char Class)
    // {
    //     pNode biggest = searchBiggestNotColored(head);
    //     biggest->status.kelas = Class;
    //     biggest->status.colored = true;

    //     pNode visited = nullptr;
    //     visited = createNode(biggest->data);

    //     pNode temp = head.adjacencyList;
    //     while (!isEmpty(temp))
    //     {
    //         if (!inList(head, visited, temp) && !isColored(temp))
    //         {
    //             temp->status.kelas = Class;
    //             temp->status.colored = true;
    //             insertFirst(visited, createNode(temp->data));
    //         }
    //         temp = temp->next;
    //     }
    //     deleteList(visited);
    //     if (isGraphColored(head))
    //     {
    //         return;
    //     }
    //     else
    //     {
    //         colorIt(head, ++Class);
    //     }
    // }

    graph colorIt(graph head, char Class)
    {
        pNode biggest = searchBiggestNotColored(head);
        biggest->status.kelas = Class;
        biggest->status.colored = true;

        pNode visited = nullptr;
        visited = createNode(biggest->data);

        pNode temp = head.adjacencyList;
        while (!isEmpty(temp))
        {
            if (!inList(head, visited, temp) && !isColored(temp))
            {
                temp->status.kelas = Class;
                temp->status.colored = true;
                insertFirst(visited, createNode(temp->data));
            }
            temp = temp->next;
        }
        deleteList(visited);

        if (isGraphColored(head))
        {
            return head;
        }
        else
        {
            return colorIt(head, ++Class);
        }
    }

    void printGraph(graph head)
    {
        int count = 1;
        if (!isEmpty(head.adjacencyList))
        {
            for_each(head.adjacencyList, [&count](const pNode &p)
                     {
                         std::cout << "| " << std::setw(3) << std::setfill(' ') << std::left << count;
                         std::cout << "| " << std::setw(15) << std::setfill(' ') << std::left << p->data.nama
                                   << "| " << std::setw(15) << std::setfill(' ') << std::left << p->data.kode
                                   << "| " << std::setw(7) << std::setfill(' ') << std::left << p->status.jadwal[0]
                                   << "| " << std::setw(7) << std::setfill(' ') << std::left << p->status.jadwal[1]
                                   << "| " << std::setw(7) << std::setfill(' ') << std::left << p->status.jadwal[2]
                                   << "| " << std::setw(7) << std::setfill(' ') << std::left << p->status.jadwal[3]
                                   << "| " << std::setw(7) << std::setfill(' ') << std::left << p->status.jadwal[4]
                                   << "| " << std::setw(7) << std::setfill(' ') << std::left << p->status.kelas << "| \n";
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
        }
        else
        {
            std::cout << "Graph Kosong!\n";
        }
    }
} // namespace graph