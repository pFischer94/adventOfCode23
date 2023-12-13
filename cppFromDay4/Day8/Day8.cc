#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Node.cpp"
#include "Node2.cpp"
#include "Calculations.cc"

int countStepsPart1(const vector<string>& lines);
// int countStepsPart2(map<Node, pair<Node, Node>>& nodesMap);
// long calculateLCM(const vector<int>& steps);
// int ggT(const vector<int>& steps);
// vector<int> getAllDividers(int num);
// bool vectorContains(const vector<int>& nums, int num);
int countStepsPart2b(const vector<string>& lines);

int main() {
    MethodFrame mF("Day8.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input8.txt").getLines();

    // int numSteps = countStepsPart1(lines);

    int numSteps = countStepsPart2b(lines);

    cout << endl << "numSteps:     " << numSteps << endl;

    mF.printEnd();
    return 0;
}

int countStepsPart2b(const vector<string>& lines) {
    map<string, Node2> nodeMap = Node2::readNodeMap(lines);
    vector<Node2*> startingNodes = Node2::findStartingNodes(nodeMap);
    vector<int> stepsFromStartingNodes;
    string instructions = lines[0];

    for (Node2* node : startingNodes) {
        Node2* currNode = node;
        int numSteps = 0;
        while (!currNode->getName().ends_with("Z")) {
            char direction = instructions[numSteps % instructions.size()];
            currNode = currNode->followDirection(direction);
            numSteps++;
        }
        stepsFromStartingNodes.emplace_back(numSteps);
    }

    long lowestCommonMultiple = lcmOfVector(stepsFromStartingNodes);
    cout << "lcm:      " << lowestCommonMultiple << endl;

    for (int i = 0; i < startingNodes.size(); i++) {
        cout << *startingNodes[i] << "      " << stepsFromStartingNodes[i] << endl;
    }

    int steps = 0;
    return steps;
}




















int countStepsPart1(const vector<string>& lines) {
    string instructions = lines[0];
    map<Node, pair<Node, Node>> nodesMap = Node::readNodes(lines);
    cout << "nodesMap      created" << endl;

    Node currNode = nodesMap.begin()->first;

    int numSteps = 0;
    while (currNode.getName() != "ZZZ") {
        char direction = instructions[numSteps % instructions.size()];
        currNode = currNode.followDirection(nodesMap, direction);
        numSteps++;
    }

    return numSteps;
}

// int countStepsPart2(map<Node, pair<Node, Node>>& nodesMap) {
//     vector<Node> startingNodes = Node::findStartingNodes(nodesMap);
//     cout << "startingNodes found" << endl;
//     Node::printVector(startingNodes);
//     cout << endl;

//     for (Node& node : startingNodes) {
//         node.recordStepsToZ(nodesMap);
//     }
//     cout << "stepsToZ recorded" << endl;
//     Node::printVector(startingNodes);
//     cout << endl;
//     Node::printMap(nodesMap);

//     vector<int> steps;
//     for (Node& node : startingNodes) {
//         steps.emplace_back(node.getStepsToZ());
//     }
//     int numSteps = calculateLCM(steps);

//     return numSteps;
// }

// long calculateLCM(const vector<int> &steps) {
//     long product = 1;
//     for (int step : steps) {
//         product *= step;
//     }
//     int gcd = ggT(steps);

//     return product / gcd;
// }

// int ggT(const vector<int> &steps) {
//     vector<vector<int>> teilerOfAll;
//     for (int step : steps) {
//         vector<int> teilerOfOne = getAllDividers(step);
//         teilerOfAll.emplace_back(teilerOfOne);
//     }

//     int ggT;
//     vector<int> teilerOfFirst = teilerOfAll[0];
//     for (int index = teilerOfFirst.size() - 1; index >= 1; index--) {
//         int teiler = teilerOfFirst[index];
//         for (vector<int> dividersOfOne : teilerOfAll) {
//             if (vectorContains(dividersOfOne, teiler)) {
//                 return teiler;
//             }
//         }
//     }
//     return 1;
// }

// vector<int> getAllDividers(int num) {
//     vector<int> teilerOfOne;
//     for (int i = 1; i <= num; i++) {
//         if (num % i == 0) {
//             teilerOfOne.emplace_back(i);
//         }
//     }
//     return teilerOfOne;
// }

// bool vectorContains(const vector<int> &nums, int num) {
//     return false;
// }
