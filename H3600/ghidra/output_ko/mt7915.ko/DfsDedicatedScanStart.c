// module: mt7915.ko
// function: DfsDedicatedScanStart @ 0x2362d0
// size: 336 bytes
//

void DfsDedicatedScanStart(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  undefined1 uVar5;
  uint uVar6;
  
  if (0 < DebugLevel) {
    printk("[%s]\n","DfsDedicatedScanStart");
  }
  if ((*(char *)(param_1 + 0x7953fa) != '\x01') || (*(char *)(param_1 + 0x795404) != '\x01')) {
    return;
  }
  iVar1 = DfsBwChQueryByDefault(param_1,2,param_1 + 0x795130,1,1,1,0);
  uVar6 = (uint)(iVar1 << 0x10) >> 0x18;
  iVar2 = DfsBwChQueryByDefault(param_1,2,param_1 + 0x795130,1,1,1,1);
  uVar4 = (uint)(iVar2 << 0x10) >> 0x18;
  uVar5 = (char)((uint)iVar1 >> 8);
  if ((uVar4 < uVar6) || (uVar5 = (char)((uint)iVar2 >> 8), uVar6 < uVar4)) {
    *(undefined1 *)(param_1 + 0x7953fb) = uVar5;
    *(undefined1 *)(param_1 + 0x7953fc) = 0;
  }
  else {
    uVar3 = RandomByte(param_1);
    *(undefined1 *)(param_1 + 0x7953fc) = 0;
    if ((uVar3 & 1) == 0) {
      uVar6 = uVar4;
    }
    *(char *)(param_1 + 0x7953fb) = (char)uVar6;
    if (uVar6 == 0) {
      if (DebugLevel < 1) {
        return;
      }
      printk("[%s] No available Outband BW\n","DfsDedicatedScanStart");
      return;
    }
  }
  MlmeEnqueue(param_1,0x2b,0xc,0,0,0);
  RtmpOsMlmeUp(param_1 + 0x286298);
  return;
}

