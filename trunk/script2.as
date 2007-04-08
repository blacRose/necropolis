
void main()
{
  object_t A = _object(0,320);
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
