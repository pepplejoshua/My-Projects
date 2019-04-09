int count = round(random(10, 15));
Ball balls[] = new Ball[count];

void setup()
{
  size(640, 360);

  for (int i = 0; i < count; ++i)
  {
    balls[i] = new Ball();
  }
}

void draw()
{
  background(0, 50, 50);

  for (int i = 0; i < count; ++i)
  {
    balls[i].logic();
    balls[i].show();
  }
}
