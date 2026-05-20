// module: mt7915.ko
// function: WLAN_ERR_RecoverCheck @ 0x15a8cc
// size: 108 bytes
//

void WLAN_ERR_RecoverCheck(int param_1,int param_2)

{
  uint uVar1;
  
  if (param_1 == 0) {
    *(undefined4 *)((int)&g_arrulWLANErrorCnt + param_2 * 4) = 0;
    return;
  }
  uVar1 = *(int *)((int)&g_arrulWLANErrorCnt + param_2 * 4) + 1;
  *(uint *)((int)&g_arrulWLANErrorCnt + param_2 * 4) = uVar1;
  if (0x77 < uVar1) {
    if (g_bWLANReboot == '\0') {
      return;
    }
    g_bWLANReboot = 0;
                    /* WARNING: Subroutine does not return */
    panic("Wifi Chipset Lost\n");
  }
  return;
}

