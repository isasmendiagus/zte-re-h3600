// module: mt7915.ko
// function: bssUpdateChannel @ 0x1c3d1c
// size: 236 bytes
//

void bssUpdateChannel(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined2 local_2c;
  undefined2 local_2a;
  undefined1 local_28;
  undefined1 local_27;
  undefined1 local_26;
  undefined1 local_25;
  uint local_24;
  
  local_28 = *(undefined1 *)(param_2 + 0x60);
  local_27 = *(undefined1 *)(param_2 + 0x61);
  local_26 = *(undefined1 *)(param_2 + 0x62);
  local_25 = *(undefined1 *)(param_2 + 0x5e);
  local_2c = 2;
  local_2a = 0xc;
  local_24 = 0x100;
  if (((*(byte *)(param_2 + 0x22) & 0xc0) != 0) && (*(int *)(param_2 + 0x1c) == 0x10001)) {
    local_24 = 0;
    iVar1 = is_ru26_disable_channel(param_1,local_28,*(byte *)(param_2 + 0x22));
    if (iVar1 != 0) {
      local_24 = CONCAT31(local_24._1_3_,1);
    }
  }
  if (2 < DebugLevel) {
    printk("(%s), ucPrimCh=%d, ucCentChSeg0=%d, ucCentChSeg1=%d, BW=%d, ucHetbRU26Disable=%d, ucHetbAllDisable=%d\n"
           ,"bssUpdateChannel",local_28,local_27,local_26,local_25,local_24 & 0xff,
           local_24 >> 8 & 0xff);
  }
  AndesAppendCmdMsg(param_3,&local_2c,0xc);
  return;
}

