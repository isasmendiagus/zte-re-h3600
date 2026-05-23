// module: mt7915.ko
// function: D_SetAgeTime @ 0x9b17c
// size: 128 bytes
//

undefined4 D_SetAgeTime(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined1 local_50 [20];
  undefined4 local_3c;
  
  iVar1 = DebugLevel;
  param_1[0x40a] = param_2;
  if (0 < iVar1) {
    printk("%s(): AgeTime = %u\n","D_SetAgeTime",param_2);
    param_2 = param_1[0x40a];
  }
  local_50[0] = 0xe;
  local_3c = param_2;
  RtmpOSWrielessEventSend(*param_1,1,0x950,0,local_50,0x40);
  return 1;
}

