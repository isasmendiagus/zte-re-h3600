// module: mt7915.ko
// function: AP_E2PROM_IOCTL_PostCtrl @ 0x150508
// size: 144 bytes
//

void AP_E2PROM_IOCTL_PostCtrl(int param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uStack_10;
  
  uStack_10 = param_4;
  sVar1 = strlen(param_2);
  uVar4 = *(uint *)(param_1 + 0x10);
  uVar2 = sVar1 & 0xffff;
  *(short *)(param_1 + 0x14) = (short)sVar1;
  uVar3 = *(uint *)(((uint)&uStack_10 & 0xffffe000) + 8);
  if (!CARRY4(uVar4,uVar2) && uVar4 + uVar2 <= uVar3) {
    uVar3 = 0;
  }
  if (uVar3 == 0) {
    uVar2 = __copy_to_user(uVar4,param_2);
    if (uVar2 == 0) {
      return;
    }
  }
  else if (uVar2 == 0) {
    return;
  }
  if (DebugLevel < 3) {
    return;
  }
  printk("%s: copy_to_user() fail\n","AP_E2PROM_IOCTL_PostCtrl",uVar2,uStack_10);
  return;
}

