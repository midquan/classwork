package com.teamcookiemonsters.munch;

import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.w3c.dom.Text;

public class RestInfoActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_rest_info);

        // receive passed in restaurant info
        String name = getIntent().getStringExtra("name");
        String phone = getIntent().getStringExtra("phone");
        String address1 = getIntent().getStringExtra("address1");
        String address2 = getIntent().getStringExtra("address2");
        String address3 = getIntent().getStringExtra("address3");
        String city = getIntent().getStringExtra("city");
        String state = getIntent().getStringExtra("state");
        String country = getIntent().getStringExtra("country");
        String zipcode = getIntent().getStringExtra("zipcode");
        final String latitude = getIntent().getStringExtra("latitude");
        final String longitude = getIntent().getStringExtra("longitude");
        //String url = getIntent().getStringExtra("url");
        //String isopen = getIntent().getStringExtra("isopen");
        String price = getIntent().getStringExtra("price");
        Double rating = getIntent().getDoubleExtra("rating", 0.0);
        //convert passed in double to string
        String ratingString = rating.toString();


        // set up textviews
        TextView phoneText = (TextView) findViewById(R.id.phone_text);
        TextView addressText = (TextView) findViewById(R.id.address_text);
        //TextView cityText = (TextView) findViewById(R.id.city_text);
        //TextView stateText = (TextView) findViewById(R.id.state_text);
        //TextView countryText = (TextView) findViewById(R.id.country_text);
        //TextView zipcodeText = (TextView) findViewById(R.id.zipcode_text);
        //TextView urlText = (TextView) findViewById(R.id.url_text);
        //TextView isopenText = (TextView) findViewById(R.id.isopen_text);
        TextView priceText = (TextView) findViewById(R.id.price_text);
        TextView ratingText = (TextView) findViewById(R.id.rating_text);

        // concat addresses
        String address = address1 + "\n" + city + ", " + state + " " + zipcode;
        /*
        if (address2 == null || address2 == "" && address3 == null || address3 == "") {
            // keep address as is
        } else if (address3 == null || address3 == "") {
            address = address1 + "\n" + address2;
        } else if (address2 == null || address2 == "") {
            address = address1 + "\n" + address3;
        }
        */

        // display texts
        phoneText.setText(phone);
        addressText.setText(address);
        //cityText.setText(city);
        //stateText.setText(state);
        //countryText.setText(country);
        //zipcodeText.setText(zipcode);
        //urlText.setText(url);
        //isopenText.setText(isopen);
        priceText.setText("Price: " + price);
        ratingText.setText("Rating: " + ratingString);

        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        toolbar.setTitle(name);
        setSupportActionBar(toolbar);

        FloatingActionButton goMap = (FloatingActionButton) findViewById(R.id.map_fab);
        goMap.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String googlemaps = "http://www.google.com/maps/place/"+ latitude + "," + longitude;
                Intent naviIntent = new Intent(Intent.ACTION_VIEW, Uri.parse(googlemaps));
                startActivity(naviIntent);
            }
        });

    }
}
