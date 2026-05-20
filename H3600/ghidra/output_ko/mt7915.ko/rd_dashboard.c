// module: mt7915.ko
// function: rd_dashboard @ 0x155614
// size: 496 bytes
//

/* WARNING: Type propagation algorithm not settling */

undefined4 rd_dashboard(int param_1,int param_2)

{
  byte bVar1;
  size_t sVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  char *pcVar6;
  char *local_28 [3];
  char *local_1c [2];
  
  os_alloc_mem(param_1,local_1c,0x800);
  uVar3 = 0;
  if (local_1c[0] != (char *)0x0) {
    __memzero(local_1c[0],0x800);
    pcVar6 = local_1c[0];
    local_1c[0][0] = '\n';
    local_1c[0][1] = '\0';
    sVar2 = strlen(local_1c[0]);
    local_28[0] = "====================";
    sprintf(pcVar6 + sVar2,"%s%-16s%s\n","===================="," RvR Debug Info ");
    bVar1 = *(byte *)(param_1 + 0xa7c2e8);
    if ((bVar1 & 1) != 0) {
      printBasicinfo(param_1,local_1c[0]);
      bVar1 = *(byte *)(param_1 + 0xa7c2e8);
    }
    if ((bVar1 & 2) != 0) {
      printWcid(param_1,local_1c[0]);
      bVar1 = *(byte *)(param_1 + 0xa7c2e8);
    }
    if ((bVar1 & 4) != 0) {
      printMacCounter(param_1,local_1c[0]);
      bVar1 = *(byte *)(param_1 + 0xa7c2e8);
    }
    if ((bVar1 & 8) != 0) {
      printPhyCounter(param_1,local_1c[0]);
      bVar1 = *(byte *)(param_1 + 0xa7c2e8);
    }
    if ((bVar1 & 0x10) != 0) {
      printNoise(param_1,local_1c[0]);
      bVar1 = *(byte *)(param_1 + 0xa7c2e8);
    }
    if ((bVar1 & 0x80) != 0) {
      printOthers(param_1,local_1c[0]);
    }
    pcVar6 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    sprintf(pcVar6 + sVar2,"%s\n","========================================================");
    pcVar6 = local_1c[0];
    sVar2 = strlen(local_1c[0]);
    uVar4 = *(uint *)(param_2 + 0x10);
    *(short *)(param_2 + 0x14) = (short)sVar2;
    uVar5 = *(uint *)(((uint)local_28 & 0xffffe000) + 8);
    if (!CARRY4(uVar4,sVar2 & 0xffff) && uVar4 + (sVar2 & 0xffff) <= uVar5) {
      uVar5 = 0;
    }
    if (uVar5 == 0) {
      __copy_to_user(uVar4,pcVar6);
      pcVar6 = local_1c[0];
    }
    os_free_mem(pcVar6);
    if (DebugLevel < 3) {
      uVar3 = 1;
    }
    else {
      printk("%s<-----------------\n","rd_dashboard");
      uVar3 = 1;
    }
  }
  return uVar3;
}

