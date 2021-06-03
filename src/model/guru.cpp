#pragma once
#include <string>

struct Guru
{
    std::string kode;
    std::string nama;
    char status[5];
};

void inisiasiStatus(char arr[5])
{
    char init[] = {'0', '0', '0', '0', '0'};
    arr = init;
}

struct Node
{
    Guru data;
    Node *edge;
    Node *next;
};
typedef Node *pNode;

pNode createNode(Guru data)
{
    pNode newNode = new Node;
    newNode->data = data;
    newNode->edge = nullptr;
    newNode->next = nullptr;
    return newNode;
}

bool isEmpty(pNode head)
{
    return (head = nullptr) ? true : false;
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

template <typename F> void for_each (pNode head, F func){
    pNode curr = head;
    while (curr != nullptr){
        func(curr -> data);
        curr = curr -> next;
    }
}