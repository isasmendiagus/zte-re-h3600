// module: mt7915.ko
// function: wlan_operate_set_lsig_txop_protect @ 0x107d44
// size: 40 bytes
//

undefined4 wlan_operate_set_lsig_txop_protect(int param_1,char param_2)

{
  int iVar1;
  
  if ((param_1 != 0) && (iVar1 = *(int *)(param_1 + 0xb14), iVar1 != 0)) {
    *(char *)(iVar1 + 0x1c) = param_2;
    *(byte *)(iVar1 + 0x37) = *(byte *)(iVar1 + 0x37) & 0x7f | param_2 << 7;
  }
  return 0;
}

