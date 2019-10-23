package com.teamcookiemonsters.munch;

import android.content.Intent;
import android.content.SharedPreferences;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.CheckBox;
import android.widget.Toast;



public class Main4Activity extends AppCompatActivity {

    // Creates 5 checkboxes for OpenNow and Price Levels
    CheckBox OpenNow;
    CheckBox Dollar1;
    CheckBox Dollar2;
    CheckBox Dollar3;
    CheckBox Dollar4;

    // Default Boolean values for the checkboxes
    boolean bOpenNow = false;
    boolean bDollar1 = true;
    boolean bDollar2 = true;
    boolean bDollar3 = true;
    boolean bDollar4 = true;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main4);

        //Sets Checkboxes attached to xml
        OpenNow = (CheckBox) findViewById(R.id.checkBox1);
        //OpenNow.setChecked(false);
        OpenNow.setOnClickListener(PrefListen);
        //OpenNow.setText("Open Now");
        Dollar1 = (CheckBox) findViewById(R.id.checkBox2);
        //Dollar1.setOnClickListener(this);
        Dollar1.setOnClickListener(PrefListen);
        //Dollar1.setChecked(true);
        Dollar2 = (CheckBox) findViewById(R.id.checkBox3);
        //Dollar2.setOnClickListener(this);
        Dollar2.setOnClickListener(PrefListen);
        //Dollar2.setChecked(true);
        Dollar3 = (CheckBox) findViewById(R.id.checkBox4);
        //Dollar3.setOnClickListener(this);
        Dollar3.setOnClickListener(PrefListen);
        //Dollar3.setChecked(true);
        Dollar4 = (CheckBox) findViewById(R.id.checkBox5);
        //Dollar4.setOnClickListener(this);
        Dollar4.setOnClickListener(PrefListen);
        //Dollar4.setChecked(bDollar4);
    }

    private View.OnClickListener PrefListen = new View.OnClickListener() {
        public void onClick(View v) {
            // do something when the button is clicked

            // Switch statement to handle button presses.
            switch (v.getId() /*to get clicked view id**/) {
                // does case when checkbox1(OpenNow) is clicked
                case R.id.checkBox1:

                    if(OpenNow.isChecked()) bOpenNow = true;
                    else bOpenNow = false;

                    break;

                // does case when checkbox2(Dollar1) is clicked
                case R.id.checkBox2:
                    if(Dollar1.isChecked()) bDollar1 = true;
                    else bDollar1 = false;
                    //System.out.println(bDollar1);
                    break;

                // does case when checkbox3(Dollar2) is clicked
                case R.id.checkBox3:
                    if(Dollar2.isChecked()) bDollar2 = true;
                    else bDollar2 = false;
                    //System.out.println(bDollar2);
                    break;

                // does case when checkbox4(Dollar3) is clicked
                case R.id.checkBox4:
                    if(Dollar3.isChecked()) bDollar3 = true;
                    else bDollar3 = false;
                    //System.out.println(bDollar3);
                    break;

                // does case when checkbox5(Dollar4) is clicked
                case R.id.checkBox5:
                    if(Dollar4.isChecked()) bDollar4 = true;
                    else bDollar4 = false;
                    //System.out.println(bDollar4);
                    break;
                default:
                    break;
            }

        }

    };

    // Saves the preferences for the app onBackPressed into SharedPreferences
    public void onBackPressed(){
        //System.out.println(bOpenNow + " " + bDollar1 + " " + bDollar2 + " " + bDollar3+ " " + bDollar4);
        String sOpenNow = Boolean.toString(bOpenNow);
        String sDollars = dollarsignconvert();
        // Checks for bad input and forces it to default input
        if(sDollars.equals("bad input")){
            Toast.makeText(Main4Activity.this, "Warning!! If no price level is chosen the app will default to all price levels.", Toast.LENGTH_SHORT).show();
            sDollars = "1,2,3,4";
        }
        SharedPreferences pref = getApplicationContext().getSharedPreferences("MyPref", 0); // 0 - for private mode
        SharedPreferences.Editor editor = pref.edit();
        editor.putString("eOpenNow", sOpenNow);
        editor.putString("eDollars", sDollars);
        editor.commit();

        finish();
    }

    // Converts the 4 different price levels into a string that can be accepted by Yelp API
    public String dollarsignconvert (){
        if(bDollar1 && !(bDollar2) && !(bDollar3) && !(bDollar4)) return "1";
        else if(!(bDollar1) && bDollar2 && !(bDollar3) && !(bDollar4)) return "2";
        else if(!(bDollar1) && !(bDollar2) && bDollar3 && !(bDollar4)) return "3";
        else if(!(bDollar1) && !(bDollar2) && !(bDollar3) && bDollar4) return "4";
        else if(bDollar1 && bDollar2 && !(bDollar3) && !(bDollar4)) return "1,2";
        else if(bDollar1 && !(bDollar2) && bDollar3 && !(bDollar4)) return "1,3";
        else if(bDollar1 && !(bDollar2) && !(bDollar3) && bDollar4) return "1,4";
        else if(!(bDollar1) && bDollar2 && bDollar3 && !(bDollar4)) return "2,3";
        else if(!(bDollar1) && bDollar2 && !(bDollar3) && bDollar4) return "2,4";
        else if(!(bDollar1) && !(bDollar2) && bDollar3 && bDollar4) return "3,4";
        else if(bDollar1 && bDollar2 && bDollar3 && !(bDollar4)) return "1,2,3";
        else if(bDollar1 && bDollar2 && !(bDollar3) && bDollar4) return "1,2,4";
        else if(bDollar1 && !(bDollar2) && bDollar3 && bDollar4) return "1,3,4";
        else if(!(bDollar1) && bDollar2 && bDollar3 && bDollar4) return "2,3,4";
        else if(bDollar1 && bDollar2 && bDollar3 && bDollar4) return "1,2,3,4";
        // bad input causes default to be used
        else return "bad input";
    }

}