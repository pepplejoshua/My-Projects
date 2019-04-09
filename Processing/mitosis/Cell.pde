class Cell
{
  float x, y;
  
  int red, green, blue, si;

  Helper v;
  
  Cell(float xa, float ya, int s)
  {
    this.x = xa;
    this.y = ya;
    si = s;
    v = new Helper();
    red = gen(3, 255);
    green = gen(3, 255);
    blue = gen(3, 255);
  }

  boolean clicked(float a, float b)
  {
    int d = v.distance(this.x, this.y, a, b);
    
    if (d < this.si)
      return true;
     else
       return false;
  }

  void move()
  {
    v.rand();
    this.x += v.xi;
    this.y += v.yi;
  }

  void show()
  {
    noStroke();
    fill(red, green, blue, 100);
    ellipse(x, y, si, si);
  }
}

class Helper
{
  float xi, yi;

  void rand()
  {
    xi = random(-1, 1);
    yi = random(-1, 1);
  }
  
  int distance(float a, float b, float c, float d)
  {
      
      int dis =  round(sqrt(sq(c - a) + sq(d - b)));
      return dis;
  }
}
