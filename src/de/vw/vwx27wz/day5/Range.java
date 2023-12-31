package de.vw.vwx27wz.day5;

import java.util.ArrayList;
import java.util.List;

public abstract class Range {

    private long start;
    private long end;

    protected Range(long start, long end) {
        if (end < start) {
            throw new RuntimeException("end < start");
        }
        this.start = start;
        this.end = end;
    }

    public boolean isValid() {
        return this.start <= this.end;
    }

    public boolean isBefore(Range other) {
        return this.end < other.start;
    }

    public boolean overlaps(Range other) {
        return !(this.isBefore(other) || other.isBefore(this));
    }

    public boolean overlapsOrIsAdjacent(Range other) {
        return this.overlaps(other) || this.start - other.end == 1 || other.start - this.end == 1;
    }

    public static List<SeedRange> mergeAdjacentRangesIn(List<SeedRange> sortedRanges) {
        List<SeedRange> mergedRanges = new ArrayList<>();

        for (int index = 0; index < sortedRanges.size(); index++) {
            SeedRange sortedRange = sortedRanges.get(index);

            if (mergedRanges.size() == 0) {
                mergedRanges.add(sortedRange);
            } else {
                SeedRange lastMerged = mergedRanges.get(mergedRanges.size() - 1);
                if (lastMerged.compareTo(sortedRange) > 0) {
                    throw new IllegalArgumentException("input has to be sorted beforehand");
                }

                if (lastMerged.overlapsOrIsAdjacent(sortedRange)) {
                    sortedRange.mergeLast(mergedRanges);
                } else {
                    mergedRanges.add(sortedRange);
                }
            }
        }

        return mergedRanges;
    }

    // FRAGE: warum geht private nicht?
    // ANTWORT: weil die Methode in mergeAdjacentRangesIn() von einem SeedRange Objekt benutzt wird,
    // dass private Range Methoden nicht sehen kann -> protected
    // GENERELL: Parents sollten niemals die Kinder kennen oder verwenden!!!
    protected void mergeLast(List<SeedRange> mergedRanges) {
        if (mergedRanges.size() == 0) {
            mergedRanges.add((SeedRange) this);
        }
        SeedRange lastMerged = mergedRanges.get(mergedRanges.size() - 1);
        SeedRange mergedRange = lastMerged.merge(this);
        mergedRanges.remove(lastMerged);
        mergedRanges.add(mergedRange);
    }

    public static <T extends Range> boolean isListOfRangesValid(List<T> ranges) {
        if (!ranges.get(0).isValid()) {
            return false;
        }
        for (int index = 0; index < ranges.size() - 1; index++) {
            Range leftRange = ranges.get(index);
            Range rightRange = ranges.get(index + 1);
            if (!rightRange.isValid()) {
                return false;
            }
            if (rightRange.isBefore(leftRange)) {
                return false;
            }
            if (leftRange.overlaps(rightRange)) {
                return false;
            }
        }
        return true;
    }

    public long getStart() {
        return this.start;
    }

    public long getEnd() {
        return this.end;
    }

    public int compareTo(Range o) {
        if (this.start < o.start) {
            return -1;
        }
        if (this.start > o.start) {
            return 1;
        }
        if (this.end < o.end) {
            return -1;
        }
        if (this.end > o.end) {
            return 1;
        }
        return 0;
    }

}
