package de.vw.vwx27wz.day5;

import java.util.ArrayList;
import java.util.List;

public class SeedRange extends Range {

    public SeedRange(long start, long end) {
        super(start, end);
    }

    public static List<SeedRange> readSeedRangesFromLine(String line) {
        List<SeedRange> seedRanges = new ArrayList<>();
        String[] split = line.split(" ");

        for (int i = 1; i < split.length - 1; i += 2) {
            long start = Long.parseLong(split[i]);
            long end = start + Long.parseLong(split[i + 1]) - 1;
            seedRanges.add(new SeedRange(start, end));
        }

        seedRanges.sort((a, b) -> a.compareTo(b));
        if (!Range.isListOfRangesValid(seedRanges)) {
            throw new RuntimeException("seedRanges is an invalid List of Ranges");
        }
        return seedRanges;
    }

    public static List<SeedRange> convert(List<SeedRange> sourceRanges, List<ConversionRange> conversionRanges) {
        if (!Range.isListOfRangesValid(sourceRanges) || !Range.isListOfRangesValid(conversionRanges)) {
            throw new IllegalArgumentException("at least one of the passed lists of ranges is invalid");
        }

        List<SeedRange> destinationRanges = new ArrayList<>();

        for (SeedRange sourceRange : sourceRanges) {
            List<SeedRange> convertedParts = new ArrayList<>();
            for (ConversionRange conversionRange : conversionRanges) {
                if (sourceRange.overlaps(conversionRange)) {
                    SeedRange result = conversionRange.convert(sourceRange);
                    SeedRange convertedPart = conversionRange.convertedPartOf(sourceRange);

                    destinationRanges.add(result);
                    convertedParts.add(convertedPart);
                }
            }
            List<SeedRange> remainder = sourceRange.deduct(convertedParts);
            destinationRanges.addAll(remainder);
        }

        destinationRanges.sort((a, b) -> a.compareTo(b));
        destinationRanges = Range.mergeOverlappingRangesIn(destinationRanges);
        if (!Range.isListOfRangesValid(destinationRanges)) {
            throw new RuntimeException("destinationRanges is an invalid List of SeedRanges");
        }
        return destinationRanges;
    }

    private List<SeedRange> deduct(List<SeedRange> convertedParts) {
        if (convertedParts.size() == 0) {
            return List.of(this);
        }
        convertedParts.sort((a, b) -> a.compareTo(b));
        Range.isListOfRangesValid(convertedParts);

        List<SeedRange> remainder = new ArrayList<>();

        SeedRange first = convertedParts.get(0);
        if (this.getStart() < first.getStart()) {
            remainder.add(new SeedRange(this.getStart(), first.getStart() - 1));
        }

        for (int i = 0; i < convertedParts.size() - 1; i++) {
            SeedRange curr = convertedParts.get(i);
            SeedRange next = convertedParts.get(i + 1);
            if (curr.getEnd() < next.getStart() - 1) {
                remainder.add(new SeedRange(curr.getEnd() + 1, next.getStart() - 1));
            }
        }

        SeedRange last = convertedParts.get(convertedParts.size() - 1);
        if (last.getEnd() < this.getEnd()) {
            remainder.add(new SeedRange(last.getEnd() + 1, this.getEnd()));
        }

        return remainder;
    }

    public SeedRange merge(Range... ranges) {
        if (ranges.length == 0) {
            return this;
        }

        long min = this.getStart();
        long max = this.getEnd();

        for (int index = 0; index < ranges.length; index++) {
            min = Math.min(min, ranges[index].getStart());
            max = Math.max(max, ranges[index].getEnd());
        }

        return new SeedRange(min, max);
    }

    @Override
    public String toString() {
        return "SeedRange [ start=%,15d, end=%,15d ]".formatted(this.getStart(), this.getEnd());
    }

}
