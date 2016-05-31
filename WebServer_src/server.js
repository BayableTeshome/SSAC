
var srcHost = "192.168.0.50";
var srcPort = 8004;
var video_srcPort=8005;
var srcBoundary = "--videoboundary";

var destHost = "10.42.0.1";
var destPort = 8002;

var Http = require('http');
var Net = require('net');
var Dicer = require('dicer');
var SocketIO = require('socket.io');
var fs = require('fs');
var async = require('async');
var htmlFile;
var cssFile;
var startTcp;

var socket = Net.Socket();
var video_socket = Net.Socket();


socket.connect(srcPort, srcHost, function() {
   console.log('camera server connected on port :',srcPort)

 fs.readFile('./index.html', function(err, data) {
    if (err){
        throw err;
    }
    htmlFile = data;
    });

    fs.readFile('./styles.css', function(err, data) {
      if (err){
        throw err;
      }
      cssFile = data;
      });
    
var server = Http.createServer(function (request, response) {
     
   switch (request.url) {
        case "/styles.css" :
            response.writeHead(200, {"Content-Type": "text/css"});
            response.write(cssFile);
            break;
        default :    
            response.writeHead(200, {"Content-Type": "text/html"});
            response.write(htmlFile);
    };
    response.end();
}).listen(destPort, destHost);

var io = require('socket.io').listen(server);

io.sockets.on('connection', function(client_socket){

    client_socket.on('client_data', function(data){
    process.stdout.write(data.letter);
    console.log('mobile client: ' + data);    

    });

      client_socket.on('message', function (message) {
      socket.write(message);

    // console.log('mobile client: ' + message);

    }); 

});

setInterval(function(){
    socket.write("a");

},3000);

video_socket.connect(video_srcPort, srcHost,function() {
        console.log('video client connected on port: ',video_srcPort)

        // Init Dicer :
        global.dicer = new Dicer({ boundary: srcBoundary });

        dicer.on('part', function(part) {

            var frameEncoded = '';
            part.setEncoding('base64');

            part.on('header', function(header) { });
            part.on('data', function(data) { frameEncoded += data; });
            part.on('end', function() { io.sockets.emit('image', frameEncoded); });
            
            
        });

        // Handle streams closing :
        dicer.on('finish', function() { console.log('Dicer stream finished'); });
        video_socket.on('close', function() { console.log('TCP socket closed'); });

        // Pipe :
        video_socket.pipe(dicer);
     });
     
    
});
// Home PC message

socket.on('data', function(data) {
  console.log('message from Home: ' + data);
  
  //socket.destroy(); // kill client after server's response
});
socket.on('close', function() {
  console.log('Connection closed');
});

socket.on('error', function(ex) {
  console.log("handled error");
  console.log(ex);
});
