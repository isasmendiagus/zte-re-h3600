// module: mt7915.ko
// function: IsGratuitousARP @ 0x225254
// size: 172 bytes
//

undefined4 IsGratuitousARP(undefined4 param_1,ushort *param_2,void *param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 local_16;
  undefined2 local_12;
  
  local_16 = 0xffffffff;
  local_12 = 0xffff;
  if ((((ushort)(*param_2 << 8 | *param_2 >> 8) == 0x806) &&
      (iVar2 = memcmp(param_2 + 8,param_2 + 0xd,4), iVar2 == 0)) &&
     (iVar2 = memcmp(param_3,&local_16,6), iVar2 == 0)) {
    if (DebugLevel < 3) {
      uVar1 = 1;
    }
    else {
      printk("The Packet is GratuitousARP\n");
      uVar1 = 1;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

