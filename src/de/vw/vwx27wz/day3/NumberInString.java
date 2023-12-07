package de.vw.vwx27wz.day3;

public class NumberInString {

    private int value;

    public NumberInString(String line, int index) {
        String numStr = "" + line.charAt(index);
        int indexToCheck = index - 1;

        while (indexToCheck >= 0 && Character.isDigit(line.charAt(indexToCheck))) {
            numStr = line.charAt(indexToCheck) + numStr;
            indexToCheck--;
        }

        indexToCheck = index + 1;
        while (indexToCheck < line.length() && Character.isDigit(line.charAt(indexToCheck))) {
            numStr += line.charAt(indexToCheck);
            indexToCheck++;
        }

        this.value = Integer.parseInt(numStr);
    }

    public int getValue() {
        return this.value;
    }

}
