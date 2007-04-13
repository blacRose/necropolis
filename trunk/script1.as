
void main()
{
  WindowSetTitle("Necropolis Cross-Platform Build");
  Sleep(30);
  //object_c objA;
  object_t A = _object(32,49);
  Print(GetObjectX(A));
  Print(GetObjectY(A));
  const int move_distance = 4;
  int x=GetObjectX(A);
  int y=GetObjectY(A);
  SetObjectTag(A, "Monster");
  SetObjectSprite(A, "ultrax1.gif");
  for(;;)
  {
    if(GetKeyPressed(KEY_LEFT))x-=move_distance;
    if(GetKeyPressed(KEY_RIGHT))x+=move_distance;
    if(GetKeyPressed(KEY_UP))y-=move_distance;
    if(GetKeyPressed(KEY_DOWN))y+=move_distance;
    SetObjectX(A, x);
    SetObjectY(A, y);
    Sleep(15);
  }
}
