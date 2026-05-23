// module: mt7915.ko
// function: twt_tear_down @ 0x167678
// size: 188 bytes
//

void twt_tear_down(int param_1,uint param_2,undefined4 param_3)

{
  int iVar1;
  int local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  iVar1 = *(int *)(param_1 + 8);
  local_28 = 0;
  local_24 = 0;
  local_2c = param_2 & 0xffff;
  local_30 = param_1;
  os_move_mem((void *)((int)&local_2c + 2),(void *)(param_2 * 0x14c0 + iVar1 + 0xa1e0c),6);
  local_24 = CONCAT31(local_24._1_3_,(char)param_3);
  MlmeEnqueueWithWdev(iVar1,9,0x1c,0x10,&local_30,0,param_1);
  RtmpOsMlmeUp(iVar1 + 0x286298);
  if (2 < DebugLevel) {
    printk("%s: wcid(%d),flow_id(%d)\n","twt_tear_down",param_2,param_3);
  }
  return;
}

