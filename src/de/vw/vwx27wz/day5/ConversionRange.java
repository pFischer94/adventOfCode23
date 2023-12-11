package de.vw.vwx27wz.day5;

import java.util.ArrayList;
import java.util.List;

public class ConversionRange extends Range {

    private long addend;

    public ConversionRange(long start, long end, long addend) {
        super(start, end);
        this.addend = addend;
    }

    public static List<List<ConversionRange>> readConversionTablesFromLines(List<String> lines) {
        List<List<ConversionRange>> allConversionRanges = new ArrayList<>();
        List<ConversionRange> conversionRangesOfOneMap = new ArrayList<>();

        for (int index = 3; index < lines.size(); index++) {
            String line = lines.get(index);
            if (!line.isBlank()) {
                if (!line.endsWith(":")) {
                    conversionRangesOfOneMap.add(readConversionRangeFromLine(line));
                } else {
                    conversionRangesOfOneMap.sort((a, b) -> a.compareTo(b));
                    if (!Range.isListOfRangesValid(conversionRangesOfOneMap)) {
                        throw new RuntimeException("conversionRangesOfOneMap is an invalid List of ConversionRanges");
                    }
                    allConversionRanges.add(conversionRangesOfOneMap);
                    conversionRangesOfOneMap = new ArrayList<>();
                }
            }
        }
        conversionRangesOfOneMap.sort((a, b) -> a.compareTo(b));
        if (!Range.isListOfRangesValid(conversionRangesOfOneMap)) {
            throw new RuntimeException("conversionRangesOfOneMap is an invalid List of ConversionRanges");
        }
        allConversionRanges.add(conversionRangesOfOneMap);

        return allConversionRanges;
    }

    private static ConversionRange readConversionRangeFromLine(String line) {
        String[] split = line.split(" ");
        long start = Long.parseLong(split[1]);
        long end = start + Long.parseLong(split[2]) - 1;
        if (end < start) {
            throw new RuntimeException("end < start");
        }
        long addend = Long.parseLong(split[0]) - start;
        return new ConversionRange(start, end, addend);
    }

    public SeedRange convert(SeedRange sourceRange) {
        long start = Math.max(this.getStart(), sourceRange.getStart()) + this.addend;
        long end = Math.min(this.getEnd(), sourceRange.getEnd()) + this.addend;
        return new SeedRange(start, end);
    }

    public SeedRange convertedPartOf(SeedRange sourceRange) {
        long start = Math.max(this.getStart(), sourceRange.getStart());
        long end = Math.min(this.getEnd(), sourceRange.getEnd());
        return new SeedRange(start, end);
    }

    @Override
    public String toString() {
        return "ConversionRange [ start=%,15d, end=%,15d, addend=%,15d ]".formatted(this.getStart(), this.getEnd(),
                this.addend);
    }

}
