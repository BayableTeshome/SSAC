package com.pestostech.team09;

import android.content.Intent;
import android.graphics.Color;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.view.ViewParent;
import android.widget.Button;

import java.net.URISyntaxException;

import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;


public class MainActivity extends AppCompatActivity {

    Button logIn;

    @Override
    public void onBackPressed() {


        if (findViewById(R.id.Play).getVisibility() == View.INVISIBLE)
        {
            findViewById(R.id.Play).setVisibility(View.VISIBLE); // if not visible
        }
        if (findViewById(R.id.numberPicker).getVisibility() == View.INVISIBLE)
        {
            findViewById(R.id.numberPicker).setVisibility(View.VISIBLE); // if not visible
        }
        if (findViewById(R.id.trackSwitch).getVisibility() == View.INVISIBLE)
        {
            findViewById(R.id.trackSwitch).setVisibility(View.VISIBLE);
        }
        if (findViewById(R.id.recordSwitch).getVisibility() == View.INVISIBLE)
        {
            findViewById(R.id.recordSwitch).setVisibility(View.VISIBLE);
        }
        if (findViewById(R.id.alarmSwitch).getVisibility() == View.INVISIBLE)
        {
            findViewById(R.id.alarmSwitch).setVisibility(View.VISIBLE);
        }


        super.onBackPressed();
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        logIn = (Button) findViewById(R.id.button);

        logIn.setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view) {

                Intent intent = new Intent(MainActivity.this, StreamService.class);
                startService(intent);

                FragmentManager fragmentManager = getSupportFragmentManager();
//                android.support.v4.app.FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();

                SetOptionFragment setOptionFragment = new SetOptionFragment();
//                TcpViewFragment tcpViewFragment = new TcpViewFragment();
                fragmentTransaction.add(R.id.fragmentContainer, setOptionFragment);
//                fragmentTransaction.addToBackStack(null);
                fragmentTransaction.commit();
//                logIn.setEnabled(false);
                logIn.setVisibility(View.INVISIBLE);
            }
        });
    }
}


