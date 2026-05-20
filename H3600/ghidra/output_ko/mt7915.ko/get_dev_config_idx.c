// module: mt7915.ko
// function: get_dev_config_idx @ 0x14eeb4
// size: 24 bytes
//

undefined4 get_dev_config_idx(int param_1)

{
  char *pcVar1;
  
  pcVar1 = "Get_System_CapNode_Info" + param_1 + 4;
  pcVar1[0] = '\0';
  pcVar1[1] = '\0';
  pcVar1[2] = '\0';
  pcVar1[3] = '\0';
  return 0;
}

