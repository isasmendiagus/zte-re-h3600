// module: mt7915.ko
// function: QBSS_LoadElementAppend @ 0x26de4
// size: 136 bytes
//

undefined4 QBSS_LoadElementAppend(int param_1,undefined4 param_2,char *param_3,int param_4)

{
  undefined4 local_14;
  undefined1 local_f;
  undefined1 local_e;
  ushort local_d;
  char local_b;
  undefined1 local_a;
  undefined1 local_9;
  
  if (*param_3 == '\0') {
    return 0;
  }
  local_b = param_3[9];
  local_d = (ushort)(byte)"pStaCfg->WpaPassPhrase"[param_4 * 0x5834 + param_1 + 0xb];
  local_f = 0xb;
  local_e = 5;
  local_a = 0x12;
  local_9 = 0x7a;
  MakeOutgoingFrame(param_2,&local_14,7,&local_f,0xffffffff);
  return local_14;
}

