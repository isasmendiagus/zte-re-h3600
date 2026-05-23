// module: mt7915.ko
// function: a4_ap_peer_disable @ 0x9fabc
// size: 236 bytes
//

undefined4 a4_ap_peer_disable(int param_1,int *param_2,uint param_3)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  bool bVar4;
  
  if ((param_2 != (int *)0x0) && (*param_2 == 0x20001)) {
    uVar3 = (uint)*(byte *)(param_2 + 0x39);
    uVar1 = hc_get_chip_bcn_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    bVar4 = 0x1e < uVar3;
    if (uVar3 < 0x20) {
      bVar4 = uVar1 <= uVar3;
    }
    if (bVar4) {
      uVar2 = 0;
    }
    else {
      if (*(byte *)(param_2 + 0x3a) == param_3) {
        *(undefined1 *)(param_2 + 0x3a) = 0;
        a4_delete_entry(param_1,uVar3,(short)param_2[0x38]);
        RoutingTabSetAllFree(param_1,uVar3,(short)param_2[0x38],1);
        if (1 < DebugLevel) {
          printk("a4_ap_peer_disable: Disable A4 for entry : %02x:%02x:%02x:%02x:%02x:%02x\n",
                 (char)param_2[0x3b],*(undefined1 *)((int)param_2 + 0xed),
                 *(undefined1 *)((int)param_2 + 0xee),*(undefined1 *)((int)param_2 + 0xef),
                 (char)param_2[0x3c],*(undefined1 *)((int)param_2 + 0xf1));
        }
      }
      uVar2 = 1;
    }
    return uVar2;
  }
  return 0;
}

