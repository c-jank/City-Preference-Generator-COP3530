#include <vector>
#include "maxHeap.h"
#include <SFML/graphics.hpp>
#pragma once


using namespace std;


class SplayTree {
   struct Node {
       string name;
       string state;
       int population;
       double altitude;
       double score;
       Node *left, *right;


       Node(cityData c) {
           left = nullptr;
           right = nullptr;
           name = c.name;
           state = c.state;
           population = c.population;
           altitude = c.altitude;
           score = c.score;
       }
   };


   Node *NewNode(cityData c) {
       Node *node = new Node(c);
       return node;
   }


   Node *LeftRotate(Node *old) {
       Node* replacement = old->right;
       old->right = replacement->left;
       replacement->left = old;
       return replacement;
   }


   Node *RightRotate(Node *old) {
       Node* replacement = old->left;
       old->left = replacement->right;
       replacement->right = old;
       return replacement;
   }


   Node* Splay(Node* root, double score) {
       if (root == nullptr) {
           return root;
       }
       if (root->score < score) {
           if (root->right == nullptr)
               return root;
           if (root->right->score > score) {
               root->right->left = Splay(root->right->left, score);
               if (root->right->left != nullptr)
                   root->right = RightRotate(root->right);
           }
           else if (root->right->score < score) {
               root->right->right = Splay(root->right->right, score);
               root = LeftRotate(root);
           }
           return (root->right == nullptr) ? root : LeftRotate(root);
       }
       else {
           if (root->left == nullptr) {
               return root;
           }
           if (root->left->score > score) {
               root->left->left = Splay(root->left->left, score);
               root = RightRotate(root);
           }
           else if (root->left->score < score) {
               root->left->right = Splay(root->left->right, score);
               if (root->left->right != nullptr)
                   root->left = LeftRotate(root->left);
           }
           return (root->left == nullptr) ? root : RightRotate(root);
       }
   }
public:
   Node* Insert(Node* root, cityData c) {
       if (root == nullptr) {
           return NewNode(c);
       }
       root = Splay(root, c.score);
       Node* new_node = NewNode(c);
       if (root->score < c.score) {
           new_node->left = root;
           new_node->right = root->right;
           root->right = nullptr;
       }
       else {
           new_node->right = root;
           new_node->left = root->left;
           root->left = nullptr;
       }
       return new_node;
   }


   vector<Node*> InOrder(Node* root, vector<Node*> &nodes, int results) {
       if (root != nullptr && nodes.size() < results) {
           InOrder(root->right, nodes, results);
           nodes.push_back(root);
           InOrder(root->left, nodes, results);
       }
       return nodes;
   }


   string PrintNames(int results) {
       vector<Node*> nodes;
       string s;
       nodes = InOrder(this->root, nodes, results);
       for (unsigned long int i = 0; i < results; i++) {
           s += to_string(i + 1) + ". " + nodes[i]->name + " | "+nodes[i]->state+" | " +"Pop: "+ to_string(nodes[i]->population)+" | "+"Alt: "+to_string(nodes[i]->altitude) + "\n";
       }
       return s;
   }






   Node* root;
   int size;
   SplayTree() {
       root = nullptr;
       size = 0;
   }
   void SetResults(int results) {
       size = results;
   }
};