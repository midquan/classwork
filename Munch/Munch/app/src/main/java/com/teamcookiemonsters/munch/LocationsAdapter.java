package com.teamcookiemonsters.munch;

import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.support.v7.widget.RecyclerView;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.TextView;

import java.util.List;

// create adapter extending RecyclerView's adapter
public class LocationsAdapter extends RecyclerView.Adapter<LocationsAdapter.ViewHolder> {

    public class ViewHolder extends RecyclerView.ViewHolder {
        public TextView nameTextView;
        public Button naviButton;

        public ViewHolder(View itemView) {
            super(itemView);

            nameTextView = (TextView) itemView.findViewById(R.id.location_name);
            naviButton = (Button) itemView.findViewById(R.id.navi_button);
        }
    }

    private List<Location> mLocations;
    private Context mContext;

    public LocationsAdapter(Context context, List<Location> locations) {
        mLocations = locations;
        mContext = context;
    }

    // easy access to the context object in the RecyclerView
    private Context getContext() {
        return mContext;
    }

    @Override
    public LocationsAdapter.ViewHolder onCreateViewHolder(ViewGroup parent, int viewType) {
        Context context = parent.getContext();
        LayoutInflater inflater = LayoutInflater.from(context);

        View locationView = inflater.inflate(R.layout.item_layout,parent, false);

        ViewHolder viewHolder = new ViewHolder(locationView);

        return viewHolder;
    }

    @Override
    public void onBindViewHolder(LocationsAdapter.ViewHolder viewHolder, int position) {
        Location location = mLocations.get(position);

        TextView textView = viewHolder.nameTextView;
        textView.setText(location.getName());

        Button button = viewHolder.naviButton;
        //button.setText(location.isopen() ? "Open" : "Closed");
        button.setText("123 FooBar Street\nBlah City, AB\n00000");
        button.setEnabled(location.isopen());
    }

    @Override
    public int getItemCount() {
        return mLocations.size();
    }
}