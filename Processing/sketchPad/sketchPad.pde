// default global variables
color background_color = color(255, 255, 255);
boolean drawing = false;
color d_color = color(125, 125, 125);

// colors
color a = color(255, 128, 0);
color b = color(0, 255, 0);
color c = color(0, 0, 255);
color d = color(255, 192, 203);

// this describes the drawing canvas margin
int canvas_start = 135;

// strokeWeight
int currentStrokeWeight = 1;

// coordinates
int box_wd = 55;
int x_coord = 30;
int boxa_y = 20;
int boxb_y = 100;
int boxc_y = 180;
int boxd_y = 260;

void setup() {
  // This will help make sure the program refreshes fast enough to prevent
  // the user from drawing in the colors column
  frameRate(frameRate + 100);
  size(640, 600);
  background(background_color);
  stroke(d_color);
  
  // set initial stroke weight or reset
  strokeWeight(currentStrokeWeight);
  // draw the vertical divider between canvas and palette area
  line(canvas_start-20, 0, canvas_start-20, height);
  
  // draw the 4 palette color boxes
  fill(a);
  rect(x_coord, boxa_y, box_wd, box_wd, 7);
  
  fill(b);
  rect(x_coord, boxb_y, box_wd, box_wd, 7);
  
  fill(c);
  rect(x_coord, boxc_y, box_wd, box_wd, 7);
  
  fill(d);
  rect(x_coord, boxd_y, box_wd, box_wd, 7);
}

void draw() {
  // the only thing to do in draw is.... draw ;) (that's if the user is in draw mode)
  if (mouseX > canvas_start && drawing) {
    line(pmouseX, pmouseY, mouseX, mouseY);
  }
}

void mousePressed() {
  // if mouseX is with the box width area, then proceed to check whether mouseY falls within the depth
  // of any of the palette color boxes and then set the stroke for drawing to the color for that box
  if (mouseX >= x_coord && mouseX <= (x_coord + box_wd)) {
     if (mouseY >= boxa_y && mouseY <= (boxa_y + box_wd)) {
         stroke(a);
     }
     else if (mouseY >= boxb_y && mouseY <= (boxb_y + box_wd)) {
         stroke(b);
     }
     else if (mouseY >= boxc_y && mouseY <= (boxc_y + box_wd)) {
         stroke(c);
     }
     else if (mouseY >= boxd_y && mouseY <= (boxd_y + box_wd)) {
         stroke(d);
     }
  }
  else if (mouseX > 150)
    // if the user is in the canvas area, toggle drawing mode (start drawing or stop drawing
    drawing = !drawing;
}

void keyPressed() {
  if (key == 'r' || key == 'R') {
    // reset the background color and setup the canvas for drawing again and then make sure the user is not 
    // drawing mode
    background(background_color); 
    currentStrokeWeight = 1;
    setup();
    drawing = false;
  }
  else if (key == 's' || key == 'S') {
    // this allows the user to user the base color in between using palette colors
    stroke(d_color);
  }
  // increase stroke weight 
  else if(keyCode == UP) {
    if (currentStrokeWeight < 10) {
      currentStrokeWeight += 1;
      strokeWeight(currentStrokeWeight);
    }
  }
  // decrease stroke weight
  else if(keyCode == DOWN) {
    if (currentStrokeWeight > 1) {
      currentStrokeWeight -= 1;
      strokeWeight(currentStrokeWeight);
    }
  }
}
