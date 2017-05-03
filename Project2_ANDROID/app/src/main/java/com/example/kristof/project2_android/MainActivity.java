package com.example.kristof.project2_android;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.*;
import java.io.*;
import java.net.Socket;
import java.util.Timer;
import java.util.concurrent.ThreadFactory;

public class MainActivity extends AppCompatActivity {
    Button buttonSend;
    TextView textResponse, leftText, rightText;
    VerticalSeekBar leftSeekBar, rightSeekBar;
    Socket socket;
    Thread sendThread;
    Thread sending;
    Timer t = new Timer();
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textResponse = (TextView)findViewById(R.id.response);
        leftSeekBar = (VerticalSeekBar)findViewById(R.id.seekBar1);
        rightSeekBar = (VerticalSeekBar) findViewById(R.id.seekBar2);
        leftText = (TextView) findViewById(R.id.leftText);
        rightText = (TextView) findViewById(R.id.rightText);

        leftSeekBar.setProgress(100);
        rightSeekBar.setProgress(100);
        leftSeekBar.setOnSeekBarChangeListener(
                new SeekBar.OnSeekBarChangeListener() {
                    @Override
                    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                        leftText.setText(""+(progress-100));
                        //sendMessage();
                    }

                    @Override
                    public void onStartTrackingTouch(SeekBar seekBar) {

                    }

                    @Override
                    public void onStopTrackingTouch(SeekBar seekBar) {
                        leftText.setText("stop");
                    }
                }
        );

        rightSeekBar.setOnSeekBarChangeListener(
                new SeekBar.OnSeekBarChangeListener() {
                    @Override
                    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                        rightText.setText(""+(progress-100));
                    }

                    @Override
                    public void onStartTrackingTouch(SeekBar seekBar) {

                    }

                    @Override
                    public void onStopTrackingTouch(SeekBar seekBar) {
                    }
                }
        );
        sending = new Thread(new Runnable() {
            int l_value = 0;
            int r_value = 0;
            @Override
            public void run() {
                while (true) {
                    if (l_value != leftSeekBar.getProgress() || r_value != rightSeekBar.getProgress()) {
                        final String message = "{ \"client\": 0, \"left\": " + (leftSeekBar.getProgress() - 100) + ", \"right\": " + (rightSeekBar.getProgress() - 100) + " }";
                        try {
                            socket = new Socket("192.168.0.100", 4000);
                            PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
                            out.println(message);
                            out.flush();
                            socket.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                    }
                    l_value = leftSeekBar.getProgress();
                    r_value = rightSeekBar.getProgress();
                    try {
                        Thread.sleep(200);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        sending.start();
    }
}