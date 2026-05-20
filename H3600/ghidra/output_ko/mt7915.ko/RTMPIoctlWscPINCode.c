// module: mt7915.ko
// function: RTMPIoctlWscPINCode @ 0x3c824
// size: 368 bytes
//

void RTMPIoctlWscPINCode(int *param_1,int param_2)

{
  size_t sVar1;
  uint uVar2;
  char *pcVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 extraout_r1;
  undefined4 extraout_r1_00;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  bool bVar9;
  undefined8 uVar10;
  char *local_20;
  char local_19 [9];
  
  local_19[0] = '\0';
  uVar8 = *(uint *)(*param_1 + 0x3c);
  local_19[1] = 0;
  local_19[2] = 0;
  local_19[3] = 0;
  local_19[4] = 0;
  local_19[5] = 0;
  local_19[6] = 0;
  local_19[7] = 0;
  local_19[8] = 0;
  os_alloc_mem(0,&local_20,0x80);
  if (local_20 != (char *)0x0) {
    uVar8 = uVar8 & 0xff;
    __memzero(local_20,0x80);
    if (param_1[uVar8 * 0x160d + 0xae152] != 0) {
      if ((char)param_1[uVar8 * 0x160d + 0xae153] == '\b') {
        pcVar3 = "%08u";
      }
      else {
        pcVar3 = "%04u";
      }
      sprintf(local_19,pcVar3);
      strcpy(local_20,local_19);
    }
    pcVar3 = local_20;
    sVar1 = strlen(local_20);
    uVar8 = (uint)*(ushort *)(param_2 + 0x14);
    bVar9 = sVar1 < uVar8;
    if (bVar9) {
      uVar8 = sVar1 + 1;
    }
    uVar2 = *(uint *)(param_2 + 0x10);
    uVar6 = uVar8;
    if (bVar9) {
      uVar6 = uVar8 & 0xffff;
      *(short *)(param_2 + 0x14) = (short)uVar8;
    }
    uVar7 = *(uint *)(((uint)&local_20 & 0xffffe000) + 8);
    uVar4 = uVar2 + uVar6;
    uVar8 = uVar4;
    if (!CARRY4(uVar2,uVar6)) {
      uVar8 = uVar4 - (uVar7 + 1);
    }
    uVar10 = CONCAT44(uVar8,uVar6);
    if (!CARRY4(uVar2,uVar6) && uVar4 <= uVar7) {
      uVar7 = 0;
    }
    if (uVar7 == 0) {
      uVar10 = __copy_to_user(uVar2,pcVar3);
    }
    uVar5 = (undefined4)((ulonglong)uVar10 >> 0x20);
    if ((int)uVar10 != 0) {
      printk("%s:%d copy_to_user fail! ret=%d\n","RTMPIoctlWscPINCode",0x451d,(int)uVar10);
      uVar5 = extraout_r1_00;
    }
    if (2 < DebugLevel) {
      printk(&_LC758,local_20);
      uVar5 = extraout_r1;
    }
    os_free_mem(local_20,uVar5);
  }
  return;
}

