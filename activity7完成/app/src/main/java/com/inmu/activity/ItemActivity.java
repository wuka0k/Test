package com.inmu.activity;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.KeyEvent;
import android.view.MotionEvent;
import android.widget.RelativeLayout;
import android.widget.Toast;

/**
 * 1.创建activity，添加布局文件
 * 2.在总配置文件中进行activity的申明
 */
public class ItemActivity extends AppCompatActivity {
    RelativeLayout rl;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_item);
         rl = findViewById(R.id.rl);
        //1.获取上一个activiyt传递过来intent对象
        Intent intent = getIntent();
        //2.通过intent对象获取里面的数据
        String name = intent.getStringExtra("name");
        String pwd = intent.getStringExtra("pwd");
        //3.获取页面的控件对象
    }
    float x1=0;
    float x2=0;
    @Override
    public boolean onTouchEvent(MotionEvent event) {
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
                Log.e("ItemActivity","x1:"+x1+"-x2:"+x2);
                if(x2-x1>300){
                    //Toast.makeText(ItemActivity.this,"向右滑",Toast.LENGTH_SHORT).show();
                    rl.setBackgroundColor(0xFF0000FF);
                }else if(x2-x1<-300){
                    //Toast.makeText(ItemActivity.this,"向左滑",Toast.LENGTH_SHORT).show();
                    rl.setBackgroundColor(0x0000FFFF);
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
                                ItemActivity.this.finish();
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
