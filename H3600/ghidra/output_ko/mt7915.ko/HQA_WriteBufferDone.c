// module: mt7915.ko
// function: HQA_WriteBufferDone @ 0x27466c
// size: 248 bytes
//

undefined4 HQA_WriteBufferDone(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  
  if (2 < DebugLevel) {
    printk(&_LC11,"HQA_WriteBufferDone");
  }
  uVar1 = *(uint *)(param_3 + 0xc);
  uVar1 = uVar1 << 0x18 | (uVar1 >> 8 & 0xff) << 0x10 | (uVar1 >> 0x10 & 0xff) << 8 | uVar1 >> 0x18;
  switch(uVar1) {
  case 1:
    Set_EepromBufferWriteBack_Proc(param_1,&_LC93);
    break;
  case 2:
    Set_EepromBufferWriteBack_Proc(param_1,&_LC94);
    break;
  case 3:
    Set_EepromBufferWriteBack_Proc(param_1,&_LC95);
    break;
  case 4:
    Set_EepromBufferWriteBack_Proc(param_1,&_LC96);
    break;
  default:
    if (2 < DebugLevel) {
      printk("%s: Unknow write back mode(%d)\n","HQA_WriteBufferDone",uVar1);
    }
  }
  FUN_0026cdd0(param_3,param_2,2,0);
  return 0;
}

