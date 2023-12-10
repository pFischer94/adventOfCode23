package de.vw.vwx27wz.day5.tests;

import static org.junit.jupiter.api.Assertions.assertEquals;

import java.util.List;

import org.junit.jupiter.api.Test;

import de.vw.vwx27wz.day5.Range;
import de.vw.vwx27wz.day5.SeedRange;

public class RangeTests {

    SeedRange range0To0 = new SeedRange(0, 0);
    SeedRange range1To5 = new SeedRange(1, 5);
    SeedRange range3To6 = new SeedRange(3, 6);
    SeedRange range4To4 = new SeedRange(4, 4);
    SeedRange range4To6 = new SeedRange(4, 6);

    @Test
    void testMergeOverlappingRangesIn() {
        List<SeedRange> unmerged = List.of(this.range1To5, this.range3To6);
        List<SeedRange> mergedList = Range.mergeOverlappingRangesIn(unmerged);
        assertEquals(1, mergedList.size());
        assertEquals(new SeedRange(1, 6), mergedList.get(0));
    }

    @Test
    void testOverlaps() {
        assertEquals(true, this.range1To5.overlaps(this.range3To6));
        assertEquals(true, this.range3To6.overlaps(this.range1To5));
        assertEquals(true, this.range3To6.overlaps(this.range3To6));
        assertEquals(true, this.range3To6.overlaps(this.range4To6));
        assertEquals(true, this.range4To6.overlaps(this.range3To6));
        assertEquals(true, this.range4To4.overlaps(this.range3To6));
        assertEquals(true, this.range4To6.overlaps(this.range4To4));

        assertEquals(false, this.range0To0.overlaps(this.range3To6));
        assertEquals(false, this.range0To0.overlaps(this.range4To4));
        assertEquals(false, this.range1To5.overlaps(this.range0To0));
    }

}
