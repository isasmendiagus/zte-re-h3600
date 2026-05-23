// module: mt7915.ko
// function: wmm_ctrl_set_edca @ 0xad684
// size: 96 bytes
//

void wmm_ctrl_set_edca(byte *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 8);
  iVar2 = *(int *)(iVar3 + 0x18);
  iVar1 = *(int *)(iVar2 + 0x4328);
  if (param_1[6] == 0) {
    return;
  }
  AsicSetEdcaParm(iVar1,*(int *)(iVar2 + 0x1a0c) + (uint)param_1[5] * 0x28,
                  *(undefined4 *)(iVar1 + (uint)*param_1 * 4 + 0xc));
  RcUpdateWmmEntry(iVar3,param_1,param_1[5],param_4);
  return;
}

