package com.inmu.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.text.Editable;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

/**
 * onrestart  onstart onresume 捆绑执行  常用onrestart
 * oncreate  创建的时候执行
 * onpause  onstop  捆绑执行  c常用onstop
 * ondestroy  销毁执行  资源的回收
 */
public class MainActivity extends AppCompatActivity {


    @Override
    protected void onStart() {
        super.onStart();
        //System.out.println("调用了onstart方法");
        Log.e("MainActivity","调用onstart的方法");
    }

    @Override
    protected void onResume() {
        super.onResume();
        System.out.println("调用了onresume的方法");
    }

    @Override
    protected void onPause() {
        super.onPause();
        System.out.println("调用了onpause状态");
    }

    @Override
    protected void onStop() {
        super.onStop();
        System.out.println("调用了停止状态stop");
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        System.out.println("调用了销毁的方法destroy");
    }

    @Override
    protected void onRestart() {
        super.onRestart();
        System.out.println("调用了onrestart方法");
    }

    //创建页面时候调用
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        System.out.println("执行了oncreate方法");
        setContentView(R.layout.activity_main);

        //1.找到这个按钮对象
        Button bt = findViewById(R.id.button);
        //获取俩个编辑框对象
        final EditText etName = findViewById(R.id.et_name);
        final  EditText etPwd = findViewById(R.id.et_pwd);
        //2.给按钮注册点击事件
       bt.setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View view) {

              //2.获取编辑框的内容
               String name = etName.getText().toString();
               String pwd = etPwd.getText().toString();

               //3.判断用户名和密码
               if ("hao".equals(name)&&"123".equals(pwd)){
                   //4.跳转页面
                   //4.1 创建activity  在配置文件Androidmanifest.xml进行注册
                   //4.2 跳转  Intent意图对象
                   //5.俩个activity传值  使用意图对象Intent
                   Intent intent = new Intent();
                   //存放数据到intent里面
                   intent.putExtra("name",name);
                   intent.putExtra("pwd",pwd);
                   intent.setClass(MainActivity.this,ViewPagerActivity.class);
                   startActivity(intent);
               }else{
                   Toast.makeText(MainActivity.this,"用户名或密码不正确",Toast.LENGTH_LONG).show();
               }

           }
       });

    }
}
