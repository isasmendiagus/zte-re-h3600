// module: mt7915.ko
// function: rtmp_ee_efuse_read16 @ 0x1d2f18
// size: 168 bytes
//

undefined4 rtmp_ee_efuse_read16(undefined4 param_1,uint param_2,undefined2 *param_3)

{
  undefined4 uVar1;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  local_14 = 0;
  local_24 = 0;
  MtCmdEfuseAccessRead(param_1,param_2 & 0xffff,&local_20,&local_24);
  if ((param_2 & 0xf) != 0xf) {
    *param_3 = *(undefined2 *)((int)&local_20 + (param_2 & 0xf));
  }
  if (local_24 == 0) {
    uVar1 = 1;
  }
  else if (DebugLevel < 4) {
    uVar1 = 0;
  }
  else {
    printk("%s:  Not found valid block for this offset (%x)\n","rtmp_ee_efuse_read16",param_2);
    uVar1 = 0;
  }
  return uVar1;
}

