// module: mt7915.ko
// function: PrintSrDropTaInfo @ 0x16d27c
// size: 124 bytes
//

void PrintSrDropTaInfo(undefined4 *param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  
  if (-1 < DebugLevel) {
    printk("    DropTa %2d - Address : %x\n",param_2,*param_1);
  }
  if (param_3 != 0x20) {
    PrintSrStaInfo(param_1 + param_3 * 5 + 1,param_3);
    return;
  }
  param_1 = param_1 + 1;
  uVar2 = 0;
  do {
    uVar1 = uVar2 & 0xff;
    uVar2 = uVar2 + 1;
    PrintSrStaInfo(param_1,uVar1);
    param_1 = param_1 + 5;
  } while (uVar2 != 0x20);
  return;
}

