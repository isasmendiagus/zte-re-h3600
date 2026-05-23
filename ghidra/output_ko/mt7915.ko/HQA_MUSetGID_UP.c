// module: mt7915.ko
// function: HQA_MUSetGID_UP @ 0x271d64
// size: 228 bytes
//

undefined4 HQA_MUSetGID_UP(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  uint *puVar5;
  uint *puVar7;
  uint local_30 [6];
  uint *puVar6;
  
  os_zero_mem(local_30,0x18);
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar2 = *(uint *)(param_3 + 0x10);
  local_30[0] = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
                uVar1 >> 0x18;
  puVar7 = local_30 + 1;
  local_30[1] = uVar2 << 0x18 | (uVar2 >> 8 & 0xff) << 0x10 | (uVar2 >> 0x10 & 0xff) << 8 |
                uVar2 >> 0x18;
  puVar5 = (uint *)(param_3 + 0x14);
  do {
    puVar6 = puVar5 + 1;
    uVar1 = *puVar5;
    puVar7 = puVar7 + 1;
    *puVar7 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 |
              uVar1 >> 0x18;
    puVar5 = puVar6;
  } while (puVar6 != (uint *)(param_3 + 0x24));
  iVar4 = 0;
  do {
    if (0 < DebugLevel) {
      printk("DWORD%d:%08x\n",iVar4,local_30[iVar4]);
    }
    iVar4 = iVar4 + 1;
  } while (iVar4 != 6);
  uVar3 = hqa_wifi_test_mu_set_sta_gid_and_up(param_1,local_30);
  FUN_0026cdd0(param_3,param_2,2,uVar3);
  return uVar3;
}

