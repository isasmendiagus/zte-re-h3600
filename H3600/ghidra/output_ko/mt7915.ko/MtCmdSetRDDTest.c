// module: mt7915.ko
// function: MtCmdSetRDDTest @ 0x1aef8c
// size: 132 bytes
//

void MtCmdSetRDDTest(undefined4 param_1,undefined4 param_2)

{
  undefined1 auStack_b8 [72];
  undefined4 local_70;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 uStack_5c;
  undefined1 auStack_58 [72];
  
  os_zero_mem(&local_64,0x54);
  if (2 < DebugLevel) {
    printk("%s, IsStart:%d\n","MtCmdSetRDDTest",param_2);
  }
  local_64 = 10;
  local_70 = 8;
  local_60 = param_2;
  memcpy(auStack_b8,auStack_58,0x48);
  FUN_001ac150(param_1,local_64,local_60,uStack_5c);
  return;
}

