// module: mt7915.ko
// function: TKIP_GTK_KEY_WRAP @ 0x1181a4
// size: 224 bytes
//

void TKIP_GTK_KEY_WRAP(undefined4 *param_1,undefined4 *param_2,undefined4 param_3,undefined4 param_4
                      ,undefined4 param_5)

{
  int local_3c;
  undefined4 local_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined4 local_28;
  undefined4 uStack_24;
  undefined4 uStack_20;
  undefined4 uStack_1c;
  
  local_3c = 0;
  os_alloc_mem(0,&local_3c,0x108);
  if (local_3c == 0) {
    if (-1 < DebugLevel) {
      printk("%s: Allocate memory fail!!!\n","TKIP_GTK_KEY_WRAP");
    }
  }
  else {
    local_38 = *param_2;
    uStack_34 = param_2[1];
    uStack_30 = param_2[2];
    uStack_2c = param_2[3];
    uStack_1c = param_1[3];
    local_28 = *param_1;
    uStack_24 = param_1[1];
    uStack_20 = param_1[2];
    ARC4_INIT(local_3c,&local_38,0x20);
    ARC4_Discard_KeyLength(local_3c,0x100);
    ARC4_Compute(local_3c,param_3,param_4,param_5);
    if (local_3c != 0) {
      os_free_mem();
    }
  }
  return;
}

