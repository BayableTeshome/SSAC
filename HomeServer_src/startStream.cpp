#include <gst/gst.h>
#include <gst/rtsp-server/rtsp-server.h>
#include "startStream.h"
#include <QDebug>
#include "globalVariables.h"
startStream::startStream(QObject *parent) : QObject(parent)
{

}

GstPadProbeReturn startStream::cb_have_data (GstPad *pad,GstPadProbeInfo *info,gpointer user_data)
{
    gint x, y;
    GstMapInfo map;
    guint16 *ptr, t;
    GstBuffer *buffer;

    buffer = GST_PAD_PROBE_INFO_BUFFER (info);

    buffer = gst_buffer_make_writable (buffer);

    /* Making a buffer writable can fail (for example if it
   * cannot be copied and is used more than once)
   */
    if (buffer == NULL)
        return GST_PAD_PROBE_OK;

    /* Mapping a buffer can fail (non-writable) */
    if (gst_buffer_map (buffer, &map, GST_MAP_WRITE)) {
        ptr = (guint16 *) map.data;
        /* invert data */
        for (y = 0; y < 288; y++) {
            for (x = 0; x < 384 / 2; x++) {
                t = ptr[384 - 1 - x];
                ptr[384 - 1 - x] = ptr[x];
                ptr[x] = t;
            }
            ptr += 384;
        }
        gst_buffer_unmap (buffer, &map);
    }

    GST_PAD_PROBE_INFO_DATA (info) = buffer;

    return GST_PAD_PROBE_OK;
}

void startStream::stream()
{

    if(RtspStream==true )
    {

        rtspstream();
    }
    if(httpStream==true)
    {
        httpstream();
    }

    if(tcpStream==true)
    {
         tcpstream();
    }
    if(tcpStream==false && httpStream==false && RtspStream==false )
    {
       g_main_loop_quit(loop);
    }


}

void startStream:: tcpstream()
{

    /* init GStreamer */
    //gst_init ();
    gst_init(NULL,NULL);
    loop = g_main_loop_new (NULL, FALSE);
    /* build */
    pipeline = gst_pipeline_new ("my-pipeline");
    src = gst_element_factory_make ("souphttpsrc", "src");
    if (src == NULL)
        g_error ("Could not create 'souphttpsrc' element");

    jpdec = gst_element_factory_make ("jpegdec", "jpdec");

    vidscale = gst_element_factory_make ("videoscale", "vidscale");


    filter = gst_element_factory_make ("capsfilter", "filter");
    g_assert (filter != NULL); /* should always exist */

    csp = gst_element_factory_make ("videoconvert", "csp");
    if (csp == NULL)
        g_error ("Could not create 'videoconvert' element");
    videoenc = gst_element_factory_make ("jpegenc", "videoenc");
    muxer = gst_element_factory_make ("multipartmux", "muxer");
    g_object_set (G_OBJECT (muxer), "boundary", "--videoboundary", NULL);

    sink = gst_element_factory_make ("tcpserversink", "sink");
    if (sink == NULL) {
        g_error ("Could not create neither 'xvimagesink' nor 'ximagesink' element");
    }

    g_object_set (G_OBJECT (src), "location","http://root:mmnet@192.168.0.90/mjpg/video.mjpg", NULL);
    g_object_set (G_OBJECT (src), "do-timestamp",true, NULL);
    g_object_set (G_OBJECT (src), "is_live",true, NULL);
    g_object_set (G_OBJECT (src), "timeout",5, NULL);
    g_object_set (G_OBJECT (sink), "host" , "192.168.0.50" , NULL);
    g_object_set (G_OBJECT (sink), "port" ,8005 , NULL);


    gst_bin_add_many (GST_BIN (pipeline), src,jpdec,vidscale,csp,videoenc,muxer,sink, NULL);
    gst_element_link_many ( src,jpdec,vidscale,csp,videoenc,muxer,sink, NULL);

    filtercaps = gst_caps_new_simple ("video/x-raw",
                                      "format", G_TYPE_STRING, "RGB16",
                                      "width", G_TYPE_INT, 384,
                                      "height", G_TYPE_INT, 288,
                                      "framerate", GST_TYPE_FRACTION, 5, 1,
                                      NULL);

    g_object_set (G_OBJECT (filter), "caps", filtercaps, NULL);
    gst_caps_unref (filtercaps);

    /* run */
    gst_element_set_state (pipeline, GST_STATE_PLAYING);


    /* wait until it's up and running or failed */
    if (gst_element_get_state (pipeline, NULL, NULL, -1) == GST_STATE_CHANGE_FAILURE) {
        g_error ("Failed to go into PLAYING state");
    }


        g_print ("Running TCP ...\n");
        g_main_loop_run (loop);
       // g_main_loop_quit(loop);


    /* exit */
    gst_element_set_state (pipeline, GST_STATE_NULL);
    gst_object_unref (pipeline);
}
void startStream:: httpstream()
{

    /* init GStreamer */
    gst_init(NULL,NULL);
    loop = g_main_loop_new (NULL, FALSE);

    /* build */
    pipeline = gst_pipeline_new ("my-pipeline");
    src = gst_element_factory_make ("souphttpsrc", "src");
    if (src == NULL)
      g_error ("Could not create 'souphttpsrc' element");

    jpdec = gst_element_factory_make ("jpegdec", "jpdec");

    vidscale = gst_element_factory_make ("videoscale", "vidscale");


    filter = gst_element_factory_make ("capsfilter", "filter");
    g_assert (filter != NULL); /* should always exist */

    csp = gst_element_factory_make ("videoconvert", "csp");
      if (csp == NULL)
      g_error ("Could not create 'videoconvert' element");

       videoenc = gst_element_factory_make ("x264enc", "videoenc");

       demuxer = gst_element_factory_make ("multipartdemux", "demuxer");
       mux = gst_element_factory_make ("mpegtsmux", "mux");

       sink = gst_element_factory_make ("hlssink", "sink");


    g_object_set (G_OBJECT (src), "location","http://root:mmnet@192.168.0.90/mjpg/video.mjpg", NULL);
    g_object_set (G_OBJECT (src), "do-timestamp",true, NULL);
    g_object_set (G_OBJECT (sink), "location","/home/yonas/WEB/streamcontent/hlssink", NULL);
    g_object_set (G_OBJECT (sink), "playlist-location","/home/yonas/WEB/streamcontent/", NULL);
    g_object_set (G_OBJECT (sink), "target-duration",0, NULL);
    g_object_set (G_OBJECT (sink), "max-files",5, NULL);
    g_object_set (G_OBJECT (sink), "playlist-root","http://127.0.0.1", NULL);



    gst_bin_add_many (GST_BIN (pipeline), src,jpdec,videoenc,mux,sink, NULL);
    gst_element_link_many (src,jpdec,videoenc,mux,sink, NULL);

    filtercaps = gst_caps_new_simple ("video/x-raw",
                  "format", G_TYPE_STRING, "RGB16",
                  "width", G_TYPE_INT, 384,
                  "height", G_TYPE_INT, 288,
                  "framerate", GST_TYPE_FRACTION, 25, 1,
                  NULL);

    g_object_set (G_OBJECT (filter), "caps", filtercaps, NULL);
    gst_caps_unref (filtercaps);
     /* run */
      gst_element_set_state (pipeline, GST_STATE_PLAYING);


      /* wait until it's up and running or failed */
     if (gst_element_get_state (pipeline, NULL, NULL, -1) == GST_STATE_CHANGE_FAILURE) {
       g_error ("Failed to go into PLAYING state");
      }


          g_print ("Running HLS ...\n");
          g_main_loop_run (loop);


      /* exit */
      gst_element_set_state (pipeline, GST_STATE_NULL);
      gst_object_unref (pipeline);


}

void startStream:: rtspstream()
{

          GstRTSPServer *server;
          GstRTSPMountPoints *mounts;
          GstRTSPMediaFactory *factory;


          gst_init(NULL,NULL);

          loop = g_main_loop_new (NULL, FALSE);

          server = gst_rtsp_server_new ();


          mounts = gst_rtsp_server_get_mount_points (server);


          factory = gst_rtsp_media_factory_new ();
          gst_rtsp_media_factory_set_launch (factory,
                                           "( souphttpsrc location=http://root:mmnet@192.168.0.90/mjpg/video.mjpg do-timestamp=true ! multipartdemux ! image/jpeg, width=352, height=288, framerate=25/1 ! jpegdec ! x264enc ! rtph264pay name=pay0 pt=96 )");
          gst_rtsp_media_factory_set_shared (factory, TRUE);

          gst_rtsp_mount_points_add_factory (mounts, "/test", factory);

          g_object_unref (mounts);

          gst_rtsp_server_attach (server, NULL);

          g_print ("stream ready at rtsp://10.42.0.1:8554/test\n");
          g_main_loop_run (loop);

}

