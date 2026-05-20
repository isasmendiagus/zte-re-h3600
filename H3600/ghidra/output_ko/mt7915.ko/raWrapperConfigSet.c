// module: mt7915.ko
// function: raWrapperConfigSet @ 0x1d9cc8
// size: 340 bytes
//

void raWrapperConfigSet(int param_1,undefined4 param_2,undefined1 *param_3)

{
  undefined2 uVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  *param_3 = *(undefined1 *)(param_1 + 0x286285);
  param_3[1] = (byte)((uint)(*(int *)(param_1 + 0x795124) << 0x1e) >> 0x1f);
  param_3[2] = (byte)((uint)(*(int *)(param_1 + 0x795124) << 0x1b) >> 0x1f);
  uVar2 = wlan_operate_get_tx_stream(param_2);
  param_3[3] = uVar2;
  uVar2 = wlan_operate_get_rx_stream(param_2);
  param_3[4] = uVar2;
  param_3[5] = (char)*(undefined4 *)(param_1 + 0x794ae0);
  param_3[6] = *(undefined1 *)(param_1 + 0xa39fcc);
  param_3[7] = *(undefined1 *)(param_1 + 0xa39fcd);
  param_3[8] = (byte)(((uint)*(byte *)(param_1 + 0x794cce) << 0x1f) >> 0x1f);
  param_3[9] = *(undefined1 *)(param_1 + 0x285945);
  param_3[10] = *(undefined1 *)(param_1 + 0x795949);
  param_3[0xb] = *(undefined1 *)(param_1 + 0x795058);
  param_3[0xf] = *(undefined1 *)(param_1 + 0x795943);
  if ((*(char *)(param_1 + 0x79504d) == '\0') &&
     (("SetPartProfileParameters"[param_1 + 0x18] & 0xf0U) == 0x40)) {
    param_3[0x10] = *(undefined1 *)(param_1 + 0x795944);
  }
  param_3[0xc] = "auth_fsm_reset"[param_1 + 6];
  param_3[0xd] = "auth_fsm_reset"[param_1 + 5];
  param_3[0x11] = *(undefined1 *)(param_1 + 0x795990);
  *(undefined2 *)(param_3 + 0x12) = *(undefined2 *)(param_1 + 0x79598e);
  *(undefined2 *)(param_3 + 0x14) = *(undefined2 *)(param_1 + 0x79598a);
  uVar1 = *(undefined2 *)(param_1 + 0x795988);
  *(undefined2 *)(param_3 + 0x18) = 0;
  *(undefined2 *)(param_3 + 0x16) = uVar1;
  *(undefined4 *)(param_3 + 0x1c) = *(undefined4 *)(iVar3 + 0x2c);
  *(undefined4 *)(param_3 + 0x20) = *(undefined4 *)(param_1 + 0x794b4c);
  *(undefined4 *)(param_3 + 0x24) = *(undefined4 *)(param_1 + 0x794b50);
  return;
}

