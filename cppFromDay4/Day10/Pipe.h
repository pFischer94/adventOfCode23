#ifndef PIPE_H
#define PIPE_H

#include <iomanip>
using namespace std;

class Pipe {

    enum Direction { N, S, W, E };

    int row;
    int col;
    char form;
    char directionFrom;
    Pipe* next;
    long distance;

    static int findSColInRow(const string& line);                                   // tested iO
    char findDirectionOfNext() const;                                               // tested iO
    // deprecated
    vector<pair<int, int>> getAdjacents(const vector<string>& lines);               // tested iO
    char getFormOfS() const;

    friend bool operator==(const Pipe& pipe1, const Pipe& pipe2);
    friend ostream& operator<<(ostream& os, const Pipe& pipe);
    
    friend class PipeTests;

public:
    Pipe(int row, int col, char form, char directionFrom, Pipe* to, long distance);
    ~Pipe();
    static Pipe* findS(const vector<string>& lines);                                // tested iO
    Pipe* findNextFromS(const vector<string>& lines) const;                         // tested iO
    Pipe* findNext(const vector<string>& lines) const;                              // tested iO
    static vector<string> getLinesWithLoop(const vector<string>& lines);
    long countEnclosedTiles(const vector<string>& linesWithLoop);
    char getForm() const { return this->form; }
    Pipe* getNext() const { return this->next; }
    void setNext(Pipe* next) { this->next = next; }
    long getDistance() const { return this->distance; }
    int getRow() const { return this->row; }
    int getCol() const { return this->col; }
    char getDirectionFrom() const { return this->directionFrom; }
    void setDirectionFrom(char dir) { this->directionFrom = dir; }

};

#endif