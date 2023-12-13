#include "Node.h"

map<Node, pair<Node, Node>> Node::readNodes(const vector<string> &lines) {
    map<Node, pair<Node, Node>> nodesMap;
    string line;

    // create Nodes
    for (int index = 2; index < lines.size(); index++) {
        line = lines[index];
        char* nameStr = strtok((char*) line.c_str(), " ");
        nodesMap[Node(nameStr)];
    }

    // link Nodes
    for (int index = 2; index < lines.size(); index++) {
        line = lines[index];

        char* nameStr = strtok((char*) line.c_str(), " ");
        Node name = Node(nameStr);
        strtok(NULL, " ");

        string leftStr = strtok(NULL, " ");
        leftStr = leftStr.substr(1, 3);
        Node left(leftStr);

        string rightStr = strtok(NULL, " ");
        rightStr = rightStr.substr(0, 3);
        Node right(rightStr);

        nodesMap[name].first = left;
        nodesMap[name].second = right;
    }

    return nodesMap;
}

vector<Node> Node::findStartingNodes(map<Node, pair<Node, Node>> &nodesMap) {
    vector<Node> startingNodes;
    for (auto it : nodesMap) {
        if (it.first.getName().ends_with('A')) {
            startingNodes.emplace_back(it.first);
        }
    }
    return startingNodes;
}

bool Node::allEndOnZ(const vector<Node> &currNodes) {
    for (Node node : currNodes) {
        if (!node.getName().ends_with('Z')) {
            return false;
        }
    }
    return true;
}

int Node::recordStepsToZ(map<Node, pair<Node, Node>>& nodesMap) {
    if (this->name.ends_with("Z")) {
        this->stepsToZ = 0;
        return this->stepsToZ + 1;
    }
    if (this->stepsToZ == -2) {
        return -2;
    }
    if (this->stepsToZ > -1) {
        return this->stepsToZ + 1;
    }

    // this->name = "_" + this->name;
    this->stepsToZ = -2;
    int stepsLeft = nodesMap[*this].first.recordStepsToZ(nodesMap);
    int stepsRight = nodesMap[*this].second.recordStepsToZ(nodesMap);
    int minSteps = min(stepsLeft < 0 ? 20000 : stepsLeft, stepsRight < 0 ? 20000 : stepsRight);
    this->stepsToZ = minSteps;
    return this->stepsToZ + 1;
}

void Node::printMap(const map<Node, pair<Node, Node>> &nodesMap) {
    for (auto it : nodesMap) {
        cout << it.first << endl;
    }
}

void Node::printVector(const vector<Node> &nodes) {
    string separator = "================================";
    cout << separator << endl;
    for (const Node& node : nodes) {
        cout << node << endl;
    }
    cout << separator << endl;
}

Node Node::followDirection(const map<Node, pair<Node, Node>> &nodesMap, const char &direction) const {
    if (direction == 'L') {
        return ((map<Node, pair<Node, Node>>) nodesMap)[*this].first;
    } else if (direction == 'R') {
        return ((map<Node, pair<Node, Node>>) nodesMap)[*this].second;
    } else {
        throw runtime_error("direction could not be followed");
    }
}

string Node::getName() const {
    return this->name;
}

int Node::getStepsToZ() const {
    return this->stepsToZ;
}

bool operator<(const Node &node1, const Node &node2) {
    return node1.name < node2.name;
}

ostream &operator<<(ostream &os, const Node &node) {
    os << "Node [ name: " << node.name << ", stepsToZ: " << node.stepsToZ << " ]";
    return os;
}
