package com.inmu.activity;

import android.app.Application;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.GridView;
import android.widget.ImageButton;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.widget.Toast;
import android.widget.VideoView;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.viewpager.widget.ViewPager;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.List;
import java.util.Timer;
import java.util.TimerTask;
import java.util.concurrent.Future;

public class ViewPagerActivity extends AppCompatActivity{
    long time1,time2;
    Timer timer = new Timer();
    TimerTask timerTask;
    RelativeLayout rl;
    Handler handler;
    ViewPager viewPager;
    boolean isLoop=true;
    int[] photos = {R.mipmap.a1,R.mipmap.a2,R.mipmap.a3,R.mipmap.a4};
    String[] descriptions = {"傲慢与偏见","白鹿原","白夜行","百年孤独"};
    private List<Item2> generateData() {




        List<Item2> list = new ArrayList<Item2>();
        for (int i=0;i<4;i++){
            Item2 item2 = new Item2();
            item2.setResid(photos[i]);
            item2.setDescription((descriptions[i]));
            list.add(item2);


        }

        return list;
    }

    private List<Item2> generateData1() {
        int[] photos1 = {R.mipmap.a1,R.mipmap.a2,R.mipmap.a3,R.mipmap.a4,R.mipmap.a5,R.mipmap.a6,R.mipmap.a7,R.mipmap.a8};
        String[] descriptions1 = {"傲慢与偏见","白鹿原","白夜行","百年孤独","边城","灿烂千阳","茶花女","沉默的大多数"};

        List<Item2> list = new ArrayList<Item2>();
        for (int i=0;i<8;i++) {
            Item2 item1 = new Item2();
            item1.setResid(photos1[i]);
            item1.setDescription((descriptions1[i]));
            list.add(item1);
        }
        return list;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main3);

        //shang
        rl = findViewById(R.id.rl);
        //1.获取上一个activiyt传递过来intent对象
        Intent intent = getIntent();
        //2.通过intent对象获取里面的数据
        String name = intent.getStringExtra("name");
        String pwd = intent.getStringExtra("pwd");


        ImageButton a = findViewById(R.id.a);
        ImageButton b = findViewById(R.id.b);
        ImageButton c = findViewById(R.id.c);
        ImageButton d = findViewById(R.id.d);
        a.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ViewPagerActivity.this, "天猫", Toast.LENGTH_SHORT).show();
            }
        });

        b.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ViewPagerActivity.this, "淘宝", Toast.LENGTH_SHORT).show();
            }
        });
        c.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ViewPagerActivity.this, "会员中心", Toast.LENGTH_SHORT).show();
            }
        });
        d.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Toast.makeText(ViewPagerActivity.this, "分类", Toast.LENGTH_SHORT).show();
            }
        });


        //zhong
        //模拟数据
        List<Item2> list = generateData();

        viewPager=findViewById(R.id.view_pager);
        Mydapter3 mydapter3 = new Mydapter3(this, list);
        viewPager.setAdapter(mydapter3);
        viewPager.setCurrentItem(1000*4);

//        handler= new Handler();
//        handler.postDelayed(new TimerRunnable(),3000);



        //xia
        List<Item2> list1 = generateData1();

        GridView gv = findViewById(R.id.gv);
        MyAdapter2 adapter = new MyAdapter2(this, list1);
        gv.setAdapter(adapter);
        gv.setOnItemClickListener(new AdapterView.OnItemClickListener() {
            @Override
            public void onItemClick(AdapterView<?> adapterView, View view, int i, long l) {
                TextView tv_descrip = view.findViewById(R.id.tv_descrip);
                Toast.makeText(ViewPagerActivity.this, tv_descrip.getText(), Toast.LENGTH_SHORT).show();
            }
        });



//????????????????????????????????????????????????????????????????????????????????
        timerTask = new TimerTask() {
            @Override
            public void run() {
                runOnUiThread(new Runnable() {
                    @Override
                    public void run() {
                        int currentItem = viewPager.getCurrentItem();
                        viewPager.setCurrentItem(currentItem+1);
                    }
                });
            }
        };
        timer.schedule(timerTask,2000,2000);


        viewPager.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View v, MotionEvent event) {

                switch(event.getAction()){
                    case 0:
                        time1=event.getDownTime();
                        time2=event.getEventTime();
                        timer.cancel();
                        break;
                    case 2:
                        time1=0;
                        break;
                    case 1:
                        if ((time2-time1)/100<4) {
//                            Toast.makeText(ViewPagerActivity.this,(event.getEventTime()-event.getDownTime())/100+"", Toast.LENGTH_SHORT).show();
                            Toast.makeText(ViewPagerActivity.this, descriptions[viewPager.getCurrentItem()%4], Toast.LENGTH_SHORT).show();
                        }
                        timer = new Timer();
                        timerTask = new TimerTask() {
                            @Override
                            public void run() {
                                runOnUiThread(new Runnable() {
                                    @Override
                                    public void run() {
                                        //手指离开屏幕
                                        int currentItem = viewPager.getCurrentItem();
                                        viewPager.setCurrentItem(currentItem+1);
                                    }
                                });
                            }
                        };
                        timer.schedule(timerTask,2000,2000);
                        break;
                }
                return false;
            }
        });



    }


//    class TimerRunnable implements Runnable{
//
//        @Override
//        public void run() {
//            int curItem = viewPager.getCurrentItem();
//            viewPager.setCurrentItem(curItem+1);
//            if (isLoop==false){
//
//                handler.removeCallbacks(this);
//
//            }else if(handler!=null&&isLoop==true){
//
//                handler.postDelayed(this,3000);
//            }
//        }
//    }

    float x1=0;
    float x2=0;

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        View bg = findViewById(R.id.bg);
        //Log.e("ItemActivity",event.getAction()+"");
        switch(event.getAction()){
            case 0:
                //手指触摸到屏幕,获取用户触摸的坐标
                //Log.e("ItemActivity",event.getX()+"");
                x1 = event.getX();
                break;
            case  2:
                //手指在屏幕上滑
                x2 = event.getX();
                Log.e("ViewPagerActivity","x1:"+x1+"-x2:"+x2);

                if(x2-x1>300){
                    //Toast.makeText(ItemActivity.this,"向右滑",Toast.LENGTH_SHORT).show();
                    bg.setBackgroundColor(0xFF000000);



                }else if(x2-x1<-300){
                    //Toast.makeText(ItemActivity.this,"向左滑",Toast.LENGTH_SHORT).show();
                    bg.setBackgroundColor(0xFFFFFFFF);

                }
                break;
            case 1:
                //手指离开屏幕
                //Log.e("ItemActivity",event.getX()+"")
                break;
        }
        return super.onTouchEvent(event);
    }


    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {

        switch(keyCode){
            case KeyEvent.KEYCODE_BACK:

                AlertDialog dialog = new AlertDialog.Builder(this)
                        .setTitle("重要提示")
                        .setMessage("亲，你确定要退出吗？")
                        .setIcon(R.mipmap.ic_launcher)
                        .setPositiveButton("残忍离开", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                ViewPagerActivity.this.finish();
                            }
                        })
                        .setNegativeButton("再留一会", new DialogInterface.OnClickListener() {
                            @Override
                            public void onClick(DialogInterface dialogInterface, int i) {
                                dialogInterface.dismiss();
                            }
                        })
                        .create();
                dialog.show();


                break;
        }

        return true;
    }


}


