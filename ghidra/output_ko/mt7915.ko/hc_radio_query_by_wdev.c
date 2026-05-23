// module: mt7915.ko
// function: hc_radio_query_by_wdev @ 0xaa3e0
// size: 172 bytes
//

undefined4 hc_radio_query_by_wdev(int param_1,int param_2)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0xabc);
  iVar3 = hdev_obj_state_ready(iVar4);
  if (iVar3 != 0) {
    iVar3 = *(int *)(*(int *)(iVar4 + 8) + 4);
    cVar1 = *(char *)(iVar3 + 7);
    *(char *)(param_2 + 3) = cVar1;
    *(undefined1 *)(param_2 + 6) = *(undefined1 *)(iVar3 + 6);
    *(undefined1 *)(param_2 + 7) = *(undefined1 *)(iVar3 + 5);
    *(undefined1 *)(param_2 + 4) = *(undefined1 *)(iVar3 + 8);
    uVar2 = *(undefined1 *)(iVar3 + 4);
    *(bool *)(param_2 + 1) = cVar1 != '\0';
    *(undefined1 *)(param_2 + 5) = uVar2;
    uVar2 = rf_bw_2_vht_bw();
    *(undefined1 *)(param_2 + 2) = uVar2;
    return 0;
  }
  if (-1 < DebugLevel) {
    printk("%s(): wdev=%d, hobj is not ready!\n","hc_radio_query_by_wdev",
           *(undefined1 *)(param_1 + 0xc));
  }
  return 1;
}

