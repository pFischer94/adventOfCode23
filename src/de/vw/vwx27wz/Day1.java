package de.vw.vwx27wz;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Day1 {

    private long sum = 0;

    public static void main(String[] args) {
        Day1 d1 = new Day1();
        try (BufferedReader br = Files.newBufferedReader(Paths.get("inputs/input1.txt"))) {
            br.lines().forEach(line -> {
                d1.sum += getValueFromLine(line);
            });
        } catch (IOException e) {
            e.printStackTrace();
        }
        System.out.println(d1.sum);
    }

    private static long getValueFromLine(String line) {
        String stripped = line
                .replaceAll("one", "o1ne")
                .replaceAll("two", "t2wo")
                .replaceAll("three", "t3hree")
                .replaceAll("four", "f4our")
                .replaceAll("five", "f5ive")
                .replaceAll("six", "s6ix")
                .replaceAll("seven", "s7even")
                .replaceAll("eight", "e8ight")
                .replaceAll("nine", "n9ine")
                .replaceAll("zero", "z0ero")
                .replaceAll("\\D", "");
        return Integer.parseInt("" + stripped.charAt(0) + stripped.charAt(stripped.length() - 1));
    }

}
