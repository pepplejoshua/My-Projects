class Ball
{
  int circleX;
  int circleY;
  int circleS;
  int growth;

  int actualSpeed;
  int xSpeed;
  int ySpeed;


  int red;
  int green;
  int blue;

  Ball()
  {
    circleX = round(random(0, width));
    circleY = round(random(0, height));
    circleS = 24;
    actualSpeed = round(random(1, circleS/2));
    xSpeed = actualSpeed;
    ySpeed = actualSpeed;
    randomize();
  }

  void randomize()
  {
    red = round(random(30, 255));
    green = round(random(30, 255));
    blue = round(random(30, 255));

    actualSpeed = round(random(1, circleS/2));

    growth = round(random(15, 32));
  }

  void logic()
  {
    //controls the x coordinate
    if (circleX+2 > width)
    {
      randomize();
      xSpeed *= -1;
      circleX += xSpeed;
      circleS = growth;
    } else if (circleX < 0)
    {
      randomize();
      xSpeed = actualSpeed;
      circleX += xSpeed;
      circleS = growth;
    } else
      circleX += xSpeed;


    //controls y coordinate
    if (circleY+2 > height)
    {
      randomize();
      ySpeed *= -1;
      circleY += ySpeed;
      circleS = growth;
    } else if (circleY < 0)
    {
      randomize();
      ySpeed = actualSpeed;
      circleY += ySpeed;
      circleS = growth;
    } else
      circleY += ySpeed;
  }

  void show()
  {
    fill(red, green, blue);
    noStroke();
    ellipse(circleX, circleY, circleS, circleS);
  }
}
