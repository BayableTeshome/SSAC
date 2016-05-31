package com.pestostech.team09;


import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ImageView;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.util.Base64;
import android.widget.Switch;
import android.widget.Toast;

import com.github.nkzawa.emitter.Emitter;
import com.github.nkzawa.socketio.client.IO;
import com.github.nkzawa.socketio.client.Socket;

import java.net.URISyntaxException;


/**
 * A simple {@link Fragment} subclass.
 */
public class TcpViewFragment extends Fragment {


    public TcpViewFragment() {
        // Required empty public constructor
    }

    ImageView imageView;
    private Socket socket;

    Button leftButton;
    Button rightButton;
    Button upButton;
    Button downButton;
    Button zoomInButton;
    Button zoomOutButton;


    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View tcpView = inflater.inflate(R.layout.fragment_tcp_view, container, false);


        imageView = (ImageView)tcpView.findViewById(R.id.myImage);
        leftButton = (Button)tcpView.findViewById(R.id.buttonLeft);
        rightButton = (Button)tcpView.findViewById(R.id.buttonRight);
        upButton = (Button)tcpView.findViewById(R.id.buttonUp);
        downButton = (Button)tcpView.findViewById(R.id.buttonDown);
        zoomInButton = (Button)tcpView.findViewById(R.id.buttonZoomIn);
        zoomOutButton = (Button)tcpView.findViewById(R.id.buttonZoomOut);


        {
            try{
                socket = IO.socket("http://10.42.0.1:8002");
            }catch (URISyntaxException e){
                throw new RuntimeException(e);
            }
        }
//            Log.d("onConnect","socket connected");
        socket.connect();
        socket.on("image", handleIncomingMessages);
//        socket.emit("message", "TCP");

        leftButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                //TODO click responses
//                sendMessage = new SendMessage("Left");
                socket.emit("message", "Left");
            }
        });
        rightButton.setOnClickListener(new View.OnClickListener() {
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

        return tcpView;
    }

    private Bitmap decodeImage(String data)
    {
        byte[] b = Base64.decode(data, Base64.DEFAULT);
        Bitmap bmp = BitmapFactory.decodeByteArray(b,0,b.length);
        return bmp;
    }

    public void addImage(Bitmap bm){
        imageView.setImageBitmap(bm);
    }

    private Emitter.Listener handleIncomingMessages = new Emitter.Listener(){
        @Override
        public void call(final Object... args) {
            getActivity().runOnUiThread(new Runnable(){
                @Override
                public void run() {
                    String data = (String) args[0];
                    addImage(decodeImage(data));
                }
            });
        }
    };

    @Override
    public void onDestroyView() {
        super.onDestroyView();
        socket.disconnect();
    }
}
