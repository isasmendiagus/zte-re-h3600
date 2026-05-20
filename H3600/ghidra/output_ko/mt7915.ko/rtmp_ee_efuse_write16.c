// module: mt7915.ko
// function: rtmp_ee_efuse_write16 @ 0x1d2fc4
// size: 128 bytes
//

undefined4 rtmp_ee_efuse_write16(undefined4 param_1,uint param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  bool bVar2;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  undefined1 auStack_17 [3];
  
  local_28 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  local_2c = 0;
  MtCmdEfuseAccessRead(param_1,param_2 & 0xffff,&local_28,&local_2c);
  puVar1 = (undefined1 *)((param_2 & 0xf) + 1);
  bVar2 = puVar1 != &DAT_00000010;
  if (bVar2) {
    puVar1 = &stack0xffffffe8 + (int)puVar1;
  }
  *(char *)((int)&local_28 + (param_2 & 0xf)) = (char)param_3;
  if (bVar2) {
    puVar1[-0x10] = (char)((uint)param_3 >> 8);
  }
  MtCmdEfuseAccessWrite(param_1,param_2 & 0xffff,&local_28);
  return 0;
}

