package com.example.kristof.project2_android;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;
import java.net.Socket;

public class MainActivity extends AppCompatActivity {
    Button buttonConnect,buttonSend;
    TextView textResponse;
    Socket socket;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        buttonConnect = (Button)findViewById(R.id.connect);
        buttonSend = (Button)findViewById(R.id.buttonSend);

        textResponse = (TextView)findViewById(R.id.response);
        buttonConnect.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            socket = new Socket("192.168.0.100", 4000);
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                    }).start();

                textResponse.setText("CONNECTED");
            }
        });

        buttonSend.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View v) {
                new Thread(new Runnable() {
                    @Override
                    public void run() {
                        //if (socket == null|| socket.isClosed() || !socket.isConnected()){
                            try {
                                socket = new Socket("192.168.0.100", 4000);
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                       // }
                        try {
                            PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(socket
                                    .getOutputStream())), true);
                            out.println("TEST");
                            out.flush();
                        } catch (IOException e) {
                            e.printStackTrace();
                        }
                    }
                }).start();

                textResponse.setText("TEST");
            }
        });





        }
        }


