package com.inmu.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.List;

public class ListViewActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_listview);

        //模拟数据
        List<Item> list = new ArrayList<Item>();
        for (int i=1;i<11;i++){
            Item item = new Item();
            item.setName("xm"+i);
            item.setContent(i+"号吃饭了没？");
            item.setDate("2021/04/"+i);
            list.add(item);
        }


        //1.获取listview对象
        ListView listview = findViewById(R.id.lv);
        //3.创建适配器（简单布局，adnroid自带的）
        MyAdapter adapter = new MyAdapter(this,list);
        //2.给listview设置数据填充器
        listview.setAdapter(adapter);
        //4.给条目设置点击事件
        listview.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                TextView tv_name = view.findViewById(R.id.tv_name);
                Toast.makeText(ListViewActivity.this,tv_name.getText(),Toast.LENGTH_SHORT).show();
            }
        });
    }
}
