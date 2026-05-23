// module: mt7915.ko
// function: fwdl_datapath_setup @ 0x177a9c
// size: 272 bytes
//

void fwdl_datapath_setup(int param_1,int param_2)

{
  int iVar1;
  byte *pbVar2;
  int *piVar3;
  undefined4 *puVar4;
  uint uVar5;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  uVar5 = *(uint *)(param_1 + 0x286280) & 0xfffffffb;
  if (param_2 == 1) {
    if (uVar5 == 1) {
      pbVar2 = (byte *)hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
      if (*pbVar2 != 0) {
        puVar4 = *(undefined4 **)(pbVar2 + 8);
        piVar3 = (int *)*puVar4;
        if (*piVar3 != 2) {
          uVar5 = 0;
          do {
            uVar5 = uVar5 + 1;
            if (uVar5 == *pbVar2) goto LAB_00177af4;
            puVar4 = puVar4 + 1;
            piVar3 = (int *)*puVar4;
          } while (*piVar3 != 2);
        }
        *(int **)(pbVar2 + 0x88) = piVar3;
      }
    }
LAB_00177af4:
    *(code **)(iVar1 + 200) = mt7915_kick_out_fwdl_msg;
    return;
  }
  if (uVar5 == 1) {
    pbVar2 = (byte *)hc_get_hif_ctrl(*(undefined4 *)(param_1 + 0xa797a0));
    if (*pbVar2 != 0) {
      puVar4 = *(undefined4 **)(pbVar2 + 8);
      piVar3 = (int *)*puVar4;
      if (*piVar3 != 1) {
        uVar5 = 0;
        do {
          uVar5 = uVar5 + 1;
          if (uVar5 == *pbVar2) goto LAB_00177adc;
          puVar4 = puVar4 + 1;
          piVar3 = (int *)*puVar4;
        } while (*piVar3 != 1);
      }
      *(int **)(pbVar2 + 0x88) = piVar3;
    }
  }
LAB_00177adc:
  *(code **)(iVar1 + 200) = hif_kick_out_cmd_msg;
  return;
}

