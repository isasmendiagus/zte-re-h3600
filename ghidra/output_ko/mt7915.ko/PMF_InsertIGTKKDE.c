// module: mt7915.ko
// function: PMF_InsertIGTKKDE @ 0x219e30
// size: 340 bytes
//

void PMF_InsertIGTKKDE(int param_1,int param_2,int param_3,int *param_4)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  size_t __n;
  undefined4 uVar4;
  int iVar5;
  
  if (*(char *)(param_1 + 0x286285) != '\x01') {
    return;
  }
  iVar5 = param_1 + param_2 * 0x5834;
  if (iVar5 == -0x2b7654) {
    return;
  }
  uVar2 = *(uint *)("Group%d airtime token: max %d(0x%08X), min %d(0x%08X)\n" + iVar5 + 0xb);
  if ((uVar2 & 0xa00) == 0) {
    if ((uVar2 & 0x1400) == 0) {
      if (DebugLevel < 0) {
        return;
      }
      printk("%s : unknown igtk cipher %x.\n","PMF_InsertIGTKKDE",uVar2,param_4);
      return;
    }
    uVar4 = 0x28;
    __n = 0x20;
    uVar3 = 0x28;
  }
  else {
    uVar4 = 0x18;
    __n = 0x10;
    uVar3 = 0x18;
  }
  WPA_ConstructKdeHdr(9,uVar3);
  __memzero(param_3 + 6,uVar4);
  param_2 = param_2 * 0x5834;
  *(char *)(param_3 + 6) =
       "Group%d airtime token: max %d(0x%08X), min %d(0x%08X)\n"[param_1 + param_2 + 0xf];
  cVar1 = "Group%d airtime token: max %d(0x%08X), min %d(0x%08X)\n"[param_1 + param_2 + 0xf];
  memmove((void *)(param_3 + 8),
          "Sta%d deficit token: ac0 %d(0x%08X), ac1 %d(0x%08X), ac2 %d(0x%08X), ac3 %d(0x%08X)\n" +
          param_1 + param_2 + (uint)(cVar1 == '\x05') * 6 + 0x18,6);
  memmove((void *)(param_3 + 0xe),
          "Group%d airtime token: max %d(0x%08X), min %d(0x%08X)\n" +
          param_1 + param_2 + (uint)(cVar1 == '\x05') * 0x20 + 0x10,__n);
  *param_4 = *param_4 + 0xe + __n;
  return;
}

