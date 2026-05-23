// module: mt7915.ko
// function: RTMPIoctlGetDriverInfo @ 0xdcd08
// size: 392 bytes
//

void RTMPIoctlGetDriverInfo(int param_1,int param_2)

{
  char *pcVar1;
  size_t sVar2;
  uint uVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 extraout_r1;
  uint uVar6;
  char cVar7;
  uint uVar8;
  uint uVar9;
  ulonglong uVar10;
  undefined4 local_20 [3];
  char *local_14;
  
  os_alloc_mem(0,&local_14,0x1000);
  if (local_14 == (char *)0x0) {
    if (0 < DebugLevel) {
      printk("RTMPIoctlGetDriverInfo - msg memory alloc fail.\n");
    }
  }
  else {
    __memzero(local_14,0x1000);
    cVar7 = *(char *)(param_1 + 0x286285);
    if (cVar7 == '\x01') {
      sprintf(local_14,"Driver version: %s \n","7.1.0.1");
      cVar7 = *(char *)(param_1 + 0x286285);
    }
    pcVar1 = local_14;
    if (cVar7 == '\0') {
      sVar2 = strlen(local_14);
      sprintf(pcVar1 + sVar2,"Driver version: %s \n","7.1.0.1");
    }
    pcVar1 = local_14;
    sVar2 = strlen(local_14);
    local_20[0] = *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc);
    sprintf(pcVar1 + sVar2,"FW ver: 0x%x, HW ver: 0x%x, CHIP ID: 0x%x\n",
            *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x14),
            *(undefined4 *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0x10));
    pcVar1 = local_14;
    sVar2 = strlen(local_14);
    uVar9 = *(uint *)(param_2 + 0x10);
    uVar6 = sVar2 & 0xffff;
    *(short *)(param_2 + 0x14) = (short)sVar2;
    uVar8 = *(uint *)(((uint)local_20 & 0xffffe000) + 8);
    uVar3 = uVar9 + uVar6;
    uVar4 = uVar3;
    if (!CARRY4(uVar9,uVar6)) {
      uVar4 = uVar3 - (uVar8 + 1);
    }
    uVar10 = CONCAT44(uVar4,sVar2) & 0xffffffff0000ffff;
    if (!CARRY4(uVar9,uVar6) && uVar3 <= uVar8) {
      uVar8 = 0;
    }
    if (uVar8 == 0) {
      uVar10 = __copy_to_user(uVar9,pcVar1);
    }
    uVar5 = (undefined4)(uVar10 >> 0x20);
    if (((int)uVar10 != 0) && (0 < DebugLevel)) {
      printk("%s: copy_to_user() fail\n","RTMPIoctlGetDriverInfo");
      uVar5 = extraout_r1;
    }
    os_free_mem(local_14,uVar5);
  }
  return;
}

