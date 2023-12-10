package de.vw.vwx27wz.day5;

import java.util.ArrayList;
import java.util.List;

public class SeedRange extends Range {

    // TODO // auskommentiertes entfernen
    public SeedRange(long start, long end) {
        super(start, end);
//        if (start == 0) {
//            new RuntimeException("0").printStackTrace();
//            System.out.println();
//        }
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
        // TODO listen validieren

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

//        int sourceIndex = 0;
//        boolean sourceAlreadyConverted = false;
//        int conversionIndex = 0;
//
//        while (sourceIndex < sourceRanges.size()) {
//            SeedRange sourceRange = sourceRanges.get(sourceIndex);
//            ConversionRange conversionRange = conversionRanges.get(conversionIndex);
//
////            printStuff(sourceRanges, conversionRanges, sourceIndex, conversionIndex, sourceRange, conversionRange);
//
//            if (sourceRange.overlaps(conversionRange)) {
//                // TODO Fehlersuche convert()
//                List<SeedRange> convertedRanges = sourceRange.convert(conversionRange);
//                destinationRanges.addAll(convertedRanges);
//                if (conversionRange.getEnd() >= sourceRange.getEnd()) {
//                    sourceIndex++;
//                } else {
//                    conversionIndex++;
//                }
//            } else {
//                // TODO test isBefore
//                if (conversionRange.isBefore(sourceRange)) {
//                    conversionIndex++;
//                } else {
//                    destinationRanges.add(sourceRange);
//                    sourceIndex++;
//                }
//            }
//        }

        destinationRanges.sort((a, b) -> a.compareTo(b));
        destinationRanges = Range.mergeOverlappingRangesIn(destinationRanges);
        if (!Range.isListOfRangesValid(destinationRanges)) {
            throw new RuntimeException("destinationRanges is an invalid List of SeedRanges");
        }
        return destinationRanges;
    }

    // TODO validieren und sort converted
    private List<SeedRange> deduct(List<SeedRange> convertedParts) {
        if (convertedParts.size() == 0) {
            return List.of(new SeedRange(this.getStart(), this.getEnd()));
        }

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

    private static void printStuff(List<SeedRange> sourceRanges, List<ConversionRange> conversionRanges, int sourceIndex, int conversionIndex, SeedRange sourceRange, ConversionRange conversionRange) {
        System.out.printf("sourceIndex     = %3d  < %3d  =     sourceRanges.size() %n", sourceIndex,
                sourceRanges.size());
        System.out.printf("conversionIndex = %3d  < %3d  = conversionRanges.size() %n",
                conversionIndex, conversionRanges.size());
        if (sourceIndex >= sourceRanges.size()) {
            throw new RuntimeException("sourceIndex %d is out of bounds for sourceRanges.size() %d %n"
                    .formatted(sourceIndex, sourceRanges.size()));
        }
        if (conversionIndex >= conversionRanges.size()) {
            throw new RuntimeException("conversionIndex %d is out of bounds for conversionRanges.size() %d %n"
                    .formatted(conversionIndex, conversionRanges.size()));
        }

        System.out.println("      " + sourceRange);
        System.out.println(conversionRange);
        System.out.println("overlaps:        " + sourceRange.overlaps(conversionRange));
        System.out.println("conv before src: " + conversionRange.isBefore(conversionRange));
        System.out.println();

        if (conversionRange.getStart() == 0) {
            new RuntimeException("convert from 0").printStackTrace();
            System.out.println();
        }
    }

    private List<SeedRange> convert(ConversionRange conversionRange) {
        List<SeedRange> convertedRanges = new ArrayList<>();

        if (this.surrounds(conversionRange)) {
            convertedRanges.add(new SeedRange(this.getStart(), conversionRange.getStart() - 1));
            convertedRanges.add(new SeedRange(
                    conversionRange.getStart() + conversionRange.getAddend(),
                    conversionRange.getEnd() + conversionRange.getAddend()));
            convertedRanges.add(new SeedRange(conversionRange.getEnd() + 1, this.getEnd()));
        } else if (this.isSubSetOf(conversionRange)) {
            convertedRanges.add(new SeedRange(
                    this.getStart() + conversionRange.getAddend(),
                    this.getEnd() + conversionRange.getAddend()));
        } else if (this.getStart() < conversionRange.getStart()) {
            convertedRanges.add(new SeedRange(this.getStart(), conversionRange.getStart() - 1));
            convertedRanges.add(new SeedRange(
                    conversionRange.getStart() + conversionRange.getAddend(),
                    this.getEnd() + conversionRange.getAddend()));
        } else if (this.getEnd() > conversionRange.getEnd()) {
            convertedRanges.add(new SeedRange(
                    this.getStart() + conversionRange.getAddend(),
                    conversionRange.getEnd() + conversionRange.getAddend()));
            convertedRanges.add(new SeedRange(conversionRange.getEnd() + 1, this.getEnd()));
        }

        convertedRanges.sort((a, b) -> a.compareTo(b));
        convertedRanges = Range.mergeOverlappingRangesIn(convertedRanges);
        if (!Range.isListOfRangesValid(convertedRanges)) {
            throw new RuntimeException("convertedRanges is an invalid List of SeedRanges");
        }
        return convertedRanges;
    }

    public SeedRange merge(SeedRange... seedRanges) {
        if (seedRanges.length == 0) {
            throw new RuntimeException("seedRanges is empty");
        }

        long min = this.getStart();
        long max = this.getEnd();

        for (int index = 0; index < seedRanges.length; index++) {
            min = Math.min(min, seedRanges[index].getStart());
            max = Math.max(max, seedRanges[index].getEnd());
        }

        return new SeedRange(min, max);
    }

    @Override
    public String toString() {
        return "SeedRange [ start=%,15d, end=%,15d ]".formatted(this.getStart(), this.getEnd());
    }

}
