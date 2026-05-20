// module: mt7915.ko
// function: RTMP_SET_TX_BURST @ 0xb1818
// size: 196 bytes
//

void RTMP_SET_TX_BURST(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_48 [6];
  undefined2 local_2e;
  
  iVar1 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  os_zero_mem(local_48,0x28);
  if (*(char *)(param_1 + 0x79507d) == '\0') {
    uVar2 = 0x60;
  }
  else {
    uVar2 = 0x80;
  }
  *(undefined4 *)(iVar1 + 0x80) = uVar2;
  if (param_3 == 0) {
    local_2e = 0;
  }
  else {
    local_2e = *(undefined2 *)(iVar1 + 0x80);
  }
  local_48[0] = param_2;
  if (2 < DebugLevel) {
    printk("%pS, %s: enable=%x, txop=%x\n");
  }
  FUN_000b0a74(param_1,0,0x12,0x28,local_48);
  return;
}

