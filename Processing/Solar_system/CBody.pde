class CBody {
  float dist;
  float angle;
  float o_Speed;
  float rad;
  CBody[] children;
  PVector v;
  PShape globe;
  IntList moons;
  CBody(float d, float r, float o, PImage img) {
    v = new PVector(1, 0, 0);
    dist = d;
    angle = 90;
    v.mult(dist);
    rad = r;
    o_Speed = o;
    moons= new IntList(9);
    moons.append(0);
    moons.append(0);
    moons.append(1);
    moons.append(2);
    moons.append(1);
    moons.append(1);
    moons.append(1);
    moons.append(1);
    moons.append(2);

    noStroke();
    noFill();
    globe = createShape(SPHERE, rad);
    globe.setTexture(img);
  }

  void orbit() {
    angle += o_Speed;
    if (children != null)
    {
      for (CBody child : children)
      {
        child.orbit();
      }
    }
  }

  void createMoons(int count, int maxLevel)
  {
    int currentL = 1;
    children = new CBody[count];
    float ac_rad = rad * 0.5;
    float o_speed = 1 / (rad*2);
    for (int i = 0; i < count; i++)
    {
      float r = rad / (currentL*3);
      float startD = random((rad + r) * 1.5, (rad + r) * 2);
      o_speed -= random(0.0001, 0.0005);  
      if (currentL < maxLevel)
      {
        children[i] = new CBody(startD + ac_rad, r, o_speed, textures[i]);
        ac_rad += startD;
        children[i].createMoons(moons.get(i), maxLevel - 1);
      } else if (currentL == maxLevel)
      {
        children[i] = new CBody(startD + ac_rad, r, o_speed, textures[9]);
        ac_rad += startD;
      }
    }
  }

  void draw() {
    pushMatrix();
    PVector v2 = new PVector(1, 0, 1);
    PVector p = v.cross(v2);
    rotate(angle, p.x, p.y, p.z);
    stroke(255);
    line(0, 0, 0, v.x, v.y, v.z);
    translate(v.x, v.y, v.z);

    shape(globe);
    //sphere(rad);
    //ellipse(0, 0, rad*2, rad*2);

    if (children != null)
    {
      for (CBody child : children)
      {
        child.draw();
      }
    }
    popMatrix();
  }
}
