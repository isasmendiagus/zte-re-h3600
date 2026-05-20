// module: mt7915.ko
// function: notify_timer_callback @ 0x206e60
// size: 256 bytes
//

void notify_timer_callback(undefined4 param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  undefined1 auStack_34 [8];
  int local_2c;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  undefined1 local_24;
  undefined1 auStack_23 [15];
  
  iVar2 = *(int *)(param_2 + 8);
  if (2 < DebugLevel) {
    printk("%s: enter\n","notify_timer_callback");
  }
  os_zero_mem(&local_2c,0x14);
  local_25 = 4;
  local_27 = 0x4f;
  local_28 = 0;
  local_26 = 0;
  local_24 = 0;
  local_2c = param_2;
  FUN_00206840(param_2);
  hc_bcolor_get_bitmap(param_2,auStack_34);
  os_move_mem(auStack_23,auStack_34,8);
  MlmeEnqueueWithWdev(iVar2,9,0x1d,0x14,&local_2c,0,param_2);
  RtmpOsMlmeUp(iVar2 + 0x286298);
  bVar1 = *(char *)(param_2 + 0xa44) + 1;
  *(byte *)(param_2 + 0xa44) = bVar1;
  if (bVar1 < 3) {
    RTMPSetTimer(param_2 + 0xa48,(uint)*(byte *)(param_2 + 0xa45) * 1000);
  }
  else {
    *(undefined1 *)(param_2 + 0xa46) = 0;
  }
  return;
}

