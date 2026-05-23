// module: mt7915.ko
// function: RRM_InsertSTARRMEnCapIE @ 0x21cefc
// size: 180 bytes
//

void RRM_InsertSTARRMEnCapIE(int param_1,undefined4 param_2,int *param_3,int param_4)

{
  undefined1 local_36;
  undefined1 local_35;
  int local_34;
  undefined4 local_30;
  undefined4 uStack_2c;
  
  local_36 = 5;
  local_35 = 0x46;
  if (param_4 < (int)(uint)*(byte *)(param_1 + 0x794ab8)) {
    param_1 = param_1 + param_4 * 0x2137b0;
    local_30 = *(undefined4 *)(&DAT_0036e6f3 + param_1);
    uStack_2c = *(undefined4 *)(&DAT_0036e6f7 + param_1);
    MakeOutgoingFrame(param_2,&local_34,1,&local_35,1,&local_36,5,&local_30,0xffffffff);
    *param_3 = *param_3 + local_34;
  }
  return;
}

