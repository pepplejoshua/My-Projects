ArrayList<Cell> cells;

void setup()
{
  size(700, 700);
  cells = new ArrayList<Cell>();

  cells.add(new Cell(gen(30, width-20), gen(30, height-20), gen(40, 80)));
  cells.add(new Cell(gen(30, width-20), gen(30, height-20), gen(40, 80)));
}

void draw()
{ 
  background(0, 55, 55);
  for (int i = 0; i < cells.size(); ++i)
  {
    cells.get(i).move();
    cells.get(i).show();
  }
}

void mousePressed()
{
  boolean pressed = false;
  for (int i = 0; i < cells.size(); ++i)
  {
    if (cells.get(i).clicked(mouseX, mouseY))
    {
      pressed = true;
      Cell A = new Cell(cells.get(i).x, cells.get(i).y, cells.get(i).si/2);
      A.red = cells.get(i).red;
      A.green = cells.get(i).green;
      A.blue = cells.get(i).blue;

      Cell B = new Cell(cells.get(i).x, cells.get(i).y, cells.get(i).si/2);
      B.red = cells.get(i).red;
      B.green = cells.get(i).green;
      B.blue = cells.get(i).blue;

      cells.add(A);
      cells.add(B);
    }
  }

  if (!pressed)
  {
    Cell C = new Cell(mouseX, mouseY, gen(40, 80));
    C.red = gen(3, 255);
    C.green = gen(3, 255);
    C.blue = gen(3, 255);

    cells.add(C);
  }
}


int gen(int s, int e)
{
  assert(s < e);
  return round(random(s, e));
}
