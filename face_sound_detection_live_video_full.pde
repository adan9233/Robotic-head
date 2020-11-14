import gab.opencv.*;
import processing.video.*;
import java.awt.*;
import ddf.minim.*;
Minim soundengine;
AudioSample sonido1;
AudioSample sonido2;
Capture video;
OpenCV opencv;

PFont orcFont;

void setup() {
  size(640, 480);
  video = new Capture(this, 640/2, 480/2);
  opencv = new OpenCV(this, 640/2, 480/2);
  opencv.loadCascade(OpenCV.CASCADE_FRONTALFACE);  
  orcFont = loadFont("OCRAExtended-30.vlw");
  soundengine = new Minim(this);
  sonido2 = soundengine.loadSample("warning_anobjectdetected.mp3", 1024);
  sonido1 = soundengine.loadSample("a_near_object_detected.mp3", 1024);
  
  video.start();
}

void draw() {
  scale(2);
  opencv.loadImage(video);

  image(video, 0, 0 );

  noFill();
  stroke(#FF0080);
  strokeWeight(3);
  Rectangle[] faces = opencv.detect();
  println(faces.length);
  

  for (int i = 0; i < faces.length; i++) {
    println(faces[i].x + "," + faces[i].y);
    rect(faces[i].x, faces[i].y, faces[i].width, faces[i].height);
     sonido1.trigger();
    delay (3000);
    sonido2.stop();
  }
}

void captureEvent(Capture c) {
  c.read();
}
