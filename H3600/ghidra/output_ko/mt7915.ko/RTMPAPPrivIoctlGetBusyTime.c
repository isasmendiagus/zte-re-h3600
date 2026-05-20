// module: mt7915.ko
// function: RTMPAPPrivIoctlGetBusyTime @ 0x15a3a4
// size: 280 bytes
//

undefined4 RTMPAPPrivIoctlGetBusyTime(int *param_1,int param_2)

{
  longlong lVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  undefined1 auStack_18 [4];
  uint local_14 [2];
  
  local_14[0] = 0;
  if (((*(int *)(*param_1 + 0x38) - 0x100U & 0xfffffeff) == 0) &&
     (uVar5 = *(uint *)(*param_1 + 0x3c) & 0xff, uVar5 < *(byte *)((int)param_1 + 0x2b7242))) {
    sVar2 = HcGetBandByWdev(param_1 + uVar5 * 0x160d + 0xadc92);
    lVar1 = (ulonglong)
            (uint)(param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar2)] +
                   param_1[(int)(&UNK_0029f0c6 + sVar2)] +
                  param_1[(int)("cmd_txbf_en_dynsnd_intr" + sVar2 + 2)]) * 0xd1b71759;
    uVar5 = (uint)((int)((ulonglong)lVar1 >> 0x20) << 0xb) >> 0x18;
    if (100 < uVar5) {
      uVar5 = 99;
    }
    if (2 < DebugLevel) {
      printk("Current channel busy_percent = %d\n",uVar5,(int)lVar1);
    }
    uVar4 = *(uint *)(param_2 + 0x10);
    *(undefined2 *)(param_2 + 0x14) = 4;
    uVar6 = *(uint *)(((uint)auStack_18 & 0xffffe000) + 8);
    if (uVar4 < 0xfffffffc && uVar4 + 4 <= uVar6) {
      uVar6 = 0;
    }
    if (uVar6 == 0) {
      local_14[0] = uVar5;
      uVar3 = __copy_to_user(uVar4,local_14);
    }
    else {
      uVar3 = 4;
    }
  }
  else {
    uVar3 = 0xfffffff2;
  }
  return uVar3;
}

