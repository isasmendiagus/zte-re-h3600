// module: mt7915.ko
// function: ApCliIfLookUp @ 0x6b1d8
// size: 132 bytes
//

undefined4 ApCliIfLookUp(int param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = memcmp(&DAT_0036db73 + param_1,param_2,6);
  uVar2 = 0;
  if (iVar1 != 0) {
    iVar1 = memcmp(&DAT_00581323 + param_1,param_2,6);
    if (iVar1 != 0) {
      return 0xffffffff;
    }
    uVar2 = 1;
  }
  if (2 < DebugLevel) {
    printk("%s():ApCliIfIndex=%d\n","ApCliIfLookUp",uVar2);
  }
  return uVar2;
}

