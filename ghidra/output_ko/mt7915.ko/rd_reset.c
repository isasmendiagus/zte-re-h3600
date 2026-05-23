// module: mt7915.ko
// function: rd_reset @ 0x153c7c
// size: 284 bytes
//

undefined4 rd_reset(undefined4 param_1,undefined4 param_2,int param_3)

{
  size_t sVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uVar4;
  uint extraout_r1;
  uint uVar5;
  uint uVar6;
  char *pcVar7;
  uint uVar8;
  undefined1 auStack_20 [4];
  char *local_1c [2];
  
  os_alloc_mem(param_1,local_1c,0x800);
  uVar2 = 0;
  if (local_1c[0] != (char *)0x0) {
    __memzero(local_1c[0],0x800);
    pcVar7 = local_1c[0];
    local_1c[0][0] = '\n';
    local_1c[0][1] = '\0';
    sVar1 = strlen(local_1c[0]);
    builtin_strncpy(pcVar7 + sVar1,"Reset all counter!\n",0x14);
    Set_ResetStatCounter_Proc(param_1,0);
    pcVar7 = local_1c[0];
    sVar1 = strlen(local_1c[0]);
    uVar5 = *(uint *)(param_3 + 0x10);
    uVar8 = sVar1 & 0xffff;
    *(short *)(param_3 + 0x14) = (short)sVar1;
    uVar6 = *(uint *)(((uint)auStack_20 & 0xffffe000) + 8);
    uVar3 = uVar5 + uVar8;
    uVar4 = uVar3;
    if (!CARRY4(uVar5,uVar8)) {
      uVar4 = uVar3 - (uVar6 + 1);
    }
    if (!CARRY4(uVar5,uVar8) && uVar3 <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 == 0) {
      __copy_to_user(uVar5,pcVar7,uVar8);
      uVar4 = extraout_r1;
      pcVar7 = local_1c[0];
    }
    os_free_mem(pcVar7,uVar4);
    if (DebugLevel < 3) {
      uVar2 = 1;
    }
    else {
      printk("%s<-----------------\n","rd_reset");
      uVar2 = 1;
    }
  }
  return uVar2;
}

