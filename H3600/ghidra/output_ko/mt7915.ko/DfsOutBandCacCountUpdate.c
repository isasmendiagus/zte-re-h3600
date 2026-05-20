// module: mt7915.ko
// function: DfsOutBandCacCountUpdate @ 0x2348b0
// size: 292 bytes
//

void DfsOutBandCacCountUpdate(int param_1)

{
  ushort uVar1;
  int iVar2;
  ushort *puVar3;
  
  if (*(int *)(param_1 + 0xa79184) != 2) {
    return;
  }
  if (*(char *)(param_1 + 0x7953fa) != '\0') {
    if ((*(char *)(param_1 + 0x795402) == '\0') && (*(char *)(param_1 + 0x7953ee) != '\x01')) {
      if (*(char *)(param_1 + 0x7953e6) == '\x01') {
        if (2 < DebugLevel) {
          printk("%s() radar is detected by dedicated RX.\n","DfsOutBandCacCountUpdate");
          return;
        }
      }
      else {
        puVar3 = (ushort *)(param_1 + 0x795400);
        uVar1 = *puVar3;
        *puVar3 = uVar1 + 1;
        iVar2 = DebugLevel;
        if (*(ushort *)(param_1 + 0x795406) < uVar1) {
          *(undefined1 *)(param_1 + 0x795402) = 1;
          *puVar3 = 0;
          if (0 < iVar2) {
            printk("%s() OutBand(SynB) CAC complete and is available now.\n",
                   "DfsOutBandCacCountUpdate");
          }
          if (*(char *)(param_1 + 0x795404) == '\x01') {
            MlmeEnqueue(param_1,0x2c,2,0,0,0);
            RtmpOsMlmeUp(param_1 + 0x286298);
            return;
          }
        }
      }
    }
  }
  return;
}

