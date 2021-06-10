// #pragma once
#include <string>
#include <windows.h>

struct Guru
{
    std::string kode;
    std::string nama;
};

struct Status{
    char jadwal[5];
    char kelas;
    bool colored;
};

Status inisiasiStatus(){
    Status s;
    for(int i = 0; i < 5; i++){
        s.jadwal[i] = '0';
    }
    s.kelas = '0';
    s.colored = false;
    return s;
}

struct Node
{
    Guru data;
    Status status;
    Node *edge;
    Node *next;
    int totaledge;
};
typedef Node *pNode;

pNode createNode(Guru data)
{
    pNode newNode = new Node;
    newNode->data = data;
    newNode->status = inisiasiStatus();
    newNode->edge = nullptr;
    newNode->next = nullptr;
    newNode->totaledge = 0;
    return newNode;
}

bool isEmpty(pNode head)
{
    return (head == nullptr) ? true : false;
}

void insertFirst(pNode &head, const pNode pNew)
{
    if (isEmpty(head))
    {
        head = pNew;
    }
    else
    {
        pNew->next = head;
        head = pNew;
    }
}

pNode searchByKode(pNode head, std::string target)
{
    if (isEmpty(head))
        return nullptr;
    pNode result = head;
    while (result != nullptr)
    {
        if (result->data.kode == target)
        {
            return result;
        }
        result = result->next;
    }
    return nullptr;
}

template <typename F>
void for_each(pNode head, F func)
{
    pNode curr = head;
    while (curr != nullptr)
    {
        func(curr);
        curr = curr->next;
    }
}