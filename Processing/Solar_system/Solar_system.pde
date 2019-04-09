import peasy.*;

CBody sun;
boolean orb;
PeasyCam cam;

PImage sun_img; 
PImage[] textures = new PImage[10];

void setup() {
  size(1000, 1000, P3D);
  // location, color, radius (which is used for size, * 2), speed
  cam = new PeasyCam(this, 2000);
  textures[0] = loadImage("mercury.jpg");
  textures[1] = loadImage("venus.jpg");
  textures[2] = loadImage("earth.jpg");
  textures[3] = loadImage("mars.jpg");
  textures[4] = loadImage("jupiter.jpg");
  textures[5] = loadImage("saturn.jpg");
  textures[6] = loadImage("uranus.jpg");
  textures[7] = loadImage("neptune.jpg");
  textures[8] = loadImage("pluto.jpg");
  textures[9] = loadImage("moon.jpg");
  sun_img = loadImage("sun.jpg");


  sun = new CBody(0, width * 0.06, 0, sun_img);

  sun.createMoons(9, 2);
  orb = false;
}

void draw() {
  background(0);
  lights();
  //translate(width/2, height/2);
  sun.draw();


  if (orb)
    sun.orbit();
}

void mouseClicked()
{
  orb = !orb;
}
