// module: mt7915.ko
// function: sae_cn_confirm_ecc @ 0x20bf88
// size: 276 bytes
//

void sae_cn_confirm_ecc(int param_1,int param_2,undefined4 param_3)

{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined1 *puVar4;
  undefined1 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int local_124;
  undefined1 auStack_120 [132];
  undefined1 auStack_9c [132];
  
  puVar7 = *(undefined4 **)(param_1 + 0x54);
  puVar6 = *(undefined4 **)(param_1 + 0x58);
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_cn_confirm_ecc");
  }
  local_124 = *(int *)(param_1 + 100);
  Bignum_BI2Bin_with_pad(*puVar7,auStack_120,&local_124);
  local_124 = *(int *)(param_1 + 100);
  Bignum_BI2Bin_with_pad(puVar7[1],auStack_120 + local_124,&local_124,local_124);
  local_124 = *(int *)(param_1 + 100);
  Bignum_BI2Bin_with_pad(*puVar6,auStack_9c,&local_124);
  local_124 = *(int *)(param_1 + 100);
  Bignum_BI2Bin_with_pad(puVar6[1],auStack_9c + local_124,&local_124,local_124);
  if (param_2 == 0) {
    uVar2 = *(undefined4 *)(param_1 + 0x28);
    uVar3 = *(undefined4 *)(param_1 + 0x50);
    puVar4 = auStack_9c;
    uVar1 = *(undefined2 *)(param_1 + 0x84);
    puVar5 = auStack_120;
  }
  else {
    uVar2 = *(undefined4 *)(param_1 + 0x50);
    uVar3 = *(undefined4 *)(param_1 + 0x28);
    puVar4 = auStack_120;
    uVar1 = *(undefined2 *)(param_1 + 4);
    puVar5 = auStack_9c;
  }
  sae_cn_confirm_cmm(param_1,uVar2,uVar3,puVar4,puVar5,*(int *)(param_1 + 100) << 1,uVar1,param_3);
  return;
}

