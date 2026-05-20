// module: mt7915.ko
// function: TKIP_GTK_KEY_UNWRAP @ 0x118288
// size: 4 bytes
//

void TKIP_GTK_KEY_UNWRAP(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,
                        undefined4 param_4,undefined4 param_5)

{
  int iStack_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 uStack_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  iStack_3c = 0;
  os_alloc_mem(0,&iStack_3c,0x108);
  if (iStack_3c == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","TKIP_GTK_KEY_WRAP");
    }
  }
  else {
    uStack_38 = *param_2;
    uStack_34 = param_2[1];
    uStack_30 = param_2[2];
    uStack_2c = param_2[3];
    uStack_1c = param_1[3];
    uStack_28 = *param_1;
    uStack_24 = param_1[1];
    uStack_20 = param_1[2];
    ARC4_INIT(iStack_3c,&uStack_38,0x20);
    ARC4_Discard_KeyLength(iStack_3c,0x100);
    ARC4_Compute(iStack_3c,param_3,param_4,param_5);
    if (iStack_3c != 0) {
      os_free_mem();
    }
  }
  return;
}

