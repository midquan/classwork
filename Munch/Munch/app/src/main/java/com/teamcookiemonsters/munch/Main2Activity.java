package com.teamcookiemonsters.munch;

import android.app.SearchManager;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.net.Uri;
import android.os.AsyncTask;
import android.support.v4.view.MenuItemCompat;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ExpandableListView;
import android.widget.ListView;
import android.widget.SearchView;
import android.widget.Toast;

import com.yelp.fusion.client.connection.YelpFusionApi;
import com.yelp.fusion.client.connection.YelpFusionApiFactory;
import com.yelp.fusion.client.models.Business;
import com.yelp.fusion.client.models.SearchResponse;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.lang.*;
import java.util.Random;
import java.util.concurrent.TimeUnit;

import retrofit2.Call;
import retrofit2.Response;

import android.location.Location;
import android.location.LocationManager;

import static junit.framework.Assert.assertNotNull;

/*
 * Includes Scrollable List view that is searchable with restaurant information
 */

public class Main2Activity extends AppCompatActivity implements SearchView.OnQueryTextListener, SearchView.OnCloseListener {

    private SearchManager searchManager;
    private android.widget.SearchView searchView;
    private MyExpandableListAdapter listAdapter;
    private ExpandableListView myList;
    private ArrayList<ParentRow> parentList = new ArrayList<ParentRow>();
    private ArrayList<ParentRow> showTheseParentList = new ArrayList<ParentRow>();
    private MenuItem searchItem;

    public String clientID = "eJuUlcITJQl5ZFtbE-Vs6g";
    public String clientSecret = "q79eV6MADDyFMboJWaBNg41qaxBsAiAkxhElntcYQr2FfaCJPigDfJn4hJvuq97A";
    public String web = "https://api.yelp.com/oauth2/token";
    public String accessToken = "h0hbwDp-INaIDxBnvI75S9GNpokFCIiUq6k8PG6ZSvS96o8pJFWLtBpvNGhXrb6qUVNoHdo_cifBSv-W5EooyI2AEceKbXlhHUWDsqz8A6bCCGk1wKkY8xIwnZ__WXYx";

    Thread t;

    public String testOne;
    public YelpFusionApi mYelpFusionApi;
    public YelpFusionApiFactory apiFactory;
    public Map<String, String> mParams;
    public static int listDisplay;
    public static int listEnd;
    public int listLength;
    public int realListLength;
    public static int size = 15;

    //SearchResponse response;

    // data arrays for items to be listed and displayed in search results
    public static String[] rNames = new String[size];
    //Object[] rAddresses = new Object[20];
    public static String[] rPhones = new String[size];
    //String[] rURLs = new String[20];
    public static String[] rImageURLs = new String[size];
    public static String[] rAddresses1 = new String[size];
    public static String[] rAddresses2 = new String[size];
    public static String[] rAddresses3 = new String[size];
    public static String[] rCities = new String[size];
    public static String[] rStates = new String[size];
    public static String[] rCountries = new String[size];
    public static String[] rZipCodes = new String[size];
    public static Double[] rLatitudes = new Double[size];
    public static Double[] rLongitudes = new Double[size];
    //Boolean[] rIsOpen = new Boolean[20];
    public static String[] rPrice = new String[size];
    public static Double[] rRating = new Double[size];

    // data place holders for a restaurant to be looked at
    public int randomIndex;
    public String restaurantName;
    //public Object restaurantAddress;
    public String restaurantPhone;
    public String restaurantURL;
    public String restaurantAddress1;
    public String restaurantAddress2;
    public String restaurantAddress3;
    public String restaurantCity;
    public String restaurantState;
    public String restaurantCountry;
    public String restaurantZipCode;
    public Double restaurantLatitude;
    public Double restaurantLongitude;
    //public Boolean restaurantIsOpen;
    public String restaurantPrice;
    public Double restaurantRating;

    public String sOpenNow;
    public String sDollars;
    public SearchItem search;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        Intent intent = getIntent();
        search = (SearchItem)intent.getSerializableExtra("Search");
        String text = search.getSearch();
        listDisplay = search.getStart();
        listLength = search.getLength();


        // Setting up Yelp access
        apiFactory = new YelpFusionApiFactory();
        try {
            //yelpFusionApi = apiFactory.createAPI(clientID, clientSecret);
            mYelpFusionApi = apiFactory.createAPI(accessToken);
        } catch (IOException ex) {
            Log.d("CREATION", "PLEASE WORK");
            //Toast.makeText(this,"Didnt Work",Toast.LENGTH_LONG).show();
        }

        mParams = new HashMap<>();

        sOpenNow = "false";
        sDollars = "1,2,3,4";
        SharedPreferences sharepref = getApplicationContext().getSharedPreferences("MyPref", 0); // 0 - for private mode
        if(sharepref.getString("eOpenNow", null) != null) sOpenNow = sharepref.getString("eOpenNow", null);
        if(sharepref.getString("eDollars", null) != null) sDollars = sharepref.getString("eDollars", null);


        // Comment out below for Android Emulator ================================
        /*
        // Location Manager to find longitude and latitude of current location and put into search
        LocationManager lm = (LocationManager)getSystemService(Context.LOCATION_SERVICE);
        Location location = lm.getLastKnownLocation(LocationManager.GPS_PROVIDER);
        double longitude = location.getLongitude();
        double latitude = location.getLatitude();

        String lon = Double.toString(longitude);
        String lat = Double.toString(latitude);

        //setSearch();
        mParams.put("term", text);
        mParams.put("latitude", lat);
        mParams.put("longitude", lon);
        mParams.put("limit", "44");
        mParams.put("radius", "15000");
        mParams.put("open_now", sOpenNow);
        mParams.put("price", sDollars);
        new GetData().execute();
        */
        // =======================================================================


        // Comment out Below for Android Device ----------------------------------

        //System.out.println(sOpenNow);

        mParams.put("term", text);
        mParams.put("latitude", "37.000353");
        mParams.put("longitude", "-122.06314429999998");
        mParams.put("limit", "44");
        mParams.put("radius", "15000");
        mParams.put("open_now", sOpenNow);
        mParams.put("price", sDollars);
        new GetData().execute();

        // -----------------------------------------------------------------------


        // API search delay timer
        try {
            // thread to sleep for 1000 milliseconds
            Thread.sleep(4000);
        } catch (Exception e) {
            Toast.makeText(this,"Didnt Work",Toast.LENGTH_LONG).show();
        }


        /*
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSuportActionBar(toolbar);

        FloatingActionButton fab = (FloatingActionButton) findViewById(R.id.fab);
        fab.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                Snackbar.make(view, "Replace with your own action", Snackbar.LENGTH)
                        .setAction("Action", null).show();
            }
        });
        */

        searchManager = (SearchManager) getSystemService(Context.SEARCH_SERVICE);
        //top layer list
        parentList = new ArrayList<ParentRow>();
        //display the top layer list
        showTheseParentList = new ArrayList<ParentRow>();

        //app will crash if display list not called here
        displayList();
        //expands the list of contents
        expandAll();

        Button nextButton = (Button) findViewById(R.id.right_button);

        // Next button for updated page info
        nextButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //Intent naviIntent = new Intent(Intent.ACTION_VIEW, Uri.parse("https://www.google.com/"));
                //startActivity(naviIntent);
                //EditText mEdit;
                //String text;
                //mEdit = (EditText)findViewById(R.id.searchText);
                //text = mEdit.getText().toString();
                //SearchItem newSearch = new SearchItem();
                //newSearch.setSearch(text);
                if(listLength > size) {
                    search.setStart(listDisplay + size);
                    search.setLength(listLength - size);
                }
                Intent intent = new Intent(Main2Activity.this, Main2Activity.class);
                intent.putExtra("Search", search);
                finish();
                startActivity(intent);
            }
        });

        //Button viewButton = (Button) findViewById(R.id.munch_button);
        //ExpandableListView lv = (ExpandableListView) findViewById(R.id.results_list);
        //lv.setAdapter(new MyExpandableListAdapter(this,R.layout.child_row, ));
        myList.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> parent, View view, int position, long id) {
                Toast.makeText(Main2Activity.this,"List item position at " + position, Toast.LENGTH_SHORT).show();
            }
        });

        // "Pick for Me" button
        final Button randomButton = (Button) findViewById(R.id.random_button);
        randomButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // get random index
                randomIndex = getRandomInt();

                // get restaurant info
                restaurantName = rNames[randomIndex];
                //restaurantAddress = rAddresses[randomIndex];
                restaurantPhone = rPhones[randomIndex];
                //restaurantURL = rURLs[randomIndex];
                restaurantAddress1 = rAddresses1[randomIndex];
                restaurantAddress2 = rAddresses2[randomIndex];
                restaurantAddress3 = rAddresses3[randomIndex];
                restaurantCity = rCities[randomIndex];
                restaurantState = rStates[randomIndex];
                restaurantCountry = rCountries[randomIndex];
                restaurantZipCode = rZipCodes[randomIndex];
                restaurantLatitude = rLatitudes[randomIndex];
                restaurantLongitude = rLongitudes[randomIndex];
                //restaurantIsOpen = rIsOpen[randomIndex];
                restaurantPrice = rPrice[randomIndex];
                restaurantRating = rRating[randomIndex];

                // "target" restaurant info activity
                Intent restInfoIntent = new Intent((Main2Activity.this), RestInfoActivity.class);

                // pass restaurant info to the activity
                restInfoIntent.putExtra("name", restaurantName);
                restInfoIntent.putExtra("phone", restaurantPhone);
                restInfoIntent.putExtra("address1", restaurantAddress1);
                restInfoIntent.putExtra("address2", restaurantAddress2);
                restInfoIntent.putExtra("address3", restaurantAddress3);
                restInfoIntent.putExtra("city", restaurantCity);
                restInfoIntent.putExtra("state", restaurantState);
                restInfoIntent.putExtra("country", restaurantCountry);
                restInfoIntent.putExtra("zipcode", restaurantZipCode);
                restInfoIntent.putExtra("latitude", Double.toString(restaurantLatitude));
                restInfoIntent.putExtra("longitude", Double.toString(restaurantLongitude));
                //restInfoIntent.putExtra("url", restaurantURL);
                //restInfoIntent.putExtra("isopen", restaurantIsOpen);
                restInfoIntent.putExtra("price", restaurantPrice);
                restInfoIntent.putExtra("rating", restaurantRating);

                // launch activity
                startActivity(restInfoIntent);
            }
        });
    }

    //load list data
    private void loadData() {
        ArrayList<ChildRow> childRows = new ArrayList<ChildRow>();
        ParentRow parentRow = null;

        /*
        childRows.add(new ChildRow(R.mipmap.ic_launcher_round
                , "Text1"));
        childRows.add(new ChildRow(R.mipmap.ic_launcher_round
                , testOne));
        */

        for(int i = 0; i < size; i++){
            if(rNames[i] != null) {
                childRows.add(new ChildRow(R.mipmap.ic_launcher_round, rNames[i]));
            }
        }

        parentRow = new ParentRow("Restaurant", childRows);
        parentList.add(parentRow);

    }

    //expand top layer list
    private void expandAll() {
        int count = listAdapter.getGroupCount();
        for (int i = 0; i < count; i++) {
            myList.expandGroup(i);
        }
    }

    // show list
    private void displayList() {
        loadData();

        myList = (ExpandableListView) findViewById(R.id.results_list);
        listAdapter = new MyExpandableListAdapter(Main2Activity.this, parentList);
        myList.setAdapter(listAdapter);
    }


    // gets random integer for the index i in rNames[i] which is the list used to display search results
    private int getRandomInt() {
        int min = 1;
        int max = size;
        Random rand = new Random();
        int randInt = rand.nextInt((max-min)+1)+min;
        return randInt;
    }

    //creates options menu
    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        //inflate the menu; this adds items to the aciton bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        searchItem = menu.findItem(R.id.action_search);
        searchView = (SearchView) MenuItemCompat.getActionView(searchItem);
        searchView.setSearchableInfo(searchManager.getSearchableInfo(getComponentName()));
        searchView.setIconifiedByDefault(false);
        searchView.setOnQueryTextListener(this);
        searchView.setOnCloseListener(this);
        searchView.requestFocus();

        return true;
    }

    //initialize for results of search
    @Override
    public boolean onClose() {
        listAdapter.filterData("");
        expandAll();
        return false;
    }

    //does search
    @Override
    public boolean onQueryTextSubmit(String query) {
        listAdapter.filterData(query);
        expandAll();
        return false;
    }

    //filters results
    @Override
    public boolean onQueryTextChange(String newText) {
        listAdapter.filterData(newText);
        expandAll();
        return false;
    }

    //gets yelp data
    class GetData extends AsyncTask<String, String, String> {

        @Override
        protected String doInBackground(String... params) {
            Call<SearchResponse> call = mYelpFusionApi.getBusinessSearch(mParams);
            Response<SearchResponse> response = null;
            try {
                response = call.execute();
            } catch (IOException e){
                e.printStackTrace();
            }
            //loads data into lists
            if(response != null){
                int i = 0;
                if(listLength == 0){
                    listLength = response.body().getBusinesses().size();
                }
                for(int k = listDisplay; k < (listLength + listDisplay); k++) {
                    if(listLength < size){
                        realListLength = listLength;
                    }
                    if(i == size){
                        realListLength = i;
                        break;
                    }
                    if(response.body().getBusinesses().get(k).getName() != null) {
                        Log.v("Businesses", response.body().getBusinesses().get(k).getName());
                        rNames[i] = response.body().getBusinesses().get(k).getName();
                        //rAddresses[i] = response.body().getBusinesses().get(i).getLocation();
                        rPhones[i] = response.body().getBusinesses().get(k).getDisplayPhone();
                        //rURLs[i] = response.body().getBusinesses().get(i).getUrl();
                        rImageURLs[i] = response.body().getBusinesses().get(k).getImageUrl();
                        rAddresses1[i] = response.body().getBusinesses().get(k).getLocation().getAddress1();
                        rAddresses2[i] = response.body().getBusinesses().get(k).getLocation().getAddress2();
                        rAddresses3[i] = response.body().getBusinesses().get(k).getLocation().getAddress3();
                        rCities[i] = response.body().getBusinesses().get(k).getLocation().getCity();
                        rStates[i] = response.body().getBusinesses().get(k).getLocation().getState();
                        rCountries[i] = response.body().getBusinesses().get(k).getLocation().getCountry();
                        rZipCodes[i] = response.body().getBusinesses().get(k).getLocation().getZipCode();
                        rLatitudes[i] = response.body().getBusinesses().get(k).getCoordinates().getLatitude();
                        rLongitudes[i] = response.body().getBusinesses().get(k).getCoordinates().getLongitude();
                        //rIsOpen[i] = response.body().getBusinesses().get(i).getHours().get(i).getIsOpenNow();
                        rPrice[i] = response.body().getBusinesses().get(k).getPrice();
                        rRating[i] = response.body().getBusinesses().get(k).getRating();
                    }
                    i++;
                }
            }
            return null;
        }
    }

    /*
    // clears arrays on back press
    public void onBackPressed() {
        Arrays.fill(rNames, null);
        Arrays.fill(rPhones, null);
        Arrays.fill(rImageURLs, null);
        Arrays.fill(rAddresses1, null);
        Arrays.fill(rAddresses2, null);
        Arrays.fill(rAddresses3, null);
        Arrays.fill(rCities, null);
        Arrays.fill(rStates, null);
        Arrays.fill(rCountries, null);
        Arrays.fill(rZipCodes, null);
        Arrays.fill(rLatitudes, null);
        Arrays.fill(rLongitudes, null);
        Arrays.fill(rPrice, null);
        Arrays.fill(rRating, null);

        finish();
    }
    */
}
