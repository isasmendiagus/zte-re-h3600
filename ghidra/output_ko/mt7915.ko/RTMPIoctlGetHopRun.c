// module: mt7915.ko
// function: RTMPIoctlGetHopRun @ 0x162168
// size: 120 bytes
//

void RTMPIoctlGetHopRun(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 extraout_r2;
  uint uVar3;
  uint uVar4;
  undefined4 uStack_8;
  
  uVar2 = 4;
  uVar4 = *(uint *)(param_2 + 0x10);
  uVar3 = *(uint *)(((uint)&uStack_8 & 0xffffe000) + 8);
  *(undefined2 *)(param_2 + 0x14) = 4;
  if (uVar4 < 0xfffffffc && uVar4 + 4 <= uVar3) {
    uVar3 = 0;
  }
  uStack_8 = param_4;
  if ((uVar3 == 0) &&
     (iVar1 = __copy_to_user(uVar4,param_1 + 0xa7cc00), uVar2 = extraout_r2, iVar1 == 0)) {
    return;
  }
  if (DebugLevel < 0) {
    return;
  }
  printk("[%s]: copy_to_user() fail\n","RTMPIoctlGetHopRun",uVar2,uStack_8);
  return;
}

