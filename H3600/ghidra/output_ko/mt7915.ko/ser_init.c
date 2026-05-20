// module: mt7915.ko
// function: ser_init @ 0xb22f8
// size: 180 bytes
//

undefined4 ser_init(int param_1)

{
  int iVar1;
  
  iVar1 = param_1 + 0x285cfc;
  *(undefined4 *)(param_1 + 0x285d34) = 0;
  *(undefined4 *)(param_1 + 0x285d2c) = 1;
  RtmpOSTaskInit(iVar1,"ser_task",param_1,param_1 + 0xa78454,param_1 + 0xa78478);
  iVar1 = RtmpOSTaskAttach(iVar1,ser_ctrl_task,iVar1);
  if ((iVar1 == 1) && (-1 < DebugLevel)) {
    printk("%s: unable to start %s\n",*(undefined4 *)(param_1 + 4),"ser_init");
  }
  return 1;
}

