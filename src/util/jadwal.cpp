// #pragma once
#include "../model/guru.cpp"
#include <iostream>

namespace Hari
{
    struct Day
    {
        std::string day;
    };

    struct DayNode
    {
        Day data;
        pNode vertex;
        DayNode *next;
    };
    typedef DayNode *pDayNode;

    pDayNode createDayNode(Day data)
    {
        pDayNode newNode = new DayNode;
        newNode->data = data;
        newNode->vertex = nullptr;
        newNode->next = nullptr;
        return newNode;
    }

    bool isDayEmpty(pDayNode head)
    {
        return (head == nullptr) ? true : false;
    }

    void insertDayFirst(pDayNode &head, const pDayNode pNew)
    {
        if (isDayEmpty(head))
        {
            head = pNew;
        }
        else
        {
            pNew->next = head;
            head = pNew;
        }
    }

    pDayNode inisiasiHari()
    {
        pDayNode head = nullptr;
        std::string jadwal[5] = {"Jumat", "Kamis", "Rabu", "Selasa", "Senin"};
        for (std::string s : jadwal)
        {
            insertDayFirst(head, createDayNode(Day{s}));
        }
        return head;
    }

    pDayNode searchByHari(pDayNode head, std::string target)
    {
        if (isDayEmpty(head))
            return nullptr;
        pDayNode result = head;
        while (result != nullptr)
        {
            if (result->data.day == target)
            {
                return result;
            }
            result = result->next;
        }
        return nullptr;
    }

    void addVertex(pDayNode &head, pNode pNew)
    {
        if (isEmpty(searchByKode(head->vertex, pNew->data.kode)))
        {
            insertFirst(head->vertex, createNode(pNew->data));
        }
        else
        {
            std::cout<<"addvertex gagal\n";
        }
    }

    template <typename F> void for_each (pDayNode head, F func){
        pDayNode curr = head;
        while (curr != nullptr){
            func(curr);
            curr = curr -> next;
        }
    }

    void setStatusSenin(pNode &head){
        head->status.jadwal[0] = '1';        
    }

    void setStatusSelasa(pNode &head){
         head->status.jadwal[1] = '1';
    }

    void setStatusRabu(pNode &head){
         head->status.jadwal[2] = '1';
    }

    void setStatusKamis(pNode &head){
         head->status.jadwal[3] = '1';
    }

    void setStatusJumat(pNode &head){
         head->status.jadwal[4] = '1';
    }
} // namespace hari