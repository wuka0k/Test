package com.inmu.activity;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.viewpager.widget.PagerAdapter;

import java.util.List;
import java.util.Timer;
import java.util.TimerTask;

public class Mydapter3 extends PagerAdapter {

    Context context;
    List<Item2> list;

    public Mydapter3(Context context,List<Item2> list){
        this.context=context;
        this.list=list;
    }

    @Override
    public int getCount() {
//        return list.size();
        return 10000;
    }

    @NonNull
    @Override
    public Object instantiateItem(@NonNull ViewGroup container, int position) {
        View view = LayoutInflater.from(context).inflate(R.layout.activity_item3, null, false);
        ImageView page_iv = view.findViewById(R.id.page_iv);
        TextView page_tv = view.findViewById(R.id.page_tv);
        Item2 item2=list.get(position%4);
        page_iv.setBackgroundResource(item2.getResid());
        page_tv.setText(item2.getDescription());



        container.addView(view);
        return view;
    }

    @Override
    public void destroyItem(@NonNull ViewGroup container, int position, @NonNull Object object) {
        container.removeView((View)object);
    }

    @Override
    public boolean isViewFromObject(@NonNull View view, @NonNull Object object) {
        return view == object;
    }
}
