// module: mt7915.ko
// function: HQA_MUGetQD @ 0x271ed0
// size: 308 bytes
//

undefined4 HQA_MUGetQD(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int iVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  int iVar12;
  undefined4 local_60 [15];
  
  uVar1 = DebugLevel;
  uVar4 = *(uint *)(param_3 + 0xc);
  __memzero(local_60,0x38);
  DebugLevel = 1;
  iVar9 = 0;
  uVar5 = hqa_wifi_test_mu_get_qd(param_1,(int)(char)(uVar4 >> 0x18),local_60);
  iVar12 = DebugLevel;
  do {
    if (2 < iVar12) {
      printk("DWORD%d:%08x\n",iVar9,local_60[iVar9]);
      iVar12 = DebugLevel;
    }
    iVar9 = iVar9 + 1;
  } while (iVar9 != 0xe);
  puVar2 = (undefined4 *)(param_3 + 0xe);
  puVar3 = local_60;
  do {
    puVar11 = puVar3;
    puVar10 = puVar2;
    uVar6 = puVar11[1];
    uVar7 = puVar11[2];
    uVar8 = puVar11[3];
    *puVar10 = *puVar11;
    puVar10[1] = uVar6;
    puVar10[2] = uVar7;
    puVar10[3] = uVar8;
    puVar2 = puVar10 + 4;
    puVar3 = puVar11 + 4;
  } while (puVar11 + 4 != local_60 + 0xc);
  uVar6 = puVar11[5];
  puVar10[4] = puVar11[4];
  puVar10[5] = uVar6;
  if (2 < iVar12) {
    printk("%s: sub:%u, qd.length:%zu, pqd:%p, HqaCmd->Data:%p\n","HQA_MUGetQD",
           uVar4 << 0x18 | (uVar4 >> 8 & 0xff) << 0x10 | (uVar4 >> 0x10 & 0xff) << 8 | uVar4 >> 0x18
           ,0x38,local_60,(uint *)(param_3 + 0xc));
  }
  FUN_0026cdd0(param_3,param_2,0x3a,uVar5);
  DebugLevel = uVar1;
  return uVar5;
}

