#include <ranges>
#include "../MethodFrame.h"
#include "../TxtReader.h"
#include "Range.h"
using namespace std;

vector<Range> readSeedRanges(const string& line);
void printRanges(const vector<Range> &ranges);

int main() {
    MethodFrame mF("Day5_Try2.cc -> main");
    mF.printStart();
    vector<string> lines = TxtReader("../../inputs/input5.txt").getLines();

    vector<Range> seedRanges = readSeedRanges(lines[0]);
    printRanges(seedRanges);
    cout << endl;

    int amount = seedRanges.size();

    // TODO hier nochmal umstellen
    // jede Line erstellt neue (verschobene) Ranges newRanges
    // die alten bleiben bestehen
    // bei "map :" line und einmal am Ende wird seedRanges mit newRanges überschrieben und newRanges gecleart

    vector<Range> newRanges;
    for (int index = 3; index < lines.size(); index ++) {
        string line = lines[index];

        if (!line.empty() && isdigit(line.front())) {
            string destinationStr = strtok((char*) line.c_str(), " ");
            string sourceStr = strtok(NULL, " ");
            string rangeStr = strtok(NULL, " ");
            long start = stol(sourceStr);
            long end = start + stol(rangeStr) - 1;
            long addend = stol(destinationStr) - start;
            Range modRange(start, end);

            for (Range& range : seedRanges) {
                if (range.overlaps(modRange)) {
                    if (range.surrounds(modRange)) {
                        newRanges.emplace_back(Range(range.getStart(), modRange.getStart() - 1));
                        newRanges.emplace_back(Range(start + addend, end + addend));
                        newRanges.emplace_back(Range(end + 1, range.getEnd()));
                        amount += 2;
                    } else if (range.isSubSetOf(modRange)) {
                        newRanges.emplace_back(Range(range.getStart() + addend, range.getEnd() + addend));
                    } else if (range.getStart() < modRange.getStart()) {
                        newRanges.emplace_back(Range(range.getStart(), modRange.getStart() -1));
                        newRanges.emplace_back(Range(modRange.getStart() + addend, range.getEnd() + addend));
                        amount += 1;
                    } else if (range.getEnd() > modRange.getEnd()) {
                        newRanges.emplace_back(Range(range.getStart() + addend, modRange.getEnd() + addend));
                        newRanges.emplace_back(Range(modRange.getEnd() + 1, range.getEnd()));
                        amount += 1;
                    }
                } else {
                    newRanges.emplace_back(range);
                }
            }
        } else if (line.back() == ':') {
            cout << "seeds nefore: " << seedRanges.size() << endl;
            cout << "new: " << newRanges.size() << endl;
            amount -= seedRanges.size();
            seedRanges = newRanges;
            cout << "seeds after: " << seedRanges.size() << endl;
            // if (index < 24) {
            //     printRanges(seedRanges);
            //     cout << endl;
            // }
            newRanges.clear();
        } 
    }
    seedRanges = newRanges;
    // printRanges(seedRanges);
    // cout << endl;

    long min = LONG_MAX;
    for (Range range : seedRanges) {
        // range.print();
        if (range.getStart() < min) {
            min = range.getStart();
        }
    }
    cout << min << endl;
    cout << "amount: " << amount << endl;

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

void printRanges(const vector<Range> &ranges) {
    for (const Range& range : ranges) {
        range.print();
    }
}
