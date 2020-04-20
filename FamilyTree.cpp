//
// Created by dor on 12/04/2020.
//

#include "FamilyTree.hpp"
#include <iostream>
#include <string>

#define COUNT 10

using namespace family;
struct Mexception : std::exception {
    const char* what() const throw() {
        const char* ex = "No Such Relation In Tree";
        return ex;
    }
};
//default constructor- NODE//
Node::Node() {}
//creating node implementation//
Node::Node(std::string Name) {
    name = Name;
    Mom = NULL;
    Dad = NULL;
    son = NULL;
}

/*class tree constructor -
need to have root pointer to NULL
*/
Tree::Tree() {
    Node* t_root;
    root = t_root;
}
/*class tree destructor -
need to free all memory (all nodes) in the tree
*/
Tree::~Tree() {
    freeALL(root);
}
/*tree constructor-
 * using name for the root
*/
Tree::Tree(const std::string n){
    Node *t_root;
    t_root = new Node(n);
    t_root->relation="me";
    t_root->relation_num=0;
    t_root->Mom=NULL;    t_root->Dad=NULL;    t_root->son=NULL;
    root = t_root;
}

/*
    adding father to a person name in the tree.

*/
Tree& Tree::addFather(std::string x, std::string x_father) {
    Node * root_clone;
    root_clone = root;
    findbyname(x);
    Add_Father(root_clone,x,x_father);
    Tree& tree = *this;

    return tree;
}

/*
    recursive adding father to a node in the tree.
*/
void Tree::Add_Father(Node * r, std::string x, std::string x_father){
//we reached the node to add father to.
    if(r->name==x){
        if(r->Dad == NULL){

            Node* new_dad = new Node(x_father);
            r->Dad = new_dad;
            new_dad->son = r;
            new_dad->relation_num = r->relation_num +1;

            if(r->relation_num==0){
                new_dad->relation = "father";
            }

            if(r->relation_num==1){
                new_dad->relation = "grandfather";
            }

            if(r->relation_num > 1){
                int i;
                int j= new_dad->relation_num -2;
                new_dad->relation="";
                for(i=0; i<j; i++){
                    new_dad->relation +="great-";
                }
                new_dad->relation +="grandfather";
            }
            return;
        } else {
            throw "Father allready exist";
        }

    }
    if(r->Dad !=NULL){Add_Father(r->Dad,x,x_father);}
    if(r->Mom !=NULL){Add_Father(r->Mom,x,x_father);}
}


Tree &Tree::addMother(std::string x, std::string x_mother) {
    Node * root_clone;
    root_clone = root;
    findbyname(x);
    Add_Mother(root_clone,x,x_mother);
    Tree& tree = *this;

    return tree;
}
/*
    recursive adding father to a node in the tree.
*/
void Tree::Add_Mother(Node * r, std::string x,std::string x_mother){
//we reached the node to add father to.
    if(r->name==x){
        if(r->Mom == NULL){

            Node* new_mom = new Node(x_mother);
            r->Mom = new_mom;
            new_mom->son = r;
            new_mom->relation_num = r->relation_num +1;

            if(r->relation_num==0){
                new_mom->relation = "mother";
            }

            if(r->relation_num==1){
                new_mom->relation = "grandmother";
            }

            if(r->relation_num > 1){
                int i;
                int j= new_mom->relation_num -2;
                new_mom->relation="";
                for(i=0; i<j; i++){
                    new_mom->relation +="great-";
                }
                new_mom->relation +="grandmother";
            }


            return;
        }else {
            throw "Mother allredy exist";
        }

    }
    if(r->Dad !=NULL){Add_Mother(r->Dad,x,x_mother);}
    if(r->Mom !=NULL){Add_Mother(r->Mom,x,x_mother);}
    return;
}


std::string Tree::relation(std::string x) {

    Node* r = root;
    std::string result;
    result =  search_relation(r,x);
    if (result == "")
        result = "unrelated";

    return result;
}

/*
    recursivly find the name to seek relation of.
    returns the relation string.
*/
std::string Tree::search_relation(Node*r ,std::string x){
    std::string s = r->name;
    std::string res="";

    if(r->name == x) {
        res = "";
        res= r->relation;
        return res;
    }

    else if(r->Dad==NULL && r->Mom!=NULL) return search_relation(r->Mom,x);
    else if(r->Dad!=NULL && r->Mom==NULL) return search_relation(r->Dad,x);

    else if(r->Dad!=NULL && r->Mom!=NULL){
        std::string a="";std::string b="";
        a = search_relation(r->Dad,x);
        b = search_relation(r->Mom,x);
        if (a!=""){
            return a;
        }else {
        return b;
        }
    }
    return "";
}

//given name search in tree if exist//
void Tree::findbyname(std::string x) {

    Node* t_root ;
    t_root= root;
    int result;
    result= SearchName(t_root,x);
    if (result==0)
        throw "doesnt in tree";
}

int Tree::SearchName(Node *r, std::string x) {
    std::string f = r->relation;
    if(r->name == x){
        return 1;
    }
    else if(r->Dad==NULL && r->Mom!=NULL) return SearchName(r->Mom,x);
    else if(r->Dad!=NULL && r->Mom==NULL) return SearchName(r->Dad,x);
    else if(r->Dad!=NULL && r->Mom!=NULL){
        int a=0;int b=0;
        a = SearchName(r->Dad,x);
        b = SearchName(r->Mom,x);
        if (a!=0){
            return a;
        }else {
            return b;
        }
    }
    return 0;
}

//input ex. great-great-grandfather//
std::string Tree::find(std::string x){
    Node* t_root ;
    t_root= root;
    std::string result;
    result= relationStr_ToName(t_root,x);
    if (result=="")
        throw "cant find";

    return result;
}

std::string Tree::relationStr_ToName(Node* r, std::string x){
    std::string f = r->relation;
    if(r->relation == x){
        return r->name;
    }
    else if(r->Dad==NULL && r->Mom!=NULL) return relationStr_ToName(r->Mom,x);
    else if(r->Dad!=NULL && r->Mom==NULL) return relationStr_ToName(r->Dad,x);
    else if(r->Dad!=NULL && r->Mom!=NULL){
        std::string a="";std::string b="";
        a = relationStr_ToName(r->Dad,x);
        b = relationStr_ToName(r->Mom,x);
        if (a!=""){
            return a;
        }else {
            return b;
        }
    }
    return "" ;
}

void Tree::display() {
    Node *r = root;
    if(r == NULL){
        std::cout << "Tree is empty" << std::endl;
    }
    //send to printing//
    print_tree(r,0);
}
//printing the tree recursivly//
void Tree::print_tree(Node *r, int space){
    // Base case
    if (r == NULL)
        return;
    //incharge of spacing lelveling//
    space += COUNT;

    print_tree(r->Mom, space);

    // Print current node after space
    // count
    std::cout<<std::endl;
    for (int i = COUNT; i < space; i++) {
        std::cout<<" ";
    }
    std::cout<<r->name<<"\n";

    // Process left child
    print_tree(r->Dad, space);
}

void Tree::freeALL(Node* temp){
    if(temp->Mom!=NULL) freeALL(temp->Mom);
    if(temp->Dad!=NULL) freeALL(temp->Dad);
    if(temp->Dad==NULL && temp->Mom==NULL) {
        delete(temp);
    }
}

void Tree::remove_sub(Node* t,std::string name){
    std::string d = t->name;
    if(t->name == name) {
        if(t->Dad!=NULL) freeALL(t->Dad);
        if(t->Mom!=NULL) freeALL(t->Mom);
        if (t->son->Dad == t) {
            t->son->Dad = NULL;
        }
        if (t->son->Mom == t) {
            t->son->Mom = NULL;
        }
        delete (t);

        return;
    }
    else if(t->Dad !=NULL && SearchName(t->Dad,name)!=0){
        remove_sub(t->Dad,name);
    }
    else if(t->Mom!=NULL && SearchName(t->Mom,name)!=0){
        remove_sub(t->Mom,name);
    }
    else{
        return;
    }
//    else if(t->Dad!=NULL && t->Dad->name==name){
//        if(t->Dad->Dad!=NULL) freeALL(t->Dad);
//        delete(t->Dad);
//        t->Dad=NULL;
//        return;
//    }
//    else if(t->Mom!=NULL && t->Mom->name==name){
//        if(t->Mom->Mom!=NULL) freeALL(t->Mom);
//        delete(t->Mom);
//        t->Mom=NULL;
//        return;
//    }
//    else if (t->Dad != NULL && t->Mom !=NULL){
//         remove_sub(t->Dad,name);
//         remove_sub(t->Mom,name);
//    }
//
//    else{
//        return;
//    }
}

void Tree::remove(std::string x) {
    findbyname(x);
    if(root->name == x){
        throw "cant delete root";
        return;
    }
    remove_sub(root,x);
//    if(root->Dad!=NULL && root->Dad->name==x)  remove_sub(root->Dad,x);
//    else if(root->Mom!=NULL && root->Mom->name==x)  remove_sub(root->Mom,x);
//    else if(root->name ==x){
//        throw "cant remove root";
//    }
//    else {
//        if(root->Mom!=NULL) remove_sub(root->Mom,x);
//        if(root->Dad!=NULL) remove_sub(root->Dad,x);
//    }
}

Tree & Tree::GetTree() {
    return *this;
}
