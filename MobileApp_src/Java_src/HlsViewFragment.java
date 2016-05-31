package com.pestostech.team09;


import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.VideoView;

import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import java.net.URISyntaxException;


/**
 * A simple {@link Fragment} subclass.
 */
public class HlsViewFragment extends Fragment {


    public HlsViewFragment() {
        // Required empty public constructor
    }

    VideoView vidView;
    private Socket socket;

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View hlsView = inflater.inflate(R.layout.fragment_hls_view, container, false);

        vidView = (VideoView)hlsView.findViewById(R.id.hlsVideo);

//        {
//            try{
//                socket = IO.socket("http://10.42.0.1:8002");
//            }catch (URISyntaxException e){
//                throw new RuntimeException(e);
//            }
//        }
////            Log.d("onConnect","socket connected");
//        socket.connect();
//        socket.emit("message", "HLS");
//        socket.disconnect();


        String vidAddress = "http://10.42.0.1:8002/hlssink";  // HLS URL
        Uri vidUri = Uri.parse(vidAddress);

        vidView.setVideoURI(vidUri);

//        MediaController vidControl = new MediaController(getActivity());

//        vidControl.setAnchorView(vidView);
//        vidView.setMediaController(vidControl);

        vidView.start();


        return hlsView;
    }

}
