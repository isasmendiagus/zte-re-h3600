// module: mt7915.ko
// function: sae_parse_confirm @ 0x20a7f0
// size: 252 bytes
//

undefined4 sae_parse_confirm(int *param_1,int param_2,int param_3)

{
  ushort uVar1;
  undefined4 uVar2;
  bool bVar3;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_parse_confirm");
  }
  if (1 < (param_2 + param_3) - (param_2 + 0x1e)) {
    uVar1 = *(ushort *)(param_2 + 0x1e);
    if (*param_1 == 3) {
      bVar3 = 0xfffe < uVar1;
      if (uVar1 != 0xffff) {
        bVar3 = uVar1 <= *(ushort *)((int)param_1 + 6);
      }
      if ((bVar3) && (1 < DebugLevel)) {
        printk("confirm fail: SAE_SILENTLY_DISCARDED due to  peer_send_confirm =%d, ast_peer_sc = %d\n"
               ,uVar1);
      }
    }
    *(ushort *)(param_1 + 0x21) = uVar1;
    if (0x1f < (param_2 + param_3) - (param_2 + 0x20)) {
      local_38 = *(undefined4 *)(param_2 + 0x20);
      uStack_34 = *(undefined4 *)(param_2 + 0x24);
      uStack_30 = *(undefined4 *)(param_2 + 0x28);
      uStack_2c = *(undefined4 *)(param_2 + 0x2c);
      local_28 = *(undefined4 *)(param_2 + 0x30);
      uStack_24 = *(undefined4 *)(param_2 + 0x34);
      uStack_20 = *(undefined4 *)(param_2 + 0x38);
      uStack_1c = *(undefined4 *)(param_2 + 0x3c);
      uVar2 = sae_check_confirm(param_1,&local_38);
      return uVar2;
    }
  }
  return 1;
}

