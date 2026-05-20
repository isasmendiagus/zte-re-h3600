// module: mt7915.ko
// function: ExtEventMecInfoRead @ 0x1a76ec
// size: 156 bytes
//

void ExtEventMecInfoRead(undefined4 param_1,ushort *param_2)

{
  ushort uVar1;
  
  if ((0 < DebugLevel) && (printk("MEC Ctrl Info:\n"), 3 < DebugLevel)) {
    printk("[%s] u2ReadType %2u\n","ExtEventMecInfoRead",*param_2);
  }
  uVar1 = *param_2;
  if ((uVar1 == 0) || ((uVar1 & 1) != 0)) {
    MecInfoAmsduEnPrint(param_1,param_2 + 2);
    uVar1 = *param_2;
    if (uVar1 == 0) goto LAB_001a7748;
  }
  if ((uVar1 & 2) == 0) {
    return;
  }
LAB_001a7748:
  MecInfoAmsduThrPrint(param_1,param_2 + 2);
  return;
}

