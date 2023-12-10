package de.vw.vwx27wz;

import java.io.BufferedReader;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class Day2 {

    private int reds = 12;
    private int greens = 13;
    private int blues = 14;
    private int sum = 0;

    public static void main(String[] args) {
        Day2 d2 = new Day2();

        try (BufferedReader br = Files.newBufferedReader(Paths.get("inputs/input2.txt"))) {
            br.lines().forEach(line -> {
                d2.sum += d2.getPowerOfMinimalSet(line);
            });
        } catch (IOException e) {
            e.printStackTrace();
        }

        System.out.println(d2.sum);
    }

    private int getPowerOfMinimalSet(String line) {
        String[] splitted = line.split(":");
        String sets = splitted[1].trim();

        int redMax = getMaxFromSets(sets, "red");
        int greenMax = getMaxFromSets(sets, "green");
        int blueMax = getMaxFromSets(sets, "blue");

        return redMax * greenMax * blueMax;
    }

    @SuppressWarnings("unused")
    private int getIdFromGameIfPossible(String line) {
        String[] splitted = line.split(":");
        String game = splitted[0];
        String sets = splitted[1].trim();

        int id = getIdFromGame(game);
        int redMax = getMaxFromSets(sets, "red");
        int greenMax = getMaxFromSets(sets, "green");
        int blueMax = getMaxFromSets(sets, "blue");

        if (redMax <= this.reds && greenMax <= this.greens && blueMax <= this.blues) {
            return id;
        }
        return 0;
    }

    private static int getMaxFromSets(String sets, String color) {
        int max = 0;
        String[] splittedSets = sets.split(";");

        for (String set : splittedSets) {
            max = Math.max(max, getAmountFromSet(set.trim(), color));
        }

        return max;
    }

    private static int getAmountFromSet(String set, String color) {
        String[] splittedCubes = set.split(",");

        for (String cube : splittedCubes) {
            if (cube.contains(color)) {
                return getAmountOfCube(cube.trim());
            }
        }

        return 0;
    }

    private static int getAmountOfCube(String trim) {
        String[] split = trim.split(" ");
        return Integer.parseInt(split[0]);
    }

    private static int getIdFromGame(String game) {
        return Integer.parseInt(game.split(" ")[1]);
    }

}
