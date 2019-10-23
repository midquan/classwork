package com.teamcookiemonsters.munch;

import java.util.ArrayList;

public class Location {
    private String lName;
    private boolean lopen;
    private double ldistance;
    private String lreason;


    public Location(String name, boolean open/*, double distance, String reason*/) {
        lName = name;
        lopen = open;
        //ldistance = distance;
        //lreason = reason;
    }

    public String getName() {
        return lName;
    }

    public boolean isopen() {
        return lopen;
    }

    // temp location generator ------------------------------------------------------
    private static int lastLocationID = 0;

    public static ArrayList<Location> createLocationsList(int numLocations) {
        ArrayList<Location> locations = new ArrayList<Location>();

        for (int i = 1; i <= numLocations; i++) {
            locations.add(new Location(++lastLocationID + ". " + "Restaurant", i <= numLocations/2));
        }
        return locations;
    }
}