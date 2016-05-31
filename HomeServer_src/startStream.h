#ifndef STARTSTREAM_H
#define STARTSTREAM_H

#include <QObject>
#include <gst/gst.h>
#include <string>
#include "TargetObject.h"

class startStream : public QObject
{
    Q_OBJECT
public:
     explicit startStream(QObject *parent = 0);
     void stream();
     static GstPadProbeReturn cb_have_data (GstPad *pad,GstPadProbeInfo *info,gpointer user_data);
     QString type(QString message);
     QString status="NO";
     void tcpstream();
     void rtspstream();
     void httpstream();
signals:


public slots:
private:
     GMainLoop *loop;
     GstElement *pipeline2,*pipeline, *src,*rtpsink, *sink,*jpdec,*vidscale,*vidsca,*filter, *csp, *rtphpay,*videnc, *videoenc, *demuxer, *mux,*muxer;
     GstCaps *filtercaps;
     GstPad *pad;


};

#endif // STARTSTREAM_H

