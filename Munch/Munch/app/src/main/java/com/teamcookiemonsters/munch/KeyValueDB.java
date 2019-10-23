package com.teamcookiemonsters.munch;

import android.content.Context;
import android.content.SharedPreferences;

/**
 * Created by Justin Tse on 12/5/2017.
 * Shared Preference object
 */

public class KeyValueDB {
    private SharedPreferences sharedPreferences;
    private static String PREF_NAME = "prefs";

    // Constructor
    public KeyValueDB() {
        // Blank
    }

    // Set Shared Preference
    private static SharedPreferences getPrefs(Context context) {
        return context.getSharedPreferences(PREF_NAME, Context.MODE_PRIVATE);
    }

    // Get key value
    public static int getIntId(Context context) {
        return getPrefs(context).getInt("key", 20);
    }

    // Set key value
    public static void setIntId(Context context, int input) {
        SharedPreferences.Editor editor = getPrefs(context).edit();
        editor.putInt("key", input);
        editor.commit();
    }
}
