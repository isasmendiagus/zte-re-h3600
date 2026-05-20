// module: mt7915.ko
// function: rlmCalCacheDump @ 0x1c8a08
// size: 300 bytes
//

void rlmCalCacheDump(uint *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  uint *puVar3;
  int iVar4;
  
  uVar2 = *param_1;
  if ((uVar2 & 1) != 0) {
    hex_dump("TxLpf",param_1 + 3,0xd8,param_4,param_4);
    uVar2 = *param_1;
  }
  if ((uVar2 & 2) != 0) {
    hex_dump(&_LC12,param_1 + 0x3a,0x510);
    uVar2 = *param_1;
  }
  if ((uVar2 & 4) != 0) {
    hex_dump(&_LC13,param_1 + 0x17f,0x510);
    uVar2 = *param_1;
  }
  if ((uVar2 & 8) != 0) {
    hex_dump(&_LC14,param_1 + 0x2c4,0x360);
    uVar2 = *param_1;
  }
  puVar3 = param_1 + 0x39e;
  iVar4 = 0;
  while( true ) {
    uVar1 = 1 << (iVar4 + 4U & 0xff);
    if (uVar1 == (uVar2 & uVar1)) {
      if (2 < DebugLevel) {
        printk("RxFD(%d)\n",iVar4);
      }
      hex_dump(&_LC16,puVar3,0x540);
    }
    iVar4 = iVar4 + 1;
    puVar3 = puVar3 + 0x152;
    if (iVar4 == 9) break;
    uVar2 = *param_1;
  }
  return;
}

