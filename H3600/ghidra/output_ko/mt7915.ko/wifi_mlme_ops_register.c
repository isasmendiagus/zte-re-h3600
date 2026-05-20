// module: mt7915.ko
// function: wifi_mlme_ops_register @ 0x105798
// size: 68 bytes
//

void wifi_mlme_ops_register(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x14);
  if (uVar1 != 2) {
    if (uVar1 < 3) {
      if (uVar1 == 1) {
        ap_fsm_ops_hook();
        return;
      }
      return;
    }
    if (uVar1 != 4) {
      if (uVar1 == 0x100) {
        sta_fsm_ops_hook();
        return;
      }
      return;
    }
  }
  sta_fsm_ops_hook(param_1);
  return;
}

