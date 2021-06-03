#pragma once
#include <string>

struct Guru
{
    std::string kode;
    std::string nama;
    char status[5];
};

void inisiasiStatus(char arr[5]){
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