package de.vw.vwx27wz.day3;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

public class Rolling3Lines {

    private static final List<Character> NON_SYMBOLS = List.of('.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9');
    private List<String> threeLines;
    private String middleLine;

    public Rolling3Lines() {
        this.threeLines = new ArrayList<>();
        this.threeLines.addAll(List.of("", "", ""));
        this.middleLine = this.threeLines.get(1);
    }

    public void add(String line) {
        this.threeLines.remove(0);
        this.threeLines.add(line);
        this.middleLine = this.threeLines.get(1);
    }

    public int getSumOfGearsOfMiddleLine() {
        int sum = 0;

        for (int i = 0; i < this.middleLine.length(); i++) {
            if (this.middleLine.charAt(i) == '*') {
                sum += this.getValueIfGear(i);
            }
        }

        return sum;
    }

    private int getValueIfGear(int index) {
        List<NumberInString> adjacentNumbers = this.getAdjacentNumbers(index);
        if (adjacentNumbers.size() == 2) {
            return adjacentNumbers.get(0).getValue() * adjacentNumbers.get(1).getValue();
        }
        return 0;
    }

    private List<NumberInString> getAdjacentNumbers(int index) {
        List<NumberInString> adjacentNumbers = new ArrayList<>();
        for (String line : this.threeLines) {
            if (Character.isDigit(line.charAt(index))) {
                adjacentNumbers.add(new NumberInString(line, index));
            } else {
                if (index > 0 && Character.isDigit(line.charAt(index - 1))) {
                    adjacentNumbers.add(new NumberInString(line, index - 1));
                }
                if (index < line.length() - 1 && Character.isDigit(line.charAt(index + 1))) {
                    adjacentNumbers.add(new NumberInString(line, index + 1));
                }
            }
        }
        return adjacentNumbers;
    }

    public int getSumOfPartNumbersOfMiddleLine() {
        int sum = 0;
        Set<Integer> symbolIndizesInAllThreeLines = getSymbolIndices();
        String line = this.threeLines.get(1);

        for (int i = 0; i < line.length(); i++) {
            Character c = line.charAt(i);
            if (Character.isDigit(c)) {
                NumberWithIndices num = new NumberWithIndices(line, i);
                if (num.isPartNumber(symbolIndizesInAllThreeLines)) {
                    sum += num.getValue();
                }
                i += num.length() - 1;
            }
        }

        return sum;
    }

    private Set<Integer> getSymbolIndices() {
        Set<Integer> symbolIndizesInAllThreeLines = new HashSet<>();
        for (String line : this.threeLines) {
            for (int i = 0; i < line.length(); i++) {
                if (!NON_SYMBOLS.contains(line.charAt(i))) {
                    symbolIndizesInAllThreeLines.add(i);
                }
            }
        }
        return symbolIndizesInAllThreeLines;
    }

}
