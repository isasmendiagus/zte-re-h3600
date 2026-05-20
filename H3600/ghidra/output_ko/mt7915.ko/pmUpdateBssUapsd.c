// module: mt7915.ko
// function: pmUpdateBssUapsd @ 0x1c2760
// size: 148 bytes
//

void pmUpdateBssUapsd(undefined4 param_1,int param_2,undefined4 param_3)

{
  undefined1 uVar1;
  undefined2 local_14;
  undefined2 local_12;
  undefined4 local_10;
  undefined4 local_c;
  
  uVar1 = *(undefined1 *)(param_2 + 0x67);
  local_10 = (uint)CONCAT12(uVar1,*(undefined2 *)(param_2 + 0x66));
  local_14 = 4;
  local_12 = 0xc;
  local_c = 0xffff;
  if (2 < DebugLevel) {
    printk("%s, ucIsUapsdSupported = %d, ucUapsdTriggerAC = 0x%x,ucUapsdTriggerAC = 0x%x, u2UapsdServicePeriodTO = 0x%x\n"
           ,"pmUpdateBssUapsd",*(undefined1 *)(param_2 + 0x66),uVar1,uVar1,0xffff);
  }
  AndesAppendCmdMsg(param_3,&local_14,0xc);
  return;
}

