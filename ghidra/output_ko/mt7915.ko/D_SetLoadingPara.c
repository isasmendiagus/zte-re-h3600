// module: mt7915.ko
// function: D_SetLoadingPara @ 0x9b6ac
// size: 240 bytes
//

undefined4 D_SetLoadingPara(undefined4 param_1,undefined4 *param_2,undefined4 param_3,uint param_4)

{
  undefined1 local_58 [44];
  undefined4 local_2c;
  undefined1 local_23;
  
  if (0 < DebugLevel) {
    printk("D_SetLoadingPara:type=%d,LoadingPara=%d\n",param_4);
  }
  if (param_4 < 5) {
    if (param_4 == 0) {
      *(char *)(param_2 + 0x41e) = (char)param_3;
    }
    else if (((param_4 == 4) && (0 < DebugLevel)) &&
            (printk("========Bndstrg Driver Loading info:\n"), 0 < DebugLevel)) {
      printk("Method=%d\n",*(undefined1 *)(param_2 + 0x41e));
    }
    local_23 = (undefined1)param_4;
    if (*(char *)((int)param_2 + 0x106e) == '\x01') {
      local_58[0] = 0x18;
    }
    else {
      local_58[0] = 0x17;
    }
    local_2c = param_3;
    RtmpOSWrielessEventSend(*param_2,1,0x950,0,local_58,0x40);
  }
  return 1;
}

