// module: mt7915.ko
// function: Get_RBIST_IQ_Data @ 0xeb260
// size: 368 bytes
//

undefined4 Get_RBIST_IQ_Data(int param_1,int param_2,int *param_3,int param_4,int param_5)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar6 = *(int *)(param_1 + 0xa78acc);
  os_zero_mem(param_2,0x400);
  os_zero_mem(param_3,4);
  iVar7 = *(int *)(param_1 + 0xa78a80);
  if (2 < DebugLevel) {
    printk("%s : CapNode = 0x%08x, CapSrc = 0x%08x\n","Get_RBIST_IQ_Data",iVar7,
           *(undefined4 *)(param_1 + 0xa78a84));
  }
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7626) {
    if ((*(int *)(iVar1 + 0x180) != iVar7) && (*(int *)(iVar1 + 0x188) != iVar7)) {
      iVar3 = *(int *)(iVar1 + 0x184);
      goto joined_r0x000eb398;
    }
  }
  else {
    iVar3 = *(int *)(iVar1 + 0x17c);
joined_r0x000eb398:
    if (iVar3 != iVar7) {
      uVar2 = *(uint *)(iVar1 + 0x170);
      goto LAB_000eb2f4;
    }
  }
  uVar2 = *(uint *)(iVar1 + 0x16c);
LAB_000eb2f4:
  uVar4 = *(uint *)(param_1 + 0xa78a68);
  if ((*(uint *)(param_1 + 0xa78a7c) < uVar2) && (uVar4 == 0)) {
    uVar4 = uVar2 - *(uint *)(param_1 + 0xa78a7c);
    *(uint *)(param_1 + 0xa78a68) = uVar4;
  }
  puVar5 = (undefined4 *)(param_2 + -4);
  iVar1 = 0;
  do {
    if (uVar2 == uVar4) {
      *param_3 = iVar1;
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 0xa78a68) = 0;
      }
      return 1;
    }
    iVar1 = iVar1 + 1;
    puVar5 = puVar5 + 1;
    *puVar5 = *(undefined4 *)(iVar6 + uVar4 * 0x20 + (param_4 + param_5 * 2) * 4);
    uVar4 = *(int *)(param_1 + 0xa78a68) + 1;
    *(uint *)(param_1 + 0xa78a68) = uVar4;
  } while (iVar1 != 0x100);
  *param_3 = 0x100;
  return 1;
}

