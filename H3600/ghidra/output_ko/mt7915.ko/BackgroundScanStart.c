// module: mt7915.ko
// function: BackgroundScanStart @ 0x22de6c
// size: 392 bytes
//

void BackgroundScanStart(int param_1,undefined4 param_2,uint param_3)

{
  byte bVar1;
  uint uVar2;
  
  os_zero_mem(param_1 + 0xa79234,0x3b0);
  *(undefined1 *)(param_1 + 0xa795e4) = 0;
  BuildBgndScanChList(param_1,param_2);
  uVar2 = param_3 & 0xf;
  if (2 < DebugLevel) {
    printk("%s BgndscanType=%d, band idx=%d ===============>\n","BackgroundScanStart",uVar2,
           param_3 >> 4);
  }
  *(undefined4 *)(param_1 + 0xa79184) = 0;
  if (uVar2 == 0) {
    *(char *)(param_1 + 0xa79754) = (char)param_3;
  }
  else {
    bVar1 = *(byte *)(param_1 + 0xa79754) & 0xf;
    if ((*(byte *)(param_1 + 0xa79754) & 0xf) != 0) {
      if (DebugLevel < 3) {
        return;
      }
      printk("%s Ap Background scan is running ===============>\n","BackgroundScanStart");
      return;
    }
    *(char *)(param_1 + 0xa79754) = (char)param_3;
    if (uVar2 == 1) {
      *(undefined4 *)(param_1 + 0xa79614) = 10;
      MlmeEnqueue(param_1,0x2b,10,bVar1,bVar1,param_3);
      goto LAB_0022df20;
    }
    if (uVar2 == 2) {
      MlmeEnqueue(param_1,0x2b,bVar1,bVar1,bVar1,param_3);
      goto LAB_0022df20;
    }
    if (uVar2 == 3) {
      *(undefined1 *)(param_1 + 0xa79791) = 1;
      MlmeEnqueue(param_1,0x2b,bVar1,bVar1,bVar1,param_3 & 0xf0 | 2);
      goto LAB_0022df20;
    }
  }
  *(undefined4 *)(param_1 + 0xa79614) = 0;
  MlmeEnqueue(param_1,0x2b,2,0,0,param_3);
LAB_0022df20:
  RtmpOsMlmeUp(param_1 + 0x286298);
  return;
}

