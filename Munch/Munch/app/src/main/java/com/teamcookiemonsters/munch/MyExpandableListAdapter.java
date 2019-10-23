package com.teamcookiemonsters.munch;

import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.text.Layout;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import org.w3c.dom.Text;

import java.lang.reflect.Array;
import java.util.ArrayList;

import static com.teamcookiemonsters.munch.Main2Activity.rAddresses1;
import static com.teamcookiemonsters.munch.Main2Activity.rAddresses2;
import static com.teamcookiemonsters.munch.Main2Activity.rAddresses3;
import static com.teamcookiemonsters.munch.Main2Activity.rCities;
import static com.teamcookiemonsters.munch.Main2Activity.rCountries;
import static com.teamcookiemonsters.munch.Main2Activity.rLatitudes;
import static com.teamcookiemonsters.munch.Main2Activity.rLongitudes;
import static com.teamcookiemonsters.munch.Main2Activity.rNames;
import static com.teamcookiemonsters.munch.Main2Activity.rPhones;
import static com.teamcookiemonsters.munch.Main2Activity.rPrice;
import static com.teamcookiemonsters.munch.Main2Activity.rRating;
import static com.teamcookiemonsters.munch.Main2Activity.rStates;
import static com.teamcookiemonsters.munch.Main2Activity.rZipCodes;

// adapter for expandable list
public class MyExpandableListAdapter extends BaseExpandableListAdapter {

    String restaurantName;
    //public Object restaurantAddress;
    String restaurantPhone;
    String restaurantURL;
    String restaurantAddress1;
    String restaurantAddress2;
    String restaurantAddress3;
    String restaurantCity;
    String restaurantState;
    String restaurantCountry;
    String restaurantZipCode;
    Double restaurantLatitude;
    Double restaurantLongitude;
    //Boolean restaurantIsOpen;
    String restaurantPrice;
    Double restaurantRating;

    String sOpenNow;
    String sDollars;

    private Context context;
    private ArrayList<ParentRow> parentRowList;
    private ArrayList<ParentRow> originalList;
    //public int childIndex;

    public MyExpandableListAdapter(Context context, ArrayList<ParentRow> originalList){
        this.context = context;
        this.parentRowList = new ArrayList<>();
        this.parentRowList.addAll(originalList);
        this.originalList = new ArrayList<>();
        this.originalList.addAll(originalList);
    }

    //number of parent row
    @Override
    public int getGroupCount() {
        return parentRowList.size();
    }

    //number of child rows
    @Override
    public int getChildrenCount(int groupPosition) {
        return parentRowList.get(groupPosition).getChildList().size();
    }

    //gets the parent row containing the child row
    @Override
    public Object getGroup(int groupPosition) {
        return parentRowList.get(groupPosition);
    }

    //gets child row
    @Override
    public Object getChild(int groupPosition, int childPosition) {
        return parentRowList.get(groupPosition).getChildList().get(childPosition);
    }

    //gets location of child row's id (the upper layer list)
    @Override
    public long getGroupId(int groupPosition) {
        return groupPosition;
    }

    //gets the child row id
    @Override
    public long getChildId(int groupPosition, int childPosition) {
        return childPosition;
    }

    //checks ids
    @Override
    public boolean hasStableIds() {
        return true;
    }

    //gets group view
    @Override
    public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup viewGroup) {
        ParentRow parentRow = (ParentRow) getGroup(groupPosition);

        if (convertView == null){
            LayoutInflater layoutInflater = (LayoutInflater)
                    context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = layoutInflater.inflate(R.layout.parent_row, null);
        }
        TextView heading = (TextView) convertView.findViewById(R.id.parent_text);

        heading.setText(parentRow.getName().trim());
        return convertView;
    }

    //gets child view
    @Override
    public View getChildView(int groupPosition, final int childPosition, boolean isLastChild, View convertView, ViewGroup viewGroup) {
        ChildRow childRow = (ChildRow) getChild(groupPosition, childPosition);

        ViewHolder mainViewholder = null;
        if (convertView == null){
            LayoutInflater layoutInflater = (LayoutInflater)
                    context.getSystemService(context.LAYOUT_INFLATER_SERVICE);
            convertView = layoutInflater.inflate(R.layout.child_row, null);
            ViewHolder viewHolder = new ViewHolder();
            //viewHolder.viewButton = (Button) convertView.findViewById(R.id.munch_button);
            convertView.setTag(viewHolder);
        }
        mainViewholder = (ViewHolder) convertView.getTag();
        ImageView childIcon = (ImageView) convertView.findViewById(R.id.child_icon);
        childIcon.setImageResource(childRow.getIcon());

        final TextView childText = (TextView) convertView.findViewById(R.id.child_text);
        childText.setText(childRow.getText().trim());

        final View finalConvertView = convertView;

        // The specific item ID is stored in childposition
        // It is accessible using the KeyValueDB class, which uses shared preferences to access id from anywhere in the application
        // If you don't know how to access
        /*
        mainViewholder.viewButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                /*
                Toast.makeText(finalConvertView.getContext()
                        , "Button PRESS id is " + childPosition
                        //, childText.getText()
                        , Toast.LENGTH_SHORT).show();
                KeyValueDB.setIntId(context, childPosition);
            }
        });
        */

        childText.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {

                int itemIndex = childPosition;

                restaurantName = rNames[itemIndex];
                //restaurantAddress = rAddresses[itemIndex];
                restaurantPhone = rPhones[itemIndex];
                //restaurantURL = rURLs[itemIndex];
                restaurantAddress1 = rAddresses1[itemIndex];
                restaurantAddress2 = rAddresses2[itemIndex];
                restaurantAddress3 = rAddresses3[itemIndex];
                restaurantCity = rCities[itemIndex];
                restaurantState = rStates[itemIndex];
                restaurantCountry = rCountries[itemIndex];
                restaurantZipCode = rZipCodes[itemIndex];
                restaurantLatitude = rLatitudes[itemIndex];
                restaurantLongitude = rLongitudes[itemIndex];
                //restaurantIsOpen = rIsOpen[itemIndex];
                restaurantPrice = rPrice[itemIndex];
                restaurantRating = rRating[itemIndex];

                Intent showInfoIntent = new Intent(context, RestInfoActivity.class);

                // pass restaurant info to the activity
                showInfoIntent.putExtra("name", restaurantName);
                showInfoIntent.putExtra("phone", restaurantPhone);
                showInfoIntent.putExtra("address1", restaurantAddress1);
                showInfoIntent.putExtra("address2", restaurantAddress2);
                showInfoIntent.putExtra("address3", restaurantAddress3);
                showInfoIntent.putExtra("city", restaurantCity);
                showInfoIntent.putExtra("state", restaurantState);
                showInfoIntent.putExtra("country", restaurantCountry);
                showInfoIntent.putExtra("zipcode", restaurantZipCode);
                showInfoIntent.putExtra("latitude", Double.toString(restaurantLatitude));
                showInfoIntent.putExtra("longitude", Double.toString(restaurantLongitude));
                //showInfoIntent.putExtra("url", restaurantURL);
                //showInfoIntent.putExtra("isopen", restaurantIsOpen);
                showInfoIntent.putExtra("price", restaurantPrice);
                showInfoIntent.putExtra("rating", restaurantRating);

                context.startActivity(showInfoIntent);
            }
        });


        return convertView;
    }

    // checks if child is selectable
    @Override
    public boolean isChildSelectable(int groupPosition, int childPosition) {
        return true;
    }

    // filters data
    public void filterData(String query){
        query = query.toLowerCase();
        parentRowList.clear();

        if(query.isEmpty()){
            parentRowList.addAll(originalList);
        }else{
            for (ParentRow parentRow : originalList){
                ArrayList<ChildRow> childList = parentRow.getChildList();
                ArrayList<ChildRow> newList = new ArrayList<ChildRow>();

                for (ChildRow childRow: childList){
                    if (childRow.getText().toLowerCase().contains(query)){
                        newList.add(childRow);
                    }
                }
                if (newList.size() > 0){
                    ParentRow nParentRow = new ParentRow(parentRow.getName(), newList);
                    parentRowList.add(nParentRow);
                }
            }
        }
        notifyDataSetChanged();
    }

    public class ViewHolder {
        Button viewButton;
    }

}
