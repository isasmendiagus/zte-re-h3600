// module: mt7915.ko
// function: MtCmdSetPhyCounter @ 0x1b729c
// size: 120 bytes
//

void MtCmdSetPhyCounter(undefined4 param_1,undefined4 param_2,undefined1 param_3)

{
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_58;
  undefined1 local_57;
  
  os_zero_mem(&local_5c,0x4c);
  if (2 < DebugLevel) {
    printk("%s, Control:%d\n","MtCmdSetPhyCounter",param_2);
  }
  local_58 = (undefined1)param_2;
  local_5c = 1;
  local_5b = 0x11;
  local_57 = param_3;
  MtCmdATETest(param_1,&local_5c);
  return;
}

