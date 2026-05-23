// module: mt7915.ko
// function: MT_ATEInsertRXV @ 0x27b83c
// size: 228 bytes
//

undefined4 MT_ATEInsertRXV(undefined4 *param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (param_1 == (undefined4 *)0x0 || param_2 == 0) {
    if (DebugLevel < 0) {
      uVar1 = 0xffffffff;
    }
    else {
      printk("%s: NULL entry %p, data %p\n","MT_ATEInsertRXV",param_1,param_2,param_4);
      uVar1 = 0xffffffff;
    }
  }
  else {
    os_zero_mem(param_1,0x2c);
    *(undefined1 *)(param_1 + 1) = 1;
    *param_1 = 2;
    if ((undefined4 *)(param_2 + 8) != (undefined4 *)0x0) {
      param_1[2] = *(undefined4 *)(param_2 + 8);
    }
    if ((undefined4 *)(param_2 + 0xc) != (undefined4 *)0x0) {
      param_1[3] = *(undefined4 *)(param_2 + 0xc);
    }
    if ((undefined4 *)(param_2 + 0x10) != (undefined4 *)0x0) {
      param_1[4] = *(undefined4 *)(param_2 + 0x10);
    }
    if ((undefined4 *)(param_2 + 0x14) != (undefined4 *)0x0) {
      param_1[5] = *(undefined4 *)(param_2 + 0x14);
    }
    if ((undefined4 *)(param_2 + 0x18) != (undefined4 *)0x0) {
      param_1[6] = *(undefined4 *)(param_2 + 0x18);
    }
    if ((undefined4 *)(param_2 + 0x1c) != (undefined4 *)0x0) {
      param_1[7] = *(undefined4 *)(param_2 + 0x1c);
    }
    if ((undefined4 *)(param_2 + 0x20) != (undefined4 *)0x0) {
      param_1[8] = *(undefined4 *)(param_2 + 0x20);
    }
    if ((undefined4 *)(param_2 + 0x24) != (undefined4 *)0x0) {
      param_1[9] = *(undefined4 *)(param_2 + 0x24);
    }
    uVar1 = 0;
    if ((undefined4 *)(param_2 + 0x28) != (undefined4 *)0x0) {
      uVar1 = 0;
      param_1[10] = *(undefined4 *)(param_2 + 0x28);
    }
  }
  return uVar1;
}

