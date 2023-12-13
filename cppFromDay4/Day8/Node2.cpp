#include "Node2.h"

void test() {
    cout << "test" << endl;
}

ostream &operator<<(ostream &os, const Node2 &node)
{
    os << "Node [ name: " << node.name 
        << ", left: " << node.left->name 
        << ", right: " << node.right->name
        << ", visited: " << (node.wasVisited ? "true" : "false") << " ]";
    return os;
}

void Node2::createNodes(map<string, Node2> &nodeMap, vector<string> lines)
{
    for (int i = 2; i < lines.size(); i++) {
        char* name = strtok((char*) lines[i].c_str(), " ");
        nodeMap[name] = Node2(name);
    }
}

void Node2::linkNodes(map<string, Node2> &nodeMap, vector<string> lines)
{
    for (int i = 2; i < lines.size(); i++) {
        char* name = strtok((char*) lines[i].c_str(), " ");
        strtok(NULL, " ");

        string leftStr = strtok(NULL, " ");
        string leftName = leftStr.substr(1, 3);
        nodeMap[name].left = &nodeMap[leftName];

        string rightStr = strtok(NULL, " ");
        string rightName = rightStr.substr(0, 3);
        nodeMap[name].right = &nodeMap[rightName];
    }
}

map<string, Node2> Node2::readNodeMap(const vector<string> &lines)
{
    map<string, Node2> nodeMap;

    createNodes(nodeMap, lines);
    linkNodes(nodeMap, lines);

    return nodeMap;
}

vector<Node2*> Node2::findStartingNodes(const map<string, Node2> &nodeMap)
{
    vector<Node2*> startingNodes;

    for (auto it : nodeMap) {
        string name = it.first;
        Node2* nodeP = (Node2*) &nodeMap.at(name);
        if (name.ends_with('A')) {
            startingNodes.emplace_back(nodeP);
        }
    }

    return startingNodes;
}

int Node2::findStepsToZ(map<string, Node2>& nodeMap)
{
    vector<Node2*> nextNodes;

    for (auto& it : nodeMap) {
        it.second.wasVisited = false;
    }

    if (this->name.ends_with("Z")) {
        return 0;
    } else {
        nextNodes.emplace_back(this->left);
        nextNodes.emplace_back(this->right);
    }

    int stepsFromNextNodesToZ = findStepsFromVectorToZ(nextNodes);
    return stepsFromNextNodesToZ + 1;
}

int Node2::findStepsFromVectorToZ(vector<Node2*> startingNodes)
{
    vector<Node2*> nextNodes;

    for (Node2* node : startingNodes) {
        if (node->wasVisited == true) {
            continue;
        }
        if (node->name.ends_with("Z")) {
            return 0;
        } else {
            node->wasVisited = -2;
            nextNodes.emplace_back(node->left);
            nextNodes.emplace_back(node->right);
        }
    }

    int stepsFromNextNodesToZ = findStepsFromVectorToZ(nextNodes);
    return stepsFromNextNodesToZ + 1;
}

Node2* Node2::followDirection(const char direction) const {
    if (direction == 'L') {
        return this->left;
    } else if (direction == 'R') {
        return this->right;
    } else {
        throw runtime_error("direction could not be followed");
    }
}
