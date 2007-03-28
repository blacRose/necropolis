
void main()
{
  WindowSetTitle("Necropolis Cross-Platform Build");
  Sleep(30);
  object A = _object(32,49);
  Print(GetObjectX(A));
  Print(GetObjectY(A));
  int x=GetObjectX(A);
  int y=GetObjectY(A);
  SetObjectTag(A, "Monster");
  SetObjectSprite(A, "ultrax1.gif");
  for(;;)
  {
    if(GetKeyPressed(KEY_LEFT))x-=2;
    if(GetKeyPressed(KEY_RIGHT))x+=2;
    if(GetKeyPressed(KEY_UP))y-=2;
    if(GetKeyPressed(KEY_DOWN))y+=2;
    SetObjectX(A, x);
    SetObjectY(A, y);
    Sleep(15);
  }
}
