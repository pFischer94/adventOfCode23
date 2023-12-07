package de.vw.vwx27wz.day3;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;

public class NumberWithIndices {

    private int value;
    private List<Integer> indices;

    public NumberWithIndices(String line, int index) {
        this.indices = new ArrayList<>();
        String characters = "" + line.charAt(index);

        this.indices.add(index);
        while (++index < line.length() && Character.isDigit(line.charAt(index))) {
            this.indices.add(index);
            characters += line.charAt(index);
        }
        this.value = Integer.parseInt(characters);
    }

    public int length() {
        return this.indices.size();
    }

    public boolean isPartNumber(Set<Integer> symbolIndizesInAllThreeLines) {
        for (int adjacentIndex = firstAdjacentIndex(); adjacentIndex <= lastAdjacentIndex(); adjacentIndex++) {
            if (symbolIndizesInAllThreeLines.contains(adjacentIndex)) {
                return true;
            }
        }
        return false;
    }

    private int firstAdjacentIndex() {
        return this.indices.get(0) - 1;
    }

    private int lastAdjacentIndex() {
        return this.indices.get(this.indices.size() - 1) + 1;
    }

    public int getValue() {
        return this.value;
    }

}
