package com.inmu.activity;

import androidx.appcompat.app.AppCompatActivity;

import android.net.Uri;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.VideoView;

public class VideoActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_video);

        //1.找到vv
        final VideoView vv = findViewById(R.id.vv);
        Button btStart = findViewById(R.id.bt_start);
        vv.setVideoURI(Uri.parse("android.resource://"+getPackageName()+"/" + R.raw.a));
        btStart.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                vv.start();
            }
        });


    }
}
