#include <iostream>
#include "PipeTests.h"
#include "../TxtReader.h"
using namespace std;

int main() {
    cout << left << endl;

    PipeTests::testFindSColInRow();
    PipeTests::testFindDirectionOfNext();
    PipeTests::testFindNext();
    PipeTests::testFindNextFromS();
    PipeTests::testFindS();
    // deprecated
    PipeTests::testGetAdjacents();
    PipeTests::testFindNextUntilS();
    
    cout << endl;
    return 0;
}

void PipeTests::testFindS()
{
    cout << setw(WIDTH) << "  testFindS" << flush;

    vector<string> lines = { "FL|LL.L--7.|-LF---7J.F-JL-7|L7L--7|-|L-7L|L-7FJ||L7F7LJ|L7|F-JFJFJLJ|FJ||FJL7||||FJL7F-7|L7L7||||LJFJF-JF-7LJLJL7F-7JFJL7J.7FF-7JFF.||.F7J|.",
            "7-J.L7LF7LF|7-L--7|F7L---7LJFJF7FJL-JF-JFJF7|L7||FJ||F7L7|||LFJFJ7|FJ|FJ|L-7|||||L-7|L7|L7|FJLJ||F-J.L--J-L-7F--J|FJFJF-J7FL|JF|F7|.JJF7.L|.",
            "J.LFJ|F|---LF----J|||F7F-JF7L7||L-7F7L-7|FJLJ7||||FJLJL-JLJ|FJFJF7FJFJL7|F7||SLJL7FJ|FJ|FJ|L-7FJ|L-7F--7F7F-JL-7FJL7|FJFF77J|FF||LJ77F--7||7",
            "LF.7.LFJJ|-F|F---7LJLJ||F7||FJ||F7LJ|F-J|L--7FJ|||L--7F--7FJ|FJFJ||FJJFJLJ|||L--7|L7|L7|L7L7FJL7|F-JL7FJ||L-7F-JL7FJ||F7||JFF7F7J7LF|JJLF-|7",
            "7-JJ7-|.|F7FLJF7FJF--7|LJLJ|L-J||L--J|F7|F--JL7LJL-7-LJF-J|FJL7|FJ||F7L-7FJ||F77|L7||FJ|FJFJ|F7LJL7F7|L7||FFJL-7FJ|FJLJLJ|F7|LJ|L7..|JFJJ7L." };
    Pipe* s = Pipe::findS(lines);
    Pipe* next = new Pipe(1, 77, '|', 'S', nullptr, 1);
    Pipe* expected = new Pipe(2, 77, 'S', '0', next, 0);

    if (*s == *expected && *s->next == *next) {
        cout << GREEN << " iO" << RESET << endl;
    } else {
        cout << RED << "niO" << RESET << endl;
    }
    delete s;
    delete expected;
}

void PipeTests::testFindSColInRow()
{
    cout << setw(WIDTH) << "  testFindSColInRow" << flush;

    string line = "J.LFJ|F|---LF----J|||F7F-JF7L7||L-7F7L-7|FJLJ7||||FJLJL-JLJ|FJFJF7FJFJL7|F7||SLJL7FJ|FJ|FJ|L-7FJ|L-7F--7F7F-JL-7FJL7|FJFF77J|FF||LJ77F--7||7";
    int col = Pipe::findSColInRow(line);
    int expected = 77;

    if (col == expected) {
        cout << GREEN << " iO" << RESET << endl;
    } else {
        cout << RED << "niO" << RESET << endl;
    }
}

void PipeTests::testFindDirectionOfNext()
{
    cout << setw(WIDTH) << "  testFindDirectionOfNext" << flush;

    Pipe pipe1(0, 0, 'L', 'N', nullptr, 0);
    char directionOfNext1 = pipe1.findDirectionOfNext();
    int expected1 = 'E';
    Pipe pipe2(0, 0, '-', 'E', nullptr, 0);
    char directionOfNext2 = pipe2.findDirectionOfNext();
    int expected2 = 'W';
    Pipe pipe3(0, 0, '7', 'S', nullptr, 0);
    char directionOfNext3 = pipe3.findDirectionOfNext();
    int expected3 = 'W';

    if (directionOfNext1 == expected1 && directionOfNext2 == expected2 && directionOfNext3 == expected3) {
        cout << GREEN << " iO" << RESET << endl;
    } else {
        cout << RED << "niO" << RESET << endl;
    }
}

void PipeTests::testFindNext()
{
    cout << setw(WIDTH) << "  testFindNext" << flush;

    vector<string> lines = { "FL|LL.L--7.|-LF---7J.F-JL-7|L7L--7|-|L-7L|L-7FJ||L7F7LJ|L7|F-JFJFJLJ|FJ||FJL7||||FJL7F-7|L7L7||||LJFJF-JF-7LJLJL7F-7JFJL7J.7FF-7JFF.||.F7J|.",
            "7-J.L7LF7LF|7-L--7|F7L---7LJFJF7FJL-JF-JFJF7|L7||FJ||F7L7|||LFJFJ7|FJ|FJ|L-7|||||L-7|L7|L7|FJLJ||F-J.L--J-L-7F--J|FJFJF-J7FL|JF|F7|.JJF7.L|.",
            "J.LFJ|F|---LF----J|||F7F-JF7L7||L-7F7L-7|FJLJ7||||FJLJL-JLJ|FJFJF7FJFJL7|F7||SLJL7FJ|FJ|FJ|L-7FJ|L-7F--7F7F-JL-7FJL7|FJFF77J|FF||LJ77F--7||7",
            "LF.7.LFJJ|-F|F---7LJLJ||F7||FJ||F7LJ|F-J|L--7FJ|||L--7F--7FJ|FJFJ||FJJFJLJ|||L--7|L7|L7|L7L7FJL7|F-JL7FJ||L-7F-JL7FJ||F7||JFF7F7J7LF|JJLF-|7",
            "7-JJ7-|.|F7FLJF7FJF--7|LJLJ|L-J||L--J|F7|F--JL7LJL-7-LJF-J|FJL7|FJ||F7L-7FJ||F77|L7||FJ|FJFJ|F7LJL7F7|L7||FFJL-7FJ|FJLJLJ|F7|LJ|L7..|JFJJ7L." };
    Pipe pipe(2, 78, 'L', 'N', nullptr, 2);
    pipe.next = pipe.findNext(lines);
    Pipe expected(2, 79, 'J', 'W', nullptr, 3);

    if (*pipe.next == expected) {
        cout << GREEN << " iO" << RESET << endl;
    } else {
        cout << RED << "niO" << RESET << endl;
    }
}

void PipeTests::testFindNextUntilS()
{
    // vector<string> lines = TxtReader("../../inputs/input10.txt").getLines();
    // Pipe* curr = new Pipe(26, 80, '7', 'S', nullptr, 20);
    // cout << *curr << endl;
    // for (int i = 0; i < 8; i++) {
    //     curr = curr->findNext(lines);
    //     cout << *curr << endl;
    // }
}

void PipeTests::testFindNextFromS()
{
    cout << setw(WIDTH) << "  testFindNextFromS" << flush;

    vector<string> lines = { "FL|LL.L--7.|-LF---7J.F-JL-7|L7L--7|-|L-7L|L-7FJ||L7F7LJ|L7|F-JFJFJLJ|FJ||FJL7||||FJL7F-7|L7L7||||LJFJF-JF-7LJLJL7F-7JFJL7J.7FF-7JFF.||.F7J|.",
            "7-J.L7LF7LF|7-L--7|F7L---7LJFJF7FJL-JF-JFJF7|L7||FJ||F7L7|||LFJFJ7|FJ|FJ|L-7|||||L-7|L7|L7|FJLJ||F-J.L--J-L-7F--J|FJFJF-J7FL|JF|F7|.JJF7.L|.",
            "J.LFJ|F|---LF----J|||F7F-JF7L7||L-7F7L-7|FJLJ7||||FJLJL-JLJ|FJFJF7FJFJL7|F7||SLJL7FJ|FJ|FJ|L-7FJ|L-7F--7F7F-JL-7FJL7|FJFF77J|FF||LJ77F--7||7",
            "LF.7.LFJJ|-F|F---7LJLJ||F7||FJ||F7LJ|F-J|L--7FJ|||L--7F--7FJ|FJFJ||FJJFJLJ|||L--7|L7|L7|L7L7FJL7|F-JL7FJ||L-7F-JL7FJ||F7||JFF7F7J7LF|JJLF-|7",
            "7-JJ7-|.|F7FLJF7FJF--7|LJLJ|L-J||L--J|F7|F--JL7LJL-7-LJF-J|FJL7|FJ||F7L-7FJ||F77|L7||FJ|FJFJ|F7LJL7F7|L7||FFJL-7FJ|FJLJLJ|F7|LJ|L7..|JFJJ7L." };
    Pipe* s = new Pipe(2, 77, 'S', '0', nullptr, 0);
    s->next = s->findNextFromS(lines);
    Pipe expected(1, 77, '|', 'S', nullptr, 1);

    if (expected == *s->next) {
        cout << GREEN << " iO" << RESET << endl;
    } else {
        cout << RED << "niO" << RESET << endl;
    }
    delete s;
}

// deprecated
void PipeTests::testGetAdjacents()
{
    vector<string> lines = { 
            "FL|LL.L--7.|-LF---7J.F-JL-7|L7L--7|-|L-7L|L-7FJ||L7F7LJ|L7|F-JFJFJLJ|FJ||FJL7||||FJL7F-7|L7L7||||LJFJF-JF-7LJLJL7F-7JFJL7J.7FF-7JFF.||.F7J|.",
            "7-J.L7LF7LF|7-L--7|F7L---7LJFJF7FJL-JF-JFJF7|L7||FJ||F7L7|||LFJFJ7|FJ|FJ|L-7|||||L-7|L7|L7|FJLJ||F-J.L--J-L-7F--J|FJFJF-J7FL|JF|F7|.JJF7.L|.",
            "J.LFJ|F|---LF----J|||F7F-JF7L7||L-7F7L-7|FJLJ7||||FJLJL-JLJ|FJFJF7FJFJL7|F7||SLJL7FJ|FJ|FJ|L-7FJ|L-7F--7F7F-JL-7FJL7|FJFF77J|FF||LJ77F--7||7",
            "LF.7.LFJJ|-F|F---7LJLJ||F7||FJ||F7LJ|F-J|L--7FJ|||L--7F--7FJ|FJFJ||FJJFJLJ|||L--7|L7|L7|L7L7FJL7|F-JL7FJ||L-7F-JL7FJ||F7||JFF7F7J7LF|JJLF-|7",
            "7-JJ7-|.|F7FLJF7FJF--7|LJLJ|L-J||L--J|F7|F--JL7LJL-7-LJF-J|FJL7|FJ||F7L-7FJ||F77|L7||FJ|FJFJ|F7LJL7F7|L7||FFJL-7FJ|FJLJLJ|F7|LJ|L7..|JFJJ7L." };
    Pipe* s = new Pipe(2, 77, 'S', 'S', nullptr, 0);
    vector<pair<int, int>> adjacents = s->getAdjacents(lines);
    vector<pair<int, int>> expected = { {1,77}, {2,76}, {2,78}, {3,77} };

    if (adjacents == expected) {
        cout << GREEN << setw(WIDTH) << "  testGetAdjacents" << " iO" << RESET << endl;
    } else {
        cout << RED << setw(WIDTH) << "  testGetAdjacents" << "niO" << RESET << endl;
    }
    delete s;
}
