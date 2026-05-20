// module: mt7915.ko
// function: fp_qm_init @ 0xd448c
// size: 892 bytes
//

undefined4 fp_qm_init(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined2 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  int iVar10;
  bool bVar11;
  undefined2 *local_34;
  int local_30;
  int local_2c [2];
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  iVar10 = *(int *)("Get_RBIST_Raw_Data_Proc" + param_1 + 0x14);
  local_34 = (undefined2 *)0x0;
  local_30 = 0;
  local_2c[0] = 0;
  os_alloc_mem(param_1,&local_34,8);
  if (local_34 == (undefined2 *)0x0) {
    if (-1 < DebugLevel) {
      printk("%s os_alloc_mem fail\n","fp_qm_init");
    }
    return 1;
  }
  __memzero(local_34,8);
  puVar6 = (undefined4 *)(param_1 + 0x285b30);
  iVar7 = 0;
  puVar9 = (undefined4 *)(param_1 + 0x285b28);
  puVar8 = (undefined4 *)(param_1 + 0x285b38);
  bVar11 = *(char *)(iVar1 + 0x20) != '\0';
  if (bVar11) {
    uVar4 = 0x100;
  }
  else {
    uVar4 = 0x200;
  }
  local_34[1] = uVar4;
  if (bVar11) {
    uVar4 = 0x200;
  }
  else {
    uVar4 = 0x400;
  }
  local_34[2] = 0x2000;
  local_34[3] = uVar4;
  *local_34 = 0x2000;
  puVar2 = (undefined4 *)(param_1 + 0x285b40);
  *(undefined2 **)(param_1 + 0x285ae8) = local_34;
  puVar5 = puVar6;
  do {
    iVar3 = param_1 + iVar7 * 0x10;
    puVar9 = puVar9 + 1;
    *puVar9 = 0;
    puVar5 = puVar5 + 1;
    *puVar5 = 0;
    *(undefined4 *)(iVar3 + 0x285af0) = 0;
    *(undefined4 *)(iVar3 + 0x285aec) = 0;
    *(undefined4 *)(iVar3 + 0x285af4) = 0;
    *(undefined4 *)(iVar3 + 0x285b10) = 0;
    *(undefined4 *)(iVar3 + 0x285b0c) = 0;
    *(undefined4 *)(iVar3 + 0x285b14) = 0;
    puVar8 = puVar8 + 1;
    *puVar8 = 0;
    bVar11 = iVar7 != 1;
    puVar2 = puVar2 + 1;
    *puVar2 = 0;
    *(undefined4 *)(iVar3 + 0x285b50) = 0;
    *(undefined4 *)(iVar3 + 0x285b4c) = 0;
    iVar7 = 1;
    *(undefined4 *)(iVar3 + 0x285b54) = 0;
    *(undefined4 *)(iVar3 + 0x285b70) = 0;
    *(undefined4 *)(iVar3 + 0x285b6c) = 0;
    *(undefined4 *)(iVar3 + 0x285b74) = 0;
  } while (bVar11);
  if (*(char *)(iVar1 + 0x15b) == '\0') {
    *(undefined4 *)(param_1 + 0x285bf0) = 0;
    *(undefined4 *)(param_1 + 0x285bf8) = 0;
    *(undefined4 *)(param_1 + 0x285bf4) = 0;
    *(undefined4 *)(param_1 + 0x285bfc) = 0;
    *(undefined4 *)(param_1 + 0x285c08) = 0;
    *(undefined4 *)(param_1 + 0x285c04) = 0;
    *(undefined4 *)(param_1 + 0x285c0c) = 0;
  }
  os_alloc_mem(param_1,&local_30,8);
  if (local_30 == 0) {
    if (-1 < DebugLevel) {
      printk("%s os_alloc_mem fail\n","fp_qm_init");
    }
    os_free_mem(local_34);
  }
  else {
    __memzero(local_30,8);
    *(int *)(param_1 + 0x285b90) = local_30;
    os_alloc_mem(param_1,local_2c,0x10);
    if (local_2c[0] != 0) {
      __memzero(local_2c[0],0x10);
      *(int *)(param_1 + 0x285b94) = local_2c[0];
      OS_SPIN_LOCK_BH(param_1 + 0x285b2c);
      **(undefined4 **)(param_1 + 0x285b90) = 0;
      iVar1 = *(int *)(param_1 + 0x285b94);
      *(int *)iVar1 = iVar1;
      *(int *)(iVar1 + 4) = iVar1;
      OS_SPIN_UNLOCK_BH(param_1 + 0x285b2c);
      OS_SPIN_LOCK_BH(puVar6);
      *(undefined4 *)(*(int *)(param_1 + 0x285b90) + 4) = 0;
      iVar1 = *(int *)(param_1 + 0x285b94);
      *(int *)(iVar1 + 8) = iVar1 + 8;
      *(int *)(iVar1 + 0xc) = iVar1 + 8;
      OS_SPIN_UNLOCK_BH(puVar6);
      *(code **)(iVar10 + 0x24) = fp_enq_dataq_pkt;
      *(code **)(iVar10 + 0x30) = fp_ge_tx_deq_delay;
      fp_tx_flow_ctl(param_1,1);
      return 0;
    }
    if (-1 < DebugLevel) {
      printk("%s os_alloc_mem fail\n","fp_qm_init");
    }
  }
  os_free_mem(local_30);
  return 1;
}

