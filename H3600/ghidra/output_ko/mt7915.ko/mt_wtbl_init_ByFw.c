// module: mt7915.ko
// function: mt_wtbl_init_ByFw @ 0x19edb0
// size: 64 bytes
//

undefined4 mt_wtbl_init_ByFw(int param_1)

{
  char *pcVar1;
  undefined2 uVar2;
  
  pcVar1 = "Get_System_CenFreq_Info" + param_1;
  pcVar1[0] = '\0';
  pcVar1[1] = -0x80;
  pcVar1[2] = '\x03';
  pcVar1[3] = '\0';
  ("Get_System_CapNode_Info" + param_1 + 0x10)[0] = '\0';
  ("Get_System_CapNode_Info" + param_1 + 0x10)[1] = '\x01';
  uVar2 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
  *(undefined2 *)("Get_System_CapNode_Info" + param_1 + 8) = uVar2;
  return 1;
}

