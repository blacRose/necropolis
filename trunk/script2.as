
void main()
{
  object A = _object(0,320);
  Print(GetObjectX(A));
  Print(GetObjectY(A));
  int x=GetObjectX(A);
  int y=GetObjectY(A);
  SetObjectTag(A, "Monster");
  SetObjectSprite(A, "img.bmp");
  for(;;)
  {
    SetObjectX(A, x);
    SetObjectY(A, y);
    Sleep(30);
  }
}
