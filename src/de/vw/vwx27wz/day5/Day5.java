package de.vw.vwx27wz.day5;

import java.util.List;

import de.vw.vwx27wz.reader.Reader;

public class Day5 {

    public static void main(String[] args) {
        List<String> lines = new Reader("inputs/input5.txt").readLines();
        List<SeedRange> rangesToConvert = SeedRange.readSeedRangesFromLine(lines.get(0));
        List<List<ConversionRange>> conversionTables = ConversionRange.readConversionTablesFromLines(lines);

        for (List<ConversionRange> conversionTable : conversionTables) {
            rangesToConvert = SeedRange.convert(rangesToConvert, conversionTable);
        }

        rangesToConvert.sort((a, b) -> a.compareTo(b));
        System.out.println("amountOfRanges:   " + rangesToConvert.size());
        System.out.println("closest location: " + rangesToConvert.get(0).getStart());
    }

}
