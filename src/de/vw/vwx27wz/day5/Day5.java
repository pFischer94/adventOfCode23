package de.vw.vwx27wz.day5;

import java.util.List;

import de.vw.vwx27wz.reader.Reader;

public class Day5 {

    public static void main(String[] args) {
        List<String> lines = new Reader("inputs/input5.txt").readLines();
        List<SeedRange> rangesToConvert = SeedRange.readSeedRangesFromLine(lines.get(0));
        List<List<ConversionRange>> conversionTables = ConversionRange.readConversionTablesFromLines(lines);

        print(conversionTables);

        for (List<ConversionRange> conversionTable : conversionTables) {
            rangesToConvert = SeedRange.convert(rangesToConvert, conversionTable);
        }

        rangesToConvert.sort((a, b) -> a.compareTo(b));
        System.out.println("amountOfRanges: " + rangesToConvert.size());
        Range.printRanges(rangesToConvert);
        System.out.println("closest location: " + rangesToConvert.get(0).getStart());
    }

    private static void print(List<List<ConversionRange>> conversionTables) {
        int counter = 1;
        for (List<ConversionRange> table : conversionTables) {
            System.err.println(getMapName(counter));
            counter++;
            Range.printRanges(table);
            System.out.println();
        }
    }

    private static String getMapName(int counter) {
        return switch (counter) {
            case 1 -> "seed-to-soil map:";
            case 2 -> "soil-to-fertilizer map:";
            case 3 -> "fertilizer-to-water map:";
            case 4 -> "water-to-light map:";
            case 5 -> "light-to-temperature map:";
            case 6 -> "temperature-to-humidity map:";
            case 7 -> "humidity-to-location map:";
            case 8 -> "";
            default -> "no map name";
        };
    }

}
