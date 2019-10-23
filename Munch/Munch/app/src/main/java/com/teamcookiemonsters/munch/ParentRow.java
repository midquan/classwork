package com.teamcookiemonsters.munch;

import java.util.ArrayList;

/**
 * Created by Justin Tse on 10/24/2017.
 */
//top layer array definition
public class ParentRow {
    private String name;
    private ArrayList<ChildRow> childList;

    public ParentRow(String name, ArrayList<ChildRow> childList) {
        this.name = name;
        this.childList = childList;
    }

    //gets name
    public String getName() {
        return name;
    }

    //sets name
    public void setName(String name) {
        this.name = name;
    }

    //gets child list
    public ArrayList<ChildRow> getChildList() {
        return childList;
    }

    //sets child list
    public void setChildList(ArrayList<ChildRow> childList) {
        this.childList = childList;
    }
}
