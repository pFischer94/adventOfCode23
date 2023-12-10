#ifndef RANGE_H
#define RANGE_H

class Range {

    long start;
    long end;

    bool equals(const Range& modRange) const;
    bool isSuperSetOf(const Range& modRange) const;

public:
    Range(long start, long end) : start(start), end(end) {
        if (start > end) {
            cout << "FEHLER: start: " << start << ", end: " << end << endl;
            throw exception();
        }
    }
    vector<Range> modificateRange(const Range& modificatorRange, const long& addend);
    bool overlaps(const Range& modRange) const;
    bool surrounds(const Range& modRange) const;
    bool isSubSetOf(const Range& modRange) const;
    void print() const { cout << "Range [ start: " << start << ", end: " << end << " ]" << endl;  }
    long getStart() const { return start; }
    void setStart(long start) { this->start = start; }
    long getEnd() const { return end; }
    void setEnd(long end) { 
        if (this->start > end) {
            cout << "FEHLER: this->start: " << start << " > end: " << end << endl;
            throw exception();
        }
        this->end = end;
    }

};

bool Range::overlaps(const Range &modRange) const {
    return !(this->end < modRange.start || modRange.end < this->start);
}

bool Range::equals(const Range &modRange) const {
    return this->start == modRange.start && this->end == modRange.end;
}

bool Range::isSubSetOf(const Range &modRange) const {
    return modRange.start <= this->start && this->end <= modRange.end;
}

bool Range::isSuperSetOf(const Range &modRange) const {
    return this->start <= modRange.start && modRange.end <= this->end;
}

vector<Range> Range::modificateRange(const Range &modRange, const long &addend)
{
    vector<Range> addedRanges;

    if (this->overlaps(modRange)) {
        // modRange >= this
        if (this->isSubSetOf(modRange)) {
            this->start += addend;
            this->end += addend;
        } 
        
        else if (this->start < modRange.start) {
            addedRanges.emplace_back(Range(modRange.start + addend, this->end + addend));
            this->end = modRange.start - 1;
        } else if (this->end > modRange.end) {
            addedRanges.emplace_back(Range(this->start + addend, modRange.end + addend));
            this->start = modRange.end + 1;
        }
    }

    // // 1: mS  mE  tS  tE  ||  tS  tE  mS  mE
    // if (this->end < modRange.start || modRange.end < this->start) {
    // }

    // // 2: mS  tS__tE  mE
    // else if (modRange.start <= this->start && this->end <= modRange.end) {
    //     this->start += addend;
    //     this->end += addend;
    // }

    // // 3: tS  mS__mE  tE
    // else if (this->start < modRange.start && modRange.end < this->end) {
    //     addedRanges.emplace_back(Range(modRange.start + addend, modRange.end + addend));
    //     addedRanges.emplace_back(Range(modRange.end + 1, this->end));
    //     this->end = modRange.start - 1;
    // }

    // // 4: tS  mS__tE  mE
    // else if (this->start <= modRange.start && this->end <= modRange.end) {
    //     addedRanges.emplace_back(Range(modRange.start + addend, this->end + addend));
    //     this->end = modRange.start - 1;
    // }

    // // 5: mS  tS__mE  tE
    // else if (modRange.start <= this->start && modRange.end <= this->end) {
    //     addedRanges.emplace_back(this->start + addend, modRange.end + addend);
    //     this->start = modRange.end + 1;
    // }

    if (start > end) {
        cout << "FEHLER: start: " << start << ", end: " << end << endl;
        throw exception();
    }

    return addedRanges;
}

bool Range::surrounds(const Range &modRange) const {
    return this->start < modRange.start && modRange.end < this->end;
}

#endif