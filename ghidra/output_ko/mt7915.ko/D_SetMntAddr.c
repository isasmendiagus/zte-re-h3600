// module: mt7915.ko
// function: D_SetMntAddr @ 0x9af30
// size: 196 bytes
//

undefined4 D_SetMntAddr(undefined4 *param_1,undefined4 *param_2)

{
  int iVar1;
  undefined1 local_58 [12];
  undefined4 local_4c;
  undefined2 local_48;
  
  iVar1 = DebugLevel;
  param_1[0x41a] = *param_2;
  *(undefined2 *)(param_1 + 0x41b) = *(undefined2 *)(param_2 + 1);
  if (0 < iVar1) {
    printk("%s(): %02x:%02x:%02x:%02x:%02x:%02x\n","D_SetMntAddr",*(undefined1 *)(param_1 + 0x41a),
           *(undefined1 *)((int)param_1 + 0x1069),*(undefined1 *)((int)param_1 + 0x106a),
           *(undefined1 *)((int)param_1 + 0x106b),*(undefined1 *)(param_1 + 0x41b),
           *(undefined1 *)((int)param_1 + 0x106d));
  }
  local_4c = param_1[0x41a];
  local_48 = *(undefined2 *)(param_1 + 0x41b);
  local_58[0] = 0x11;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_58,0x40);
  return 1;
}

