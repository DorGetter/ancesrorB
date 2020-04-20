//
// Created by dor on 12/04/2020.
//
#include <iostream>
#include <string>
#pragma once
#define COUNT 10

using namespace std; 
namespace family{


    class Tree {
    public:
        struct Node* root;
        //constructors & destructors//
        Tree();
        ~Tree();
        explicit Tree(std::string name);
    public:
        //methods to achieve//
        Tree& addFather(std::string x, std::string x_father);
        Tree& addMother(std::string x, std::string x_mother);
        std::string relation(std::string x);
        std::string find(std::string x);
        void display();
        void remove(std::string x);



        // //my methods//
        void Add_Father(Node * r, std::string x, std::string x_father);
        void Add_Mother(Node * r, std::string x, std::string x_father);
        std::string search_relation(Node* r , std::string x);
        std::string relationStr_ToName(Node* r, std::string x);
        void print_tree(Node *root, int space);
        void remove_sub(Node *t, std::string name);
        void findbyname(std::string x);
        int SearchName(Node* r, std::string x);
        void freeALL(Node *temp);

        Tree &GetTree();
    };

    struct Node{

    public:
        //variables for node:
        //every vertex in the tree could have parents and children.
        std::string name;
        std::string relation;
        int relation_num;
        Node* Mom;
        Node* Dad;
        Node* son;
        //Used for find_relation function
        //default constructor ..
    public:
        Node(std:: string Name);
        Node();
    };

}
