#include <map>
#include <ranges>
#include "../MethodFrame.h"
#include "../TxtReader.h"
using namespace std;

vector<long> readSeedsFromLinePart1(char* line);
vector<long> calculateDestinationsPart1(const vector<long>& seeds, const vector<string>& lines);
vector<pair<long, long>> readSeedRangesFromLinePart2(char* line);
long readRangeWithAddend(const vector<pair<long, long>>& seedRanges, const vector<string>& lines);
void printPairs(const vector<pair<long, long>>& pairs);
long getLowestStart(const vector<pair<long, long>>& currentRanges);
vector<pair<long, long>> calculateRanges(const pair<long, long>& oldRange, const long& sourceStart,  const long& range, const long& addend);
void printLongVector(const vector<long>& vec);

map<long, long> readTotalDestinationAddendBySource(const vector<string>& lines);
void discardedSolveWithMap(vector<string> lines);
map<string, vector<string>> readMapsFromLines(vector<string> lines);

int main() {
    MethodFrame mF("Day5.cpp -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input5.txt").getLines();

    // Part 1
    // vector<long> seeds = readSeedsFromLinePart1((char*) lines[0].c_str());
    // vector<long> destinations = calculateDestinations(seeds, lines);
    // long min = LONG_MAX;
    // for (long& destination : destinations) {
    //     if (destination < min) {
    //         min = destination;
    //     }
    // }
    // cout << min << endl;

    // Part 2
    vector<pair<long, long>> seedRanges = readSeedRangesFromLinePart2((char*) lines[0].c_str());
    cout << "ping" << endl;
    cout << endl << readRangeWithAddend(seedRanges, lines) << endl;

    mF.printEnd();
    return 0;
}

vector<long> readSeedsFromLinePart1(char* line) {
    vector<long> seeds;

    strtok(line, ":");
    char* seedsStr = strtok(NULL, ":");
    char* seedStr = strtok(seedsStr, " ");
    while (seedStr != NULL) {
        seeds.emplace_back(stol(seedStr));
        seedStr = strtok(NULL, " ");
    }

    return seeds;
}

vector<long> calculateDestinationsPart1(const vector<long> &seeds, const vector<string> &lines) {
    vector<long> currentNums(seeds);
    vector<long> newNums(seeds);
    
    for (int index = 2; index < lines.size(); index++) {
        string line = lines[index];
        if (!line.empty() && isdigit(line.front())) {
            string destinationStr = strtok((char*) line.c_str(), " ");
            string sourceStr = strtok(NULL, " ");
            string rangeStr = strtok(NULL, " ");
            long destinationStart = stol(destinationStr);
            long sourceStart = stol(sourceStr);
            long range = stol(rangeStr);

            for (int index = 0; index < currentNums.size(); index++) {
                if (currentNums[index] >= sourceStart && currentNums[index] < sourceStart + range) {
                    newNums[index] = currentNums[index] + destinationStart - sourceStart;
                }
            }
        }
        if (line.back() == ':') {
            currentNums = newNums;
        }
    }
    currentNums = newNums;

    return currentNums;
}

vector<pair<long, long>> readSeedRangesFromLinePart2(char *line){
    vector<pair<long, long>> seedRanges;
    long start;
    long range;
    bool isStartNotRange = true;

    strtok(line, ":");
    char* seedsStr = strtok(NULL, ":");

    char* seedStr = strtok(seedsStr, " ");
    while (seedStr != NULL) {
        if (isStartNotRange) {
            start = stol(seedStr);
            isStartNotRange = false;
        } else {
            range = stol(seedStr);
            seedRanges.emplace_back(pair<long, long>(start, range));
            isStartNotRange = true;
        }
        seedStr = strtok(NULL, " ");
    }

    return seedRanges;
}

long readRangeWithAddend(const vector<pair<long, long>> &seedRanges, const vector<string> &lines){
    vector<pair<long, long>> currentRanges(seedRanges);
    vector<pair<long, long>> newRanges(seedRanges);
    cout << "ping2" << endl;
    cout << "lines: " << lines.size() << endl;
    
    for (int index = 2; index < lines.size(); index++) {
        cout << index << ", currentRanges: " << currentRanges.size() << endl;
        string line = lines[index];
        if (!line.empty() && isdigit(line.front())) {
            string destinationStr = strtok((char*) line.c_str(), " ");
            string sourceStr = strtok(NULL, " ");
            string rangeStr = strtok(NULL, " ");
            long destinationStart = stol(destinationStr);
            long sourceStart = stol(sourceStr);
            long range = stol(rangeStr);
            long addend = destinationStart - sourceStart;

            for (int index = 0; index < currentRanges.size(); index++) {
                // FIXME oldRanges werden mehrfach hinzugefügt, brauche eine Kopie die in void Methode bearbeitet wird, nach ":" übernehmen
                // stimmt nicht ganz: nicht void, sondern return und sammeln was neu dazu kommt UND gleichzeitig in Original verschobenes rauslöschen
                // bei ":" zusammenführen
                vector<pair<long, long>> resultRanges = calculateRanges(currentRanges[index], sourceStart, range, addend);
                cout << "resultRanges: " << resultRanges.size() << endl;
                newRanges.insert(newRanges.end(), resultRanges.begin(), resultRanges.end());
            }
        }
        if (line.back() == ':') {
            currentRanges = newRanges;
            newRanges.clear();
        }
    }
    cout << endl;
    currentRanges = newRanges;

    return getLowestStart(currentRanges);
}

void printPairs(const vector<pair<long, long>>& pairs) {
    for (const pair<long, long>& range : pairs) {
        cout << "start: " << range.first << ", range: " << range.second << endl;
    }
}

long getLowestStart(const vector<pair<long, long>> &currentRanges) {
    long min = LONG_MAX;
    for (const pair<long, long>& range : currentRanges) {
        if (range.first < min) {
            min = range.first;
        }
    }
    return min;
}

vector<pair<long, long>> calculateRanges(const pair<long, long> &oldRange, const long &sourceStart, const long &sourceRange, const long &addend){
    vector<pair<long, long>> newRanges;
    long oldStart = oldRange.first;
    long oldEnd = oldStart + oldRange.second - 1;
    long sourceEnd = sourceStart + sourceRange - 1;

    // oS oE    sS sE   || sS sE    oS oE
    if (oldEnd < sourceStart || sourceEnd < oldStart) {
        newRanges.emplace_back(oldRange);
    }
    // oS   sS__sE  oE
    else if (oldStart <= sourceStart && sourceEnd <= oldEnd) {
        newRanges.emplace_back(pair<long, long>(oldStart, sourceStart - oldStart));
        newRanges.emplace_back(pair<long, long>(sourceStart + addend, sourceRange));
        newRanges.emplace_back(pair<long, long>(sourceEnd + 1, oldEnd - sourceEnd));
    }
    // sS   oS__oE  sE
    else if (oldStart <= sourceStart && sourceEnd <= oldEnd) {
        newRanges.emplace_back(pair<long, long>(oldStart + addend, oldRange.second));
    }
    // oS   sS__oE  sE
    else if (oldStart <= sourceStart && sourceEnd <= oldEnd) {
        newRanges.emplace_back(pair<long, long>(oldStart, sourceStart - oldStart));
        newRanges.emplace_back(pair<long, long>(sourceStart + addend, oldEnd - sourceStart + 1));
    }
    // sS   oS__sE  oE
    else if (oldStart <= sourceStart && sourceEnd <= oldEnd) {
        newRanges.emplace_back(pair<long, long>(oldStart + addend, sourceEnd - oldStart + 1));
        newRanges.emplace_back(pair<long, long>(sourceEnd + 1, oldEnd - sourceEnd));
    }
    
    return newRanges;
}

void printLongVector(const vector<long>& vec) {
    for (const long& num : vec) {
        cout << num << ", ";
    }
    cout << endl;
}

map<long, long> readTotalDestinationAddendBySource(const vector<string>& lines) {
    map<long, long> map;

    for (int index = 3; index < lines.size(); index++) {
        string line = lines[index];
        if (!line.empty() && isdigit(line.front())) {
            string destinationStr = strtok((char*) line.c_str(), " ");
            string sourceStr = strtok(NULL, " ");
            string rangeStr = strtok(NULL, " ");
            long destinationStart = stol(destinationStr);
            long sourceStart = stol(sourceStr);
            long range = stol(rangeStr);

            // for (long i = sourceStart; i < sourceStart + range; i++) {
            //     if (map.find(i) == map.end()) {
            //         map[i] = destinationStart - sourceStart;
            //     } else {
            //         map[i] = map[i] + 0;
            //     }
            // }
        }
    }

    return map;
}

void discardedSolveWithMap(vector<string> lines) {
    map<string, vector<string>> maps = readMapsFromLines(lines);
    for (const auto& map : maps) {
        cout << map.first << " -> ";
        for (const string& numStr : map.second) {
            cout << numStr << ", ";
        }
        cout << endl;
    }
}

map<string, vector<string>> readMapsFromLines(vector<string> lines) {
    map<string, vector<string>> maps;
    string activeMapName;
    
    for (int index = 2; index < lines.size(); index++) {
        string line = lines[index];

        if (line.back() == ':') {
            activeMapName = std::strtok((char*) line.c_str(), " ");
        } else if (!line.empty()) {
            if (maps.find(activeMapName) == maps.end()) {
                maps[activeMapName] = {};
            }
            maps[activeMapName].emplace_back(line);
        }
    }

    return maps;
}
