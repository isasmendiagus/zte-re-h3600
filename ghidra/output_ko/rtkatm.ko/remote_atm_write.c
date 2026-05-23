// module: rtkatm.ko
// function: remote_atm_write @ 0x10554
// size: 252 bytes
//

uint remote_atm_write(undefined4 param_1,uint param_2,uint param_3)

{
  size_t sVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  char cStack_35;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  uVar6 = param_3;
  if (0x13 < param_3) {
    uVar6 = 0x14;
  }
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  local_28 = 0;
  local_24 = 0;
  if (param_2 != 0) {
    uVar5 = *(uint *)(((uint)&local_48 & 0xffffe000) + 8);
    uVar3 = param_2 + uVar6;
    uVar4 = uVar3;
    if (!CARRY4(param_2,uVar6)) {
      uVar4 = uVar3 - (uVar5 + 1);
    }
    if (!CARRY4(param_2,uVar6) && uVar3 <= uVar5) {
      uVar5 = 0;
    }
    if (uVar5 == 0) {
      iVar2 = __copy_from_user(&local_34,param_2,uVar6);
      if (iVar2 == 0) {
LAB_000105bc:
        sVar1 = strlen((char *)&local_34);
        local_44 = 0x11b83;
        local_40 = 0x11b84;
        local_3c = 0x11b85;
        local_48 = 0x11b82;
        (&cStack_35)[sVar1] = '\0';
        sscanf((char *)&local_34,"%hhx %hhx %hhx %hhx %hhx %hhx",&dmac,0x11b81);
        return param_3;
      }
    }
    else {
      if (uVar6 == 0) goto LAB_000105bc;
      __memzero(&local_34,uVar6,uVar4);
    }
  }
  return 0xfffffff2;
}

