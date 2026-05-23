// module: mt7915.ko
// function: wlan_operate_get_he_intra_bss_info @ 0x206174
// size: 96 bytes
//

byte wlan_operate_get_he_intra_bss_info(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xb14);
  if (3 < DebugLevel) {
    printk("%s: color = %d, disabled = %d\n","wlan_operate_get_he_intra_bss_info",
           *(undefined1 *)(iVar1 + 0x5c),*(undefined1 *)(iVar1 + 0x5e));
  }
  return *(char *)(iVar1 + 0x5d) << 6 | *(char *)(iVar1 + 0x5e) << 7 |
         *(byte *)(iVar1 + 0x5c) & 0x3f;
}

