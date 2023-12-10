#include <ranges>
#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Range.h"
using namespace std;

vector<Range> readSeedRanges(const string& line);
void modificateSeedRanges(vector<Range> &seedRanges, const vector<string> &lines);
Range findLowestRange(const vector<Range>& seedRanges);
void printRanges(const vector<Range>& ranges);

int main() {
    MethodFrame mF("Day5_Try2.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input5.txt").getLines();

    vector<Range> seedRanges = readSeedRanges(lines[0]);
    modificateSeedRanges(seedRanges, lines);
    Range lowestRange = findLowestRange(seedRanges);
    cout << "lowestRange: ";
    lowestRange.print();

    mF.printEnd();
    return 0;
}

vector<Range> readSeedRanges(const string& line) {
    vector<Range> seedRanges;
    long start;
    long end;
    bool isStartNotRange = true;

    strtok((char*) line.c_str(), ":");
    char* seedsStr = strtok(NULL, ":");

    char* seedStr = strtok(seedsStr, " ");
    while (seedStr != NULL) {
        if (isStartNotRange) {
            start = stol(seedStr);
            isStartNotRange = false;
        } else {
            end = start + stol(seedStr) - 1;
            Range newRange(start, end);
            seedRanges.emplace_back(newRange);
            isStartNotRange = true;
        }
        seedStr = strtok(NULL, " ");
    }

    return seedRanges;
}

void modificateSeedRanges(vector<Range> &seedRanges, const vector<string> &lines) {
    vector<Range> newRanges;
    
    for (int index = 3; index < lines.size(); index++) {
        string line = lines[index];
        if (!line.empty() && isdigit(line.front())) {

            if (index == 215) {
                cout << index << ": " << line << endl;
            }

            string destinationStr = strtok((char*) line.c_str(), " ");
            string sourceStr = strtok(NULL, " ");
            string rangeStr = strtok(NULL, " ");
            long start = stol(sourceStr);
            long end = start + stol(rangeStr) - 1;
            long addend = stol(destinationStr) - start;
            Range modificatorRange(start, end);

            vector<Range> secondPartsOfSplitRanges;
            for (Range& range : seedRanges) {
                
                if (index == 215 && range.getStart() == 0) {
                    range.print();
                }

                vector<Range> addedRanges;
                if (range.surrounds(modificatorRange)) {
                    addedRanges.emplace_back(Range(modificatorRange.getStart() + addend, modificatorRange.getEnd() + addend));
                    secondPartsOfSplitRanges.emplace_back(Range(modificatorRange.getEnd() + 1, range.getEnd()));
                    range.setEnd(modificatorRange.getStart() - 1);
                } else {
                    addedRanges = range.modificateRange(modificatorRange, addend);
                }
                newRanges.insert(newRanges.end(), addedRanges.begin(), addedRanges.end());
            }
            seedRanges.insert(seedRanges.end(), secondPartsOfSplitRanges.begin(), secondPartsOfSplitRanges.end());
        } else if (line.back() == ':') {
            seedRanges.insert(seedRanges.end(), newRanges.begin(), newRanges.end());
            newRanges.clear();
        }
    }
    seedRanges.insert(seedRanges.end(), newRanges.begin(), newRanges.end());
}

Range findLowestRange(const vector<Range> &seedRanges) {
    Range min(LONG_MAX, LONG_MAX);
    for (const Range& range : seedRanges) {
        if (range.getStart() < min.getStart()) {
            min = range;
        }
    }
    return min;
}

void printRanges(const vector<Range> &ranges) {
    for (const Range& range : ranges) {
        range.print();
    }
}
