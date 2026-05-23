// module: mt7915.ko
// function: mtf_get_wtbl_entry234 @ 0x19ed30
// size: 124 bytes
//

undefined4 mtf_get_wtbl_entry234(int param_1,uint param_2,undefined1 *param_3)

{
  uint uVar1;
  
  uVar1 = (uint)*(ushort *)("Get_System_CapNode_Info" + param_1 + 8);
  if (uVar1 != 0) {
    if (uVar1 <= param_2) {
      param_2 = uVar1 - 1 & 0xffff;
    }
    *param_3 = (char)param_2;
    *(uint *)(param_3 + 0xbc) =
         *(ushort *)("Get_System_CapNode_Info" + param_1 + 0x10) * param_2 +
         *(int *)("Get_System_CenFreq_Info" + param_1);
    return 1;
  }
  if (-1 < DebugLevel) {
    printk("%s():pAd->mac_ctrl not init yet!\n","mtf_get_wtbl_entry234");
    return 0;
  }
  return 0;
}

