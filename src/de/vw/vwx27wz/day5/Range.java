package de.vw.vwx27wz.day5;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

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
        // TODO isValid checks entfernen
        if (!this.isValid()) {
            throw new RuntimeException(this + " (this) is not a valid Range");
        }
        if (!other.isValid()) {
            throw new RuntimeException(this + " (other) is not a valid Range");
        }
//        System.out.println("this:  " + this);
//        System.out.println("other: " + other);
//        System.out.println("this.end < other.start: " + (this.end < other.start));
//        System.out.println("other.end < this.start: " + (other.end < this.start));
//        System.out.println();
        return !(this.end < other.start || other.end < this.start);
    }

    public boolean surrounds(Range other) {
        return this.start < other.start && other.end < this.end;
    }

    public boolean isSubSetOf(Range other) {
        return other.start <= this.start && this.end <= other.end;
    }

    // TODO research validate
    // TODO mergeAdjacent
    public static List<SeedRange> mergeOverlappingRangesIn(List<SeedRange> sortedRanges) {
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

                if (lastMerged.overlaps(sortedRange)) {
                    mergeLast(mergedRanges, sortedRange);
                } else {
                    mergedRanges.add(sortedRange);
                }
            }
        }

        return mergedRanges;
    }

    private static void mergeLast(List<SeedRange> mergedRanges, SeedRange sortedRange) {
        SeedRange lastMerged = mergedRanges.get(mergedRanges.size() - 1);
        SeedRange mergedRange = lastMerged.merge(sortedRange);
        mergedRanges.remove(lastMerged);
        mergedRanges.add(mergedRange);
    }

    // TODO "System." entfernen, hier und überall
    public static <T extends Range> boolean isListOfRangesValid(List<T> ranges) {
        if (!ranges.get(0).isValid()) {
            System.err.println(ranges.get(0) + " (first) is not valid");
            return false;
        }
        for (int index = 0; index < ranges.size() - 1; index++) {
            Range leftRange = ranges.get(index);
            Range rightRange = ranges.get(index + 1);
            if (!rightRange.isValid()) {
                System.err.println(rightRange + " (right) is not valid");
                return false;
            }
            if (!leftRange.isBefore(rightRange)) {
                System.err.println(leftRange + " is not before " + rightRange);
                return false;
            }
            if (leftRange.overlaps(rightRange)) {
//                System.err.println(leftRange + " overlaps " + rightRange);
//                System.out.println("left:  " + leftRange);
//                System.out.println("right: " + rightRange);
//                System.out.println(leftRange.overlaps(rightRange));
                return false;
            }
        }
        return true;
    }

    public static <T extends Range> void printRanges(List<T> ranges) {
        for (Range range : ranges) {
            System.out.println(range);
        }
    }

    public long getStart() {
        return this.start;
    }

    public long getEnd() {
        return this.end;
    }

    public void setEnd(long end) {
        if (end < this.start) {
            throw new RuntimeException("new end %d is before this.start %d".formatted(end, this.start));
        }
        this.end = end;
    }

    public int compareTo(Range o) {
        if (this.start < o.start) {
            return -1;
        }
        if (this.start > o.start) {
            return 1;
        }
        // TODO wenn läuft: nach Enden unterscheiden?
        return 0;
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.end, this.start);
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (obj == null)
            return false;
        if (getClass() != obj.getClass())
            return false;
        Range other = (Range) obj;
        return this.end == other.end && this.start == other.start;
    }

}
