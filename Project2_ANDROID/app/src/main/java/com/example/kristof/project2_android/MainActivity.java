package com.example.kristof.project2_android;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.*;
import java.io.*;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    Button buttonSend;
    TextView textResponse, leftText, rightText;
    SeekBar leftSeekBar, rightSeekBar;
    Socket socket;
    Thread sendThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textResponse = (TextView)findViewById(R.id.response);
        leftSeekBar = (SeekBar)findViewById(R.id.seekBar1);
        rightSeekBar = (SeekBar) findViewById(R.id.seekBar2);
        leftText = (TextView) findViewById(R.id.leftText);
        rightText = (TextView) findViewById(R.id.rightText);

        leftSeekBar.setProgress(100);
        rightSeekBar.setProgress(100);

        leftSeekBar.setOnSeekBarChangeListener(
                new SeekBar.OnSeekBarChangeListener() {
                    @Override
                    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                        leftText.setText(""+(progress-100));
                        sendMessage();
                    }

                    @Override
                    public void onStartTrackingTouch(SeekBar seekBar) {

                    }

                    @Override
                    public void onStopTrackingTouch(SeekBar seekBar) {

                    }
                }
        );

        rightSeekBar.setOnSeekBarChangeListener(
                new SeekBar.OnSeekBarChangeListener() {
                    @Override
                    public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                        rightText.setText(""+(progress-100));
                        sendMessage();
                    }

                    @Override
                    public void onStartTrackingTouch(SeekBar seekBar) {

                    }

                    @Override
                    public void onStopTrackingTouch(SeekBar seekBar) {

                    }
                }
        );
    }

    public void sendMessage() {
        if(sendThread != null)
            sendThread.interrupt();

        final String message = "{ \"client\": \"0\", \"left\": \"" + (leftSeekBar.getProgress()-100) + "\", \"right\": \"" + (rightSeekBar.getProgress()-100) + "\" }";
        sendThread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    socket = new Socket("192.168.0.100", 4000);
                } catch (IOException e) {
                    e.printStackTrace();
                }

                try {
                    PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket.getOutputStream())), true);
                    out.println(message);
                    out.flush();
                    socket.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });
        sendThread.start();

        textResponse.setText(message);
    }
}