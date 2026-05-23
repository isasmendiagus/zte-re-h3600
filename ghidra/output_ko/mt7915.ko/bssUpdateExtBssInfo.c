// module: mt7915.ko
// function: bssUpdateExtBssInfo @ 0x1c3184
// size: 180 bytes
//

void bssUpdateExtBssInfo(undefined4 param_1,int param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 local_20;
  int local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  uVar1 = (uint)*(byte *)(param_2 + 0xc);
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  if (uVar1 < 5) {
    printk(&_LC28,0xd6a);
    dump_stack();
    uVar1 = (uint)*(byte *)(param_2 + 0xc);
  }
  local_20 = 0x100007;
  local_1c = (uVar1 & 0xf) * 0x1014;
  if (2 < DebugLevel) {
    printk("%s (BSSINFO_EXT_BSS_INFO), ExtBssidIdx = %d, ucMbssTsfOffset = %d\n",
           "bssUpdateExtBssInfo",uVar1 & 0xf);
  }
  AndesAppendCmdMsg(param_3,&local_20,0x10);
  return;
}

