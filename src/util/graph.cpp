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

    void deleteGraph(graph &head)
    {
        pNode it = head.adjacencyList;
        while (it != nullptr)
        {
            pNode temp = it;
            it = temp->next;
            deleteList(temp->edge);
            delete temp;
        }
    }

    void insertNode(graph &head, pNode pNew)
    {
        insertFirst(head.adjacencyList, pNew);
    }

    //untuk menambah edge sesuai hari yang dipilih
    void addEdge(graph &head, pNode &pNew, Hari::pDayNode &hari)
    {
        pNode vertexList = hari->vertex;
        if (isEmpty(searchByKode(vertexList, pNew->data.kode)))
        {
            pNode temp = vertexList;
            while (temp != nullptr)
            {
                pNode inGraph = searchByKode(head.adjacencyList, temp->data.kode);
                if (isEmpty(searchByKode(pNew->edge, temp->data.kode)) && isEmpty(searchByKode(inGraph->edge, pNew->data.kode)))
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
            std::cout << "Hari sudah pernah dipilih!\n";
        }
    }

    //menukar data node
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

    void setUncolored(graph &head)
    {
        for_each(head.adjacencyList, [](pNode &p)
                 {
                     p->status.colored = false;
                     p->status.kelas = '0';
                 });
    }

    //Cek apakah node yang sedang diiterasi bertetangga dengan List node yang telah dikunjungi
    bool inList(graph head, pNode listVisited, pNode target)
    {
        pNode inGraph = nullptr;
        pNode edge = nullptr;
        pNode temp = listVisited; //untuk iterasi list yang telah dikunjungi/diwarnai
        while (!isEmpty(temp))
        {
            inGraph = searchByKode(head.adjacencyList, temp->data.kode);
            edge = searchByKode(inGraph->edge, target->data.kode);  //cari apakah temp bertetangga dengan node yang telah diwarnai
            if (!isEmpty(edge))                                     //jika bertetangga return true    
                return true;
            temp = temp->next;
        }
        return false;
    }

    //welch-powell algorithm
    graph colorIt(graph head, char Class)
    {
        pNode listColored = nullptr;
        pNode biggest = nullptr;
        pNode p = head.adjacencyList;
        while (!isEmpty(p))
        {
            //cek Node apakah sudah diwarnai apa belum
            if (!isColored(p))
            {
                //karena sudah di sort maka langsung diwarnai
                p->status.kelas = Class;
                p->status.colored = true;

                //masukkan kedalam list yang sudah diwarnai
                listColored = createNode(p->data);

                //temp digunakan untuk iterasi node selanjutnya hingga akhir
                pNode temp = p;
                while (!isEmpty(temp))
                {
                    //cek apakah temp bertetangga dengan vertex yang telah diberi warna
                    //jika tidak bertetangga dan belum diwarnai maka Node akan di warnai
                    if (!inList(head, listColored, temp) && !isColored(temp))
                    {
                        temp->status.kelas = Class;
                        temp->status.colored = true;

                        //masukkan node ke list yang telah di warnai
                        insertFirst(listColored, createNode(temp->data));
                    }
                    temp = temp->next;
                }

                Class++;
                deleteList(listColored);
            }
            p = p->next;
        }

        return head;
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
            std::cout << "Graph Kosong!\n\n";
        }
    }
} // namespace graph