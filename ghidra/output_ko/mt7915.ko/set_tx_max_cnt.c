// module: mt7915.ko
// function: set_tx_max_cnt @ 0xc3cf4
// size: 132 bytes
//

undefined4 set_tx_max_cnt(int param_1,char *param_2)

{
  int iVar1;
  undefined2 *puVar2;
  undefined4 local_c;
  
  puVar2 = *(undefined2 **)(param_1 + 0x285ae8);
  local_c = 0x400;
  if (((param_2 == (char *)0x0) || (*param_2 == '\0')) ||
     (iVar1 = sscanf(param_2,"%u",&local_c), iVar1 != 1)) {
    if (0 < DebugLevel) {
      printk("invalid input, should be tx_max_cnt\n");
    }
  }
  else {
    *puVar2 = (short)local_c;
  }
  return 1;
}

