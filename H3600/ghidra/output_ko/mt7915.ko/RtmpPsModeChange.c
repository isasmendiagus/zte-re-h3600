// module: mt7915.ko
// function: RtmpPsModeChange @ 0x1dd798
// size: 500 bytes
//

void RtmpPsModeChange(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = GetAssociatedAPByWdev(param_1,&DAT_0036db58 + param_1);
  if (s__RB_FULL__Free_Queue_List___00371ba4[param_1 + 0x14] == '\x01') {
    if (param_2 == 1) {
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) | 0x20;
      *(undefined4 *)(&DAT_00580008 + param_1) = 1;
      if ((&DAT_0058000c)[param_1] == '\0') {
        *(undefined4 *)(&DAT_00580004 + param_1) = 1;
      }
      *(undefined2 *)(&DAT_0057fffe + param_1) = 5;
    }
    else if (param_2 == 2) {
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) | 0x20;
      *(undefined4 *)(&DAT_00580008 + param_1) = 2;
      if ((&DAT_0058000c)[param_1] == '\0') {
        *(undefined4 *)(&DAT_00580004 + param_1) = 2;
      }
      *(undefined2 *)(&DAT_0057fffe + param_1) = 3;
    }
    else if (param_2 == 3) {
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) | 0x20;
      *(undefined4 *)(&DAT_00580008 + param_1) = 3;
      if ((&DAT_0058000c)[param_1] == '\0') {
        *(undefined4 *)(&DAT_00580004 + param_1) = 3;
      }
      *(undefined2 *)(&DAT_0057fffe + param_1) = 3;
    }
    else {
      if (2 < DebugLevel) {
        printk("%s(line=%d): -->\n","RtmpPsModeChange",0x114);
      }
      MlmeSetPsmBit(param_1,&DAT_0036db58 + param_1,0);
      *(uint *)(param_1 + 0x795124) = *(uint *)(param_1 + 0x795124) | 0x20;
      if ((&DAT_0058000c)[param_1] == '\0') {
        *(undefined4 *)(&DAT_00580004 + param_1) = 0;
      }
      *(undefined4 *)(&DAT_00580008 + param_1) = 0;
    }
    if (iVar1 != 0) {
      RTMPSendNullFrame(param_1,iVar1,*(undefined1 *)(param_1 + 0x794cd0),1,0);
    }
    if (2 < DebugLevel) {
      printk("PSMode=%ld\n",*(undefined4 *)(&DAT_00580004 + param_1));
      return;
    }
  }
  return;
}

