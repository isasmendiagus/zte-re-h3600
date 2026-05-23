// module: mt7915.ko
// function: set_eFusedump_Proc @ 0x1d2b9c
// size: 228 bytes
//

undefined1 set_eFusedump_Proc(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  uint uVar3;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  uVar1 = 0;
  if ("Set_IRR_TTGOnOff"[param_1 + 1] != '\0') {
    if (*(ushort *)(iVar2 + 0xe8) >> 1 != 0) {
      uVar3 = 0;
      do {
        local_1c = 2;
        local_1e = (undefined2)(uVar3 << 1);
        local_1a = 0;
        eFuseReadPhysical(param_1,&local_1e,4,&local_1a,2);
        if ((uVar3 & 3) == 0) {
          if (0 < DebugLevel) {
            printk("\nBlock %x:",(int)uVar3 >> 3);
            goto LAB_001d2c40;
          }
        }
        else {
LAB_001d2c40:
          if (0 < DebugLevel) {
            printk("%04x ",local_1a);
          }
        }
        uVar3 = uVar3 + 1;
      } while ((int)uVar3 < (int)(uint)(*(ushort *)(iVar2 + 0xe8) >> 1));
    }
    uVar1 = 1;
  }
  return uVar1;
}

