// module: mt7915.ko
// function: net_ad_tx_v2 @ 0x25a9f8
// size: 452 bytes
//

undefined4 net_ad_tx_v2(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  byte local_29 [5];
  
  local_29[0] = 0;
  iVar1 = hc_get_arch_ops(*(undefined4 *)(param_1 + 0xa797a0));
  iVar8 = *(int *)(param_1 + 0xa77bb8);
  iVar2 = HcGetBandByWdev(param_2);
  iVar7 = iVar2 * 0xd18;
  iVar3 = mt_engine_search_stack
                    (iVar8 + iVar7 + 0x4e0,*(undefined1 *)(*(int *)(param_3 + 0xc) + 0x42),local_29,
                     param_3 + 0x14);
  if (iVar3 == 0) {
    iVar3 = local_29[0] + 10;
    if (*(char *)(iVar8 + iVar7 + iVar3 * 0x20 + 0x6f8) == '\0') {
      uVar5 = 0x18;
      *(undefined1 *)(param_3 + 0x2c) = 0x18;
    }
    else {
      iVar7 = iVar8 + iVar7 + (uint)local_29[0] * 0x20;
      *(char *)(param_3 + 0x2c) = (char)*(undefined4 *)(iVar7 + 0x830);
      uVar5 = (undefined1)*(undefined4 *)(iVar7 + 0x830);
    }
    *(undefined1 *)(param_3 + 0x35) = uVar5;
    bVar9 = *(char *)(iVar8 + iVar2 * 0xd18 + iVar3 * 0x20 + 0x6fa) != '\0';
    if (bVar9) {
      uVar6 = *(uint *)(param_3 + 0x18) & 0xfff7ffff | 0x80000002;
    }
    else {
      uVar6 = *(uint *)(param_3 + 0x18) & 0xfffffffd | 0x80000;
    }
    *(uint *)(param_3 + 0x18) = uVar6;
    iVar3 = iVar2 * 0xd18 + iVar8;
    if (bVar9) {
      *(undefined1 *)(param_3 + 0x34) = 2;
    }
    else {
      *(undefined1 *)(param_3 + 0x34) = 0;
    }
    if ((*(byte *)(iVar3 + 0x1135) - 0xb < 2) && (*(char *)(iVar3 + 0x1104) != '\0')) {
      FUN_0025a924(param_1,param_2,param_3,1);
    }
    else {
      FUN_0025a924(param_1,param_2,param_3,0);
    }
    *(char *)(param_3 + 1) = (char)*(undefined2 *)(iVar2 * 0xd18 + iVar8 + 0x50e);
    if (*(int *)(param_3 + 0x14) != 0) {
      *(undefined4 *)(param_3 + 0x78) = *(undefined4 *)(*(int *)(param_3 + 0x14) + 0xf4);
    }
    if (*(char *)(iVar2 * 0xd18 + iVar8 + 0x1114) != '\0') {
      *(uint *)(param_3 + 0x18) = *(uint *)(param_3 + 0x18) | 0x40000000;
    }
    uVar4 = (**(code **)(iVar1 + 0x168))(param_1,param_3);
  }
  else {
    printk("%s: wcid:%d is in-valid in stack!\n","net_ad_tx_v2",
           *(undefined2 *)(*(int *)(param_3 + 0xc) + 0x42));
    uVar4 = 0x600;
  }
  return uVar4;
}

