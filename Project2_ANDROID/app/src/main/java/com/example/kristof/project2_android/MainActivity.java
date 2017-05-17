package com.example.kristof.project2_android;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.SeekBar;
import android.widget.Switch;
import android.widget.TextView;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Timer;

public class MainActivity extends AppCompatActivity {
    Button stopButton;
    TextView textResponse, leftText, rightText;
    Switch enable;
    VerticalSeekBar leftSeekBar, rightSeekBar;

    Socket socket;
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
        stopButton = (Button) findViewById(R.id.stopButton);
        enable = (Switch) findViewById(R.id.enable);

        leftSeekBar.setProgress(100);
        rightSeekBar.setProgress(100);
        stopButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                leftSeekBar.setProgress(100);
                rightSeekBar.setProgress(100);
            }
        });
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
                   // if(enable.isChecked()) {
                    if (enable.isChecked() || (l_value != leftSeekBar.getProgress() || r_value != rightSeekBar.getProgress())) {
                        final String message = "{ \"client\": 0, \"right\": " + (leftSeekBar.getProgress() - 100) + ", \"left\": " + (rightSeekBar.getProgress() - 100) + " }";
                        try {
                            socket = new Socket("192.168.0.100", 4000);
                            PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
                            out.println(message);
                            out.flush();
                            socket.close();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }

                        l_value = leftSeekBar.getProgress();
                        r_value = rightSeekBar.getProgress();
                    }

                    try {
                        Thread.sleep(100);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                }
            }
        });

        sending.start();
    }
}