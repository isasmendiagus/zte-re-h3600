// module: mt7915.ko
// function: DfsDedicatedOutBandRDDStart @ 0x235d80
// size: 212 bytes
//

void DfsDedicatedOutBandRDDStart(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x7953e6) = 0;
  uVar1 = *(undefined1 *)(param_1 + 0x795075);
  iVar2 = RadarChannelCheck(param_1,*(undefined1 *)(param_1 + 0x7953fb));
  *(char *)(param_1 + 0x7953e3) = (char)iVar2;
  if (iVar2 != 0) {
    mtRddControl(param_1,1,2,0,uVar1);
    *(undefined2 *)(param_1 + 0x795400) = 0;
    *(undefined1 *)(param_1 + 0x795402) = 0;
    if ((*(char *)(param_1 + 0x795075) == '\0') &&
       (iVar2 = DfsCacRestrictBand(param_1,*(undefined1 *)(param_1 + 0x7953fc),
                                   *(undefined1 *)(param_1 + 0x7953fb)), iVar2 != 0)) {
      *(undefined2 *)(param_1 + 0x795406) = 0x25d;
    }
    else {
      *(undefined2 *)(param_1 + 0x795406) = 0x41;
    }
    if (0 < DebugLevel) {
      printk("[%s]: Dedicated CAC time: %d\n","DfsDedicatedOutBandRDDStart",
             *(undefined2 *)(param_1 + 0x795406));
      return;
    }
  }
  return;
}

