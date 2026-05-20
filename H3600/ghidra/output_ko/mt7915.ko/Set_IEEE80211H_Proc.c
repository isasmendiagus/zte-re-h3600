// module: mt7915.ko
// function: Set_IEEE80211H_Proc @ 0xda120
// size: 116 bytes
//

undefined4 Set_IEEE80211H_Proc(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar2 = os_str_tol(param_2,0,10);
  iVar1 = DebugLevel;
  if ((iVar2 != 1) && (iVar2 != 0)) {
    return 0;
  }
  *(char *)(param_1 + 0x795074) = (char)iVar2;
  if (iVar1 < 3) {
    return 1;
  }
  printk("Set_IEEE80211H_Proc::(IEEE80211H=%d)\n",*(undefined1 *)(param_1 + 0x795074));
  return 1;
}

