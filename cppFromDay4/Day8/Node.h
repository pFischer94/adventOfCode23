#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <map>
using namespace std;

class Node {

    string name;
    int stepsToZ;

    friend bool operator<(const Node& node1, const Node& node2);
    friend ostream& operator<<(ostream& os, const Node& node);

public:
    Node() : stepsToZ(-1) {}
    Node(string name) : name(name), stepsToZ(-1) {}
    static map<Node, pair<Node, Node>> readNodes(const vector<string>& lines);
    static vector<Node> findStartingNodes(map<Node, pair<Node, Node>>& nodesMap);
    static bool allEndOnZ(const vector<Node>& currNodes);
    int recordStepsToZ(map<Node, pair<Node, Node>>& nodesMap);
    static void printMap(const map<Node, pair<Node, Node>>& nodesMap);
    static void printVector(const vector<Node>& nodes);
    Node followDirection(const map<Node, pair<Node, Node>>& nodesMap, const char& direction) const;
    string getName() const;
    int getStepsToZ() const;

};

#endif