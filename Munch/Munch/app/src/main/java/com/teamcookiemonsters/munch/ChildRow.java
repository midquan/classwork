package com.teamcookiemonsters.munch;

import android.widget.Button;

/**
 * Created by Justin Tse on 10/24/2017.
 */

//defines child row
public class ChildRow {
    private int icon;
    private String text;

    public ChildRow(int icon, String text) {
        this.icon = icon;
        this.text = text;
    }

    //gets icon
    public int getIcon() {
        return icon;
    }

    //sets icon
    public void setIcon(int icon) {
        this.icon = icon;
    }

    //gets text
    public String getText() {
        return text;
    }

    //sets text
    public void setText(String text) {
        this.text = text;
    }
}
