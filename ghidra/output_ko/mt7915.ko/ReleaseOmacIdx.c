// module: mt7915.ko
// function: ReleaseOmacIdx @ 0xacad8
// size: 392 bytes
//

void ReleaseOmacIdx(int param_1,uint param_2,int param_3,uint param_4)

{
  uint *puVar1;
  
  puVar1 = (uint *)0x0;
  if (param_3 != 0) {
    puVar1 = *(uint **)(param_3 + 8);
  }
  if (param_1 == 0) {
    if (param_2 == 0x40) goto LAB_000acbac;
    if (param_2 < 0x41) {
      if (param_2 == 4) goto LAB_000acbac;
      if (4 < param_2) goto LAB_000acb40;
      if (param_2 != 1) goto LAB_000acba4;
    }
    else if (param_2 != 0x800) {
      if (param_2 < 0x801) {
        if (param_2 == 0x100) {
          return;
        }
        goto LAB_000acc00;
      }
      if (param_2 != 0x2000) goto LAB_000acc38;
    }
    if (param_4 != 0) {
      return;
    }
  }
  else {
    if (param_2 == 0x40) goto LAB_000acbac;
    if (param_2 < 0x41) {
      if (param_2 == 4) goto LAB_000acbac;
      if (4 < param_2) {
LAB_000acb40:
        if (param_2 == 0x10) {
          return;
        }
        if (param_2 != 0x20) {
          if (param_2 == 8) {
            return;
          }
          goto LAB_000acb58;
        }
        goto LAB_000acbac;
      }
      if (param_2 != 1) {
LAB_000acba4:
        if (param_2 != 2) goto LAB_000acb58;
        goto LAB_000acbac;
      }
    }
    else if (param_2 != 0x800) {
      if (param_2 < 0x801) {
        if (param_2 == 0x100) {
          if (puVar1 != (uint *)0x0) {
            puVar1[2] = puVar1[2] & ~(1 << (param_4 - *(byte *)(param_1 + 0xc80) & 0xff));
            return;
          }
          return;
        }
LAB_000acc00:
        if (param_2 != 0x200) {
LAB_000acb58:
          if (-1 < DebugLevel) {
            printk("%s: OmacType(%d)\n","ReleaseOmacIdx",param_2);
            return;
          }
          return;
        }
LAB_000acbac:
        if (puVar1 != (uint *)0x0) {
          *puVar1 = *puVar1 & ~(1 << (param_4 & 0xff));
        }
        return;
      }
      if (param_2 != 0x2000) {
LAB_000acc38:
        if ((param_2 != 0x4000) && (param_2 != 0x1000)) goto LAB_000acb58;
        goto LAB_000acbac;
      }
    }
    if (param_4 != 0) {
      if (param_1 != -0xb34 && puVar1 != (uint *)0x0) {
        puVar1[1] = puVar1[1] & ~(1 << (param_4 - *(byte *)(param_1 + 0xc7f) & 0xff));
        return;
      }
      return;
    }
  }
  if (puVar1 != (uint *)0x0) {
    *puVar1 = *puVar1 & 0xfffffffe;
  }
  return;
}

