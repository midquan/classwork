package com.teamcookiemonsters.munch;

import android.widget.EditText;
import java.io.Serializable;

/**
 * Created by Sanjeet on 11/23/2017.
 * Search Object passed to List Activity
 */

public class SearchItem implements Serializable {
    public static String search;
    public static int start;
    public static int length;

    public SearchItem() {};

    public SearchItem(String input, int startInput){
        search = input;
        start = startInput;
    }

    public String getSearch() {return search;}

    public void setSearch(String actSearch) {
        search = actSearch;
    }

    public int getStart() {return start;}

    public void setStart(int startInput) {
        start = startInput;
    }

    public int getLength() {return length;}

    public void setLength(int lengthInput) {
        length = lengthInput;
    }
}

