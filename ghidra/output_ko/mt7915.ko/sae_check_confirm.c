// module: mt7915.ko
// function: sae_check_confirm @ 0x20a6dc
// size: 272 bytes
//

undefined4 sae_check_confirm(int param_1,void *param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 auStack_30 [32];
  
  if (4 < DebugLevel) {
    printk("==> %s()\n","sae_check_confirm");
  }
  if ((((*(int *)(param_1 + 0x58) != 0) && (*(int *)(param_1 + 0x28) != 0)) &&
      (*(int *)(param_1 + 0x54) != 0)) &&
     ((*(int *)(param_1 + 0x50) != 0 && (*(int *)(param_1 + 0x98) != 0)))) {
    (**(code **)(*(int *)(param_1 + 0x98) + 8))(param_1,0,auStack_30);
    iVar1 = memcmp(param_2,auStack_30,0x20);
    uVar2 = 0;
    if (iVar1 != 0) {
      if (2 < DebugLevel) {
        printk("peer_send_confirm = %d\n",*(undefined2 *)(param_1 + 0x84));
      }
      hex_dump_with_lvl("peer_confirm:",param_2,0x20,SAE_DEBUG_LEVEL2);
      hex_dump_with_lvl("verifier:",auStack_30,0x20,SAE_DEBUG_LEVEL2);
      uVar2 = 1;
    }
    return uVar2;
  }
  return 1;
}

