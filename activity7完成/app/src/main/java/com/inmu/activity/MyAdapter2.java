package com.inmu.activity;

import android.content.Context;
import android.media.Image;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import java.util.List;

public class MyAdapter2 extends BaseAdapter {

    List<Item2> list;
    Context context;

    //利用构造方法把数据传进adapter内部
    public MyAdapter2(Context context, List<Item2> list) {
        this.list = list;
        this.context = context;
    }


    @Override
    public int getCount() {
        return list.size();
    }

    @Override
    public Object getItem(int i) {
        return list.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {

        if(view==null) {
            view = LayoutInflater.from(context).inflate(R.layout.activity_item2, viewGroup, false);
        }

        ImageView iv = view.findViewById(R.id.iv);
        TextView descrip = view.findViewById(R.id.tv_descrip);

        Item2 item1 = list.get(i);
        iv.setImageResource(item1.getResid());
        descrip.setText(item1.getDescription());

        return view;
    }
}

