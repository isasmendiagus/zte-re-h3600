// module: mt7915.ko
// function: AsicCompensatePowerViaBBP @ 0x144ec8
// size: 188 bytes
//

void AsicCompensatePowerViaBBP
               (undefined4 param_1,char *param_2,undefined4 param_3,undefined4 param_4)

{
  char cVar1;
  undefined4 uVar2;
  
  if (3 < DebugLevel) {
    printk("%s: <Before> TotalDeltaPower = %d dBm\n","AsicCompensatePowerViaBBP",(int)*param_2);
  }
  cVar1 = *param_2;
  if (cVar1 < -0xb) {
    *param_2 = cVar1 + '\f';
    if (DebugLevel < 4) {
      return;
    }
    uVar2 = 0xc;
  }
  else if ((byte)(cVar1 + 0xbU) < 6) {
    *param_2 = cVar1 + '\x06';
    if (DebugLevel < 4) {
      return;
    }
    uVar2 = 6;
  }
  else {
    if (DebugLevel < 4) {
      return;
    }
    uVar2 = 0;
  }
  printk("%s: Drop the BBP transmit power by %d dBm!\n","AsicCompensatePowerViaBBP",uVar2,param_4);
  return;
}

