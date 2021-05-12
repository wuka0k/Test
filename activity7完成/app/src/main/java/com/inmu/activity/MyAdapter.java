package com.inmu.activity;

import android.content.Context;
import android.media.Image;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Adapter;
import android.widget.ArrayAdapter;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;

import org.w3c.dom.Text;

import java.util.List;


public class MyAdapter extends BaseAdapter {

    List<Item> list;
    Context context;

    //利用构造方法把数据传进adapter内部
    public MyAdapter(Context context, List<Item> list) {
        this.list = list;
        this.context = context;
    }
    //1.返回条目数量
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

    //返回每一个条目
    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        ViewHolder holder = null;
        //第一个优化点:复用view
        if(view==null){
              view = LayoutInflater.from(context).inflate(R.layout.activity_item,viewGroup,false);
              //优化2:利用viewholder对控件状态进行保存
              holder = new ViewHolder(view);
            //把holder保存在view对象里面
              view.setTag(holder);
       }else{
            holder = (ViewHolder) view.getTag();
        }
        Item item = list.get(i);
        holder.tv_name.setText(item.getName());
        holder.tv_content.setText(item.getContent());
        holder.tv_date.setText(item.getDate());
        holder.iv.setImageResource(R.mipmap.ic_launcher);
        return view;
    }
}

class ViewHolder{

    View view;
    TextView tv_name;
    TextView tv_content;
    TextView tv_date;
    ImageView iv;

    public ViewHolder(View view){
        this.view = view;
        tv_name= view.findViewById(R.id.tv_name);
        tv_content= view.findViewById(R.id.tv_content);
        tv_date= view.findViewById(R.id.tv_date);
        iv = view.findViewById(R.id.iv1);
    }
}
