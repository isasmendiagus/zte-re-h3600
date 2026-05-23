// module: mt7915.ko
// function: ChipOpsMCUHook @ 0x1a3fc8
// size: 124 bytes
//

void ChipOpsMCUHook(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = hc_get_chip_ops(*(undefined4 *)(param_1 + 0xa797a0));
  if ((param_2 & 4) == 0) {
    return;
  }
  *(code **)(iVar1 + 0xb0) = hif_mcu_fw_init;
  *(code **)(iVar1 + 0xb4) = hif_mcu_fw_exit;
  *(code **)(iVar1 + 200) = hif_kick_out_cmd_msg;
  *(code **)(iVar1 + 0xe0) = AndesSendCmdMsg;
  *(code **)(iVar1 + 0xa8) = AndesCtrlInit;
  *(code **)(iVar1 + 0xac) = AndesCtrlExit;
  FwdlHookInit(param_1);
  return;
}

