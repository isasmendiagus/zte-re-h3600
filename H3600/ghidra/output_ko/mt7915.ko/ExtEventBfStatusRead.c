// module: mt7915.ko
// function: ExtEventBfStatusRead @ 0x1a72c4
// size: 412 bytes
//

void ExtEventBfStatusRead(int param_1,undefined1 *param_2,undefined4 param_3)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if (((*(uint *)(param_1 + 0xa3ac14) & 1) != 0) ||
     ((*(int *)(param_1 + 0xa77bb4) == 1 &&
      ((*(uint *)(*(int *)(param_1 + 0xa77bb8) + 0x4e0) & 1) != 0)))) {
    TxBf_Status_Update(param_1,param_2,param_3);
  }
  switch(*param_2) {
  case 0x10:
    if (*(code **)(iVar1 + 0x150) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001a73e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(iVar1 + 0x150))(param_1,param_2[4],param_2 + 8);
      return;
    }
    break;
  case 0x11:
    if (*(code **)(iVar1 + 0x164) != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x001a7404. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      (**(code **)(iVar1 + 0x164))(param_1,*(undefined2 *)(param_2 + 2),param_2 + 8);
      return;
    }
    break;
  case 0x12:
    TxBfProfilePnPrint(param_2[1],param_2 + 8);
    return;
  case 0x13:
    TxBfProfileMemAllocMap(param_2 + 8);
    return;
  case 0x14:
    StaRecBfRead(param_1,param_2 + 8);
    return;
  case 0x15:
    (**(code **)(iVar1 + 0x148))
              (param_1,param_2[1],param_2[2],param_2[3],param_2[4],param_2[5],param_2 + 8);
    break;
  case 0x17:
    TxBfFbRptDbgInfoPrint(param_1,param_2 + 8);
    return;
  case 0x18:
    TxBfTxSndInfoPrint(param_1,param_2 + 8);
    return;
  case 0x19:
    TxBfPlyInfoPrint(param_1,param_2 + 8);
    return;
  case 0x1a:
    HeRaMuMetricInfoPrint(param_1,param_2 + 8);
    return;
  case 0x1b:
    TxBfTxCmdCfgInfoPrint(param_1,param_2 + 8);
    return;
  }
  return;
}

