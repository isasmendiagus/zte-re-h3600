// module: mt7915.ko
// function: RTMPWPARemoveAllKeys @ 0xdbc80
// size: 100 bytes
//

void RTMPWPARemoveAllKeys(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_98 [3];
  undefined2 local_8c;
  
  memset(local_98,0,0x88);
  iVar1 = GetAssociatedAPByWdev(param_1,param_2);
  if (iVar1 != 0) {
    os_zero_mem(local_98,0x88);
    local_8c = *(undefined2 *)(iVar1 + 0xe0);
    local_98[0] = 1;
    HW_ADDREMOVE_KEYTABLE(param_1,local_98);
  }
  return;
}

