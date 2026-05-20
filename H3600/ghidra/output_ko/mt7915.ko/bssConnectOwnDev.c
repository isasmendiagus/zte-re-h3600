// module: mt7915.ko
// function: bssConnectOwnDev @ 0x1c28ec
// size: 148 bytes
//

void bssConnectOwnDev(undefined4 param_1,int param_2,undefined4 param_3)

{
  byte bVar1;
  byte bVar2;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  bVar1 = *(byte *)(param_2 + 0xc);
  local_18 = *(undefined4 *)(param_2 + 0x1c);
  bVar2 = bVar1;
  if (4 < bVar1) {
    bVar2 = 0;
  }
  local_14 = 0;
  local_1c = (uint)CONCAT12(*(undefined1 *)(param_2 + 0x106),CONCAT11(bVar1,bVar2));
  local_20 = 0x100000;
  if (2 < DebugLevel) {
    printk("%s, ucHwBSSIndex = %d, ucOwnMacIdx = %d, ucBandIdx = %d, u4ConnectionType = %x\n",
           "bssConnectOwnDev",bVar2,bVar1,*(undefined1 *)(param_2 + 0x106),local_18);
  }
  AndesAppendCmdMsg(param_3,&local_20,0x10);
  return;
}

