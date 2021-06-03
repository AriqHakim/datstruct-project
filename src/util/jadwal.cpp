#pragma once
#include "../model/guru.cpp"

namespace Hari{
    struct Day
    {
        std::string day;
    };

    struct DayNode
    {
        Day data;
        DayNode *vertex;
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

    bool isEmpty(pDayNode head){
        return (head = nullptr) ? true : false;
    }

    void insert_first (pDayNode& head, const pDayNode pNew){
        if(isEmpty(head)){
            head = pNew;
        } else {
            pNew -> next = head;
            head = pNew;
        }
    }

    pDayNode inisiasiHari(){
        pDayNode head = nullptr;
        std::string jadwal[5] = {"Jumat", "Kamis", "Rabu", "Selasa", "Senin"};
        for(std::string s : jadwal){
            insert_first(head, createDayNode(Day{s}));
        }
        return head;
    }
} // namespace hari