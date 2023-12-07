package de.vw.vwx27wz.day3;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Day3 {

    public static void main(String[] args) {
        int sum = 0;
        Rolling3Lines rolling3Lines = new Rolling3Lines();

        try (BufferedReader br = Files.newBufferedReader(Paths.get("inputs/input3.txt"))) {
            String line = br.readLine();

            while (line != null) {
                rolling3Lines.add(line);
//                sum += r3L.getSumOfPartNumbersOfMiddleLine();
                sum += rolling3Lines.getSumOfGearsOfMiddleLine();
                System.out.println(line + " -> " + sum);
                line = br.readLine();
            }

            rolling3Lines.add("");
//            sum += r3L.getSumOfPartNumbersOfMiddleLine();

        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println(sum);
    }

}
