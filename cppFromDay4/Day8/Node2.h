#ifndef NODE2_H
#define NODE2_H

#include <iostream>
#include <map>
using namespace std;

class Node2 {

    string name;
    Node2* left;
    Node2* right;
    bool wasVisited;

    friend ostream& operator<<(ostream& os, const Node2& node);

    static void createNodes(map<string, Node2>& nodeMap, vector<string> lines);
    static void linkNodes(map<string, Node2>& nodeMap, vector<string> lines);

public:
    Node2() : wasVisited(false) {}
    Node2(string name) : name(name), left(nullptr), right(nullptr), wasVisited(false) {}
    static map<string, Node2> readNodeMap(const vector<string>& lines);
    static vector<Node2*> findStartingNodes(const map<string, Node2>& nodeMap);
    int findStepsToZ(map<string, Node2>& nodeMap);
    static int findStepsFromVectorToZ(vector<Node2*> startingNodes);
    Node2* followDirection(const char direction) const;
    string getName() { return this->name; }

};

#endif