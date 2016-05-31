package com.pestostech.team09;


import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.MediaController;
import android.widget.VideoView;

import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import java.net.URISyntaxException;


/**
 * A simple {@link Fragment} subclass.
 */
public class RtspViewFragment extends Fragment {


    public RtspViewFragment() {
        // Required empty public constructor
    }

    private Socket socket;
    VideoView vidView;
    Button leftButton;
    Button rigntButton;
    Button upButton;
    Button downButton;
    Button zoomInButton;
    Button zoomOutButton;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View rtspView = inflater.inflate(R.layout.fragment_rtsp_view, container, false);

        vidView = (VideoView)rtspView.findViewById(R.id.myVideo);
        leftButton = (Button)rtspView.findViewById(R.id.bnLeft);
        rigntButton = (Button)rtspView.findViewById(R.id.bnRight);
        upButton = (Button)rtspView.findViewById(R.id.bnUp);
        downButton = (Button)rtspView.findViewById(R.id.bnDown);
        zoomInButton = (Button)rtspView.findViewById(R.id.bnZoomIn);
        zoomOutButton = (Button)rtspView.findViewById(R.id.bnZoomOut);


//        {
//            try{
//                socket = IO.socket("http://10.42.0.1:8002");
//            }catch (URISyntaxException e){
//                throw new RuntimeException(e);
//            }
//        }
////            Log.d("onConnect","socket connected");
//        socket.connect();
//        socket.emit("message", "RTSP");
//        socket.disconnect();


        String vidAddress = "rtsp://10.42.0.1:8554/test";   //RTSP URL
        Uri vidUri = Uri.parse(vidAddress);

        vidView.setVideoURI(vidUri);

//        MediaController vidControl = new MediaController(getActivity());

//        vidControl.setAnchorView(vidView);
//        vidView.setMediaController(vidControl);

        vidView.start();

        leftButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO click responses
//                sendMessage = new SendMessage("Left");
                socket.emit("message", "Left");
            }
        });
        rigntButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO click responses
//                sendMessage = new SendMessage("Right");
                socket.emit("message", "Right");
            }
        });
        upButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO click responses
//                sendMessage = new SendMessage("Up");
                socket.emit("message", "Up");
            }
        });
        downButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO click responses
//                sendMessage = new SendMessage("Down");
                socket.emit("message", "Down");
            }
        });
        zoomInButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO click responses
//                sendMessage = new SendMessage("plus");
                socket.emit("message", "plus");
            }
        });
        zoomOutButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO click responses
//                sendMessage = new SendMessage("minus");
                socket.emit("message", "minus");
            }
        });

        return rtspView;

    }

}
