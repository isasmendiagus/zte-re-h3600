// module: mt7915.ko
// function: HQA_MUGetInitMCS @ 0x2722a0
// size: 220 bytes
//

undefined4 HQA_MUGetInitMCS(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  uVar3 = (*(uint *)(param_3 + 0xc) & 0xff) << 8 | *(uint *)(param_3 + 0xc) >> 8 & 0xff;
  os_zero_mem(&local_38,0x10);
  os_zero_mem(&local_28,0x10);
  uVar2 = hqa_wifi_test_mu_get_init_mcs(param_1,uVar3,&local_38);
  local_24 = local_34;
  local_28 = local_38;
  local_20 = local_30;
  local_1c = local_2c;
  *(undefined4 *)(param_3 + 0xe) = local_38;
  iVar1 = DebugLevel;
  *(undefined4 *)(param_3 + 0x12) = local_34;
  *(undefined4 *)(param_3 + 0x16) = local_30;
  *(undefined4 *)(param_3 + 0x1a) = local_2c;
  if (0 < iVar1) {
    printk("%s: gid:%u\n","HQA_MUGetInitMCS",uVar3);
  }
  FUN_0026cdd0(param_3,param_2,0x12,uVar2);
  return uVar2;
}

