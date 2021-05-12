package com.inmu.activity;

import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.AdapterView;
import android.widget.GridView;
import android.widget.ListView;
import android.widget.TextView;
import android.widget.Toast;

import androidx.appcompat.app.AppCompatActivity;

import java.util.ArrayList;
import java.util.List;

public class GridViewActivity extends AppCompatActivity {



    private List<Item2> generateData() {
        int[] photos = {R.mipmap.a1,R.mipmap.a2,R.mipmap.a3,R.mipmap.a4,R.mipmap.a5,R.mipmap.a6,R.mipmap.a7,R.mipmap.a8};
        String[] descriptions = {"abc","edg","rng","lgd","we","jd","sn","tx"};

        List<Item2> list = new ArrayList<Item2>();
        for (int i=0;i<8;i++){
            Item2 item2 = new Item2();
            item2.setResid(photos[i]);
            item2.setDescription((descriptions[i]));
            list.add(item2);
        }

        return list;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main2);

        //模拟数据
        List<Item2> list = generateData();


        GridView gv = findViewById(R.id.gv);
        MyAdapter2 adapter = new MyAdapter2(this, list);
        gv.setAdapter(adapter);
        gv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                TextView tv_descrip = view.findViewById(R.id.tv_descrip);
                Toast.makeText(GridViewActivity.this, tv_descrip.getText(), Toast.LENGTH_SHORT).show();
            }
        });

    }

}


