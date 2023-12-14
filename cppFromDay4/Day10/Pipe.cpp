#include "Pipe.h"

Pipe::Pipe(int row, int col, char form, char directionFrom, Pipe *to, long distance) 
        : row(row), col(col), form(form), directionFrom(directionFrom), next(to), distance(distance) {}

Pipe::~Pipe()
{
    if (this->next != nullptr) {
        delete this->next;
        this->next = nullptr;
    }
}

Pipe* Pipe::findS(const vector<string> &lines)
{
    Pipe* s;
    for (int row = 0; row < lines.size(); row++) {
        int col = findSColInRow(lines[row]);
        if (col >= 0) {
            s = new Pipe(row, col, 'S', '0', nullptr, 0);
            break;
        }
    }
    
    s->next = s->findNextFromS(lines);
    return s;
}

Pipe *Pipe::findNextFromS(const vector<string> &lines) const
{
    char form;
    if (this->row >= 1) {
        form = lines[this->row - 1][this->col];
        if (form == '7' || form == 'F' || form == '|') {
            return new Pipe(this->row - 1, this->col, form, 'S', nullptr, this->distance + 1);
        }
    }
    if (this->col < lines[0].size() - 1) {
        form = lines[this->row][this->col + 1];
        if (form == '7' || form == 'J' || form == '-') {
            return new Pipe(this->row, this->col + 1, form, 'W', nullptr, this->distance + 1);
        }
    }
    if (this->row < lines.size()) {
        form = lines[this->row + 1][this->col];
        if (form == 'L' || form == 'J' || form == '|') {
            return new Pipe(this->row + 1, this->col, form, 'N', nullptr, this->distance + 1);
        }
    }
    if (this->col >= 1) {
        form = lines[this->row][this->col - 1];
        if (form == 'L' || form == 'F' || form == '-') {
            return new Pipe(this->row, this->col - 1, form, 'E', nullptr, this->distance + 1);
        }
    }
    throw runtime_error("no next Pipe from S found");
}

Pipe *Pipe::findNext(const vector<string> &lines) const
{
    char directionOfNext = this->findDirectionOfNext();
    int row;
    int col;
    char directionFrom;
    switch (directionOfNext) {
        case 'N': row = this->row - 1; col = this->col; directionFrom = 'S'; break;
        case 'E': row = this->row; col = this->col + 1; directionFrom = 'W'; break;
        case 'S': row = this->row + 1; col = this->col; directionFrom = 'N'; break;
        case 'W': row = this->row; col = this->col - 1; directionFrom = 'E'; break;
    }

    return new Pipe(row, col, lines[row][col], directionFrom, nullptr, this->distance + 1);
}

char Pipe::findDirectionOfNext() const
{
    switch (this->directionFrom) {
        case 'N':
            switch (this->form) {
                case '|': return 'S';
                case 'J': return 'W';
                case 'L': return 'E';
            }
        case 'E':
            switch (this->form) {
                case '-': return 'W';
                case 'L': return 'N';
                case 'F': return 'S';
            }
        case 'S':
            switch (this->form) {
                case '|': return 'N';
                case '7': return 'W';
                case 'F': return 'E';
            }
        case 'W':
            switch (this->form) {
                case '-': return 'E';
                case 'J': return 'N';
                case '7': return 'S';
            }
    }
    throw runtime_error("directionNext could not be found");
}

int Pipe::findSColInRow(const string &line)
{
    for (int col = 0; col < line.size(); col++) {
        if (line.at(col) == 'S') {
            return col;
        }
    }
    return -1;
}

// deprecated
vector<pair<int, int>> Pipe::getAdjacents(const vector<string> &lines)
{
    vector<pair<int, int>> adjacents;

    for (int row = this->row - 1; row <= this->row + 1; row++) {
        if (row >= 0 && row < lines.size()) {
            for (int col = this->col - 1; col <= this->col + 1; col++) {
                if (col >= 0 && col < lines[row].size()) {
                    if ((row == this->row) != (col == this->col)) {
                        adjacents.emplace_back(pair<int, int>(row, col));
                    }
                }
            }
        }
    }

    return adjacents;
}

bool operator==(const Pipe &pipe1, const Pipe &pipe2)
{
    if (!(pipe1.row == pipe2.row && pipe1.col == pipe2.col && pipe1.form == pipe2.form && 
            pipe1.directionFrom == pipe2.directionFrom && pipe1.distance == pipe2.distance)) {
        return false;
    }
    if (pipe1.next == pipe2.next) {
        return true;
    }
    if (pipe1.next != nullptr && pipe2.next != nullptr) {
        if (*pipe1.next == *pipe2.next) {
            return true;
        }
    }
    return false;
}

ostream &operator<<(ostream &os, const Pipe &pipe)
{
    os << "Pipe [ row: " << setw(3) << pipe.row << ", col: " << setw(3) << pipe.col << ", form: " << pipe.form << ", directionFrom: " << pipe.directionFrom;
    if (pipe.next != nullptr) {
        os << ", next: [" << pipe.next->row << "," << pipe.next->col << "]";
    } else {
        os << ", next: nullptr";
    }
    os << ", distance: "  << pipe.distance << " ]";
    return os;
}
