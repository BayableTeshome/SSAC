package com.pestostech.team09;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentTransaction;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.CompoundButton;
import android.widget.NumberPicker;
import android.widget.Switch;
import android.widget.Toast;

import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import java.net.URISyntaxException;


/**
 * A simple {@link Fragment} subclass.
 */
public class SetOptionFragment extends Fragment{


    public SetOptionFragment() {
        // Required empty public constructor
    }
    NumberPicker numberPicker;
    Button play;
    Switch trackSwitch;
    Switch recordSwitch;
    Switch alarmSwitch;

    private Socket socket;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        final View setOptionView = inflater.inflate(R.layout.fragment_set_option, container, false);

        numberPicker = (NumberPicker) setOptionView.findViewById(R.id.numberPicker);
        play = (Button) setOptionView.findViewById(R.id.Play);
        trackSwitch = (Switch) setOptionView.findViewById(R.id.trackSwitch);
        recordSwitch = (Switch) setOptionView.findViewById(R.id.recordSwitch);
        alarmSwitch = (Switch) setOptionView.findViewById(R.id.recordSwitch);

        String[] numberPickerStrings = {
                "TCP",
                "RTSP",
                "HTTP",
                "Show Notification",
                "Play Recorded",
                "OFF"
        };
        numberPicker.setDisplayedValues(numberPickerStrings);
        numberPicker.setMinValue(0);
        numberPicker.setMaxValue(numberPickerStrings.length - 1);

        {
            try{
                socket = IO.socket("http://10.42.0.1:8002");
            }catch (URISyntaxException e){
                throw new RuntimeException(e);
            }
        }
//            Log.d("onConnect","socket connected");
        socket.connect();


        trackSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {


                if (b)
                {
                    socket.emit("message", "track");
                    Toast.makeText(getActivity().getApplicationContext(), "Auto Track Enabled",Toast.LENGTH_SHORT).show();
                }
                else
                {
                    socket.emit("message", "stopTrack");
                    Toast.makeText(getActivity().getApplicationContext(), "Auto Track Disabled",Toast.LENGTH_SHORT).show();
                }
//                socket.disconnect();
            }
        });

        recordSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {


                if (b)
                {
                    socket.emit("message", "record");
                    Toast.makeText(getActivity().getApplicationContext(), "Auto Track Enabled",Toast.LENGTH_SHORT).show();
                }
                else
                {
                    socket.emit("message", "stopRecord");
                    Toast.makeText(getActivity().getApplicationContext(), "Auto Track Disabled",Toast.LENGTH_SHORT).show();
                }
//                socket.disconnect();
            }
        });

        alarmSwitch.setOnCheckedChangeListener(new CompoundButton.OnCheckedChangeListener() {
            @Override
            public void onCheckedChanged(CompoundButton compoundButton, boolean b) {


                if (b)
                {
                    socket.emit("message", "alarm");
                    Toast.makeText(getActivity().getApplicationContext(), "Auto Track Enabled",Toast.LENGTH_SHORT).show();
                }
                else
                {
                    socket.emit("message", "stopAlarm");
                    Toast.makeText(getActivity().getApplicationContext(), "Auto Track Disabled",Toast.LENGTH_SHORT).show();
                }
//                socket.disconnect();
            }
        });
        // play button pressed
        play.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO click responses
                FragmentManager fragmentManager = getFragmentManager();
                FragmentTransaction fragmentTransaction = fragmentManager.beginTransaction();
                fragmentTransaction.setCustomAnimations(android.R.anim.fade_in,android.R.anim.fade_out);

                int choice = numberPicker.getValue();
                if (choice == 0)
                {
                    TcpViewFragment tcpViewFragment = new TcpViewFragment();
                    fragmentTransaction.add(R.id.fragmentContainer, tcpViewFragment);
                    fragmentTransaction.addToBackStack(null);
                    fragmentTransaction.commit();
                    play.setVisibility(View.INVISIBLE);
                    numberPicker.setVisibility(View.INVISIBLE);
                    trackSwitch.setVisibility(View.INVISIBLE);
                    recordSwitch.setVisibility(View.INVISIBLE);
                    alarmSwitch.setVisibility(View.INVISIBLE);
                }
                else if (choice == 1)
                {
                    RtspViewFragment rtspViewFragment = new RtspViewFragment();
                    fragmentTransaction.add(R.id.fragmentContainer, rtspViewFragment);
                    fragmentTransaction.addToBackStack(null);
                    fragmentTransaction.commit();
                    play.setVisibility(View.INVISIBLE);
                    numberPicker.setVisibility(View.INVISIBLE);
                    trackSwitch.setVisibility(View.INVISIBLE);
                    recordSwitch.setVisibility(View.INVISIBLE);
                    alarmSwitch.setVisibility(View.INVISIBLE);
                }
                else if (choice == 2)
                {
                    HlsViewFragment hlsViewFragment = new HlsViewFragment();
                    fragmentTransaction.add(R.id.fragmentContainer, hlsViewFragment);
                    fragmentTransaction.addToBackStack(null);
                    fragmentTransaction.commit();
                    play.setVisibility(View.INVISIBLE);
                    numberPicker.setVisibility(View.INVISIBLE);
                    trackSwitch.setVisibility(View.INVISIBLE);
                    recordSwitch.setVisibility(View.INVISIBLE);
                    alarmSwitch.setVisibility(View.INVISIBLE);
                }

                else if (choice == 3)
                {
                    TcpViewFragment tcpViewFragment = new TcpViewFragment();
                    fragmentTransaction.add(R.id.fragmentContainer, tcpViewFragment);
                    fragmentTransaction.addToBackStack(null);
                    fragmentTransaction.commit();
                    play.setVisibility(View.INVISIBLE);
                    numberPicker.setVisibility(View.INVISIBLE);
                    trackSwitch.setVisibility(View.INVISIBLE);
                    recordSwitch.setVisibility(View.INVISIBLE);
                    alarmSwitch.setVisibility(View.INVISIBLE);
                }
                else if (choice == 4)
                {
                    TcpViewFragment tcpViewFragment = new TcpViewFragment();
                    fragmentTransaction.add(R.id.fragmentContainer, tcpViewFragment);
                    fragmentTransaction.addToBackStack(null);
                    fragmentTransaction.commit();
                    play.setVisibility(View.INVISIBLE);
                    numberPicker.setVisibility(View.INVISIBLE);
                    trackSwitch.setVisibility(View.INVISIBLE);
                    recordSwitch.setVisibility(View.INVISIBLE);
                    alarmSwitch.setVisibility(View.INVISIBLE);
                }
                else if (choice == 5)
                {

                }
            }
        });
        return setOptionView;
    }

}
