// module: mt7915.ko
// function: Bignum_Print @ 0x20c1e4
// size: 164 bytes
//

void Bignum_Print(int *param_1)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  if (param_1 == (int *)0x0) {
    return;
  }
  printk("dmax = %d, top = %d\n",param_1[2],param_1[1]);
  uVar1 = param_1[2];
  iVar3 = uVar1 + 0x3fffffff;
  for (uVar2 = 0; uVar2 < uVar1; uVar2 = uVar2 + 1) {
    if ((3 < uVar2) && ((uVar2 & 3) == 0)) {
      printk(&_LC1);
    }
    uVar1 = *(uint *)(*param_1 + (iVar3 - uVar2) * 4);
    printk("%02x %02x %02x %02x ",uVar1 >> 0x18,(uVar1 << 8) >> 0x18,(uVar1 << 0x10) >> 0x18,
           uVar1 & 0xff);
    uVar1 = param_1[2];
  }
  printk(&_LC1);
  return;
}

