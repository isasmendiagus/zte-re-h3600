// module: mt7915.ko
// function: GetOmacIdx @ 0xacc64
// size: 624 bytes
//

uint GetOmacIdx(int param_1,uint param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint *puVar5;
  
  puVar5 = *(uint **)(param_3 + 8);
  if (param_2 != 0x40) {
    if (param_2 < 0x41) {
      if (param_2 != 4) {
        if (param_2 < 5) {
          if (param_2 == 1) goto LAB_000acd98;
          if (param_2 != 2) goto LAB_000ace28;
        }
        else {
          if (param_2 == 0x10) {
            return 0xffffffff;
          }
          if (param_2 != 0x20) {
            if (param_2 == 8) {
              return 0;
            }
            goto LAB_000ace28;
          }
        }
      }
    }
    else {
      if (param_2 == 0x800) {
LAB_000acd98:
        uVar3 = GetFirstAvailableApOmacIdx(param_1,puVar5);
        return uVar3;
      }
      if (param_2 < 0x801) {
        if (param_2 == 0x100) {
          if (*(byte *)(param_1 + 0xc7e) == 0) {
LAB_000acd6c:
            if (DebugLevel < 0) {
              return 0xffffffff;
            }
            printk("%s: OmacIndex is not available\n","GetFirstAvailableRepeaterOmacIdx");
            return 0xffffffff;
          }
          uVar3 = puVar5[2];
          if ((uVar3 & 1) == 0) {
            uVar2 = 1;
            uVar4 = 0;
          }
          else {
            uVar1 = 1;
            do {
              uVar4 = uVar1;
              uVar2 = 1 << (uVar4 & 0xff);
              if ((uint)*(byte *)(param_1 + 0xc7e) <= (uVar4 & 0xff)) goto LAB_000acd6c;
              uVar1 = uVar4 + 1;
            } while ((uVar2 & uVar3) != 0);
          }
          puVar5[2] = uVar2 | uVar3;
          if (2 < DebugLevel) {
            printk("%s: found used OmacIndex:0x%x\n","GetFirstAvailableRepeaterOmacIdx",
                   *(byte *)(param_1 + 0xc80) + uVar4);
          }
          return *(byte *)(param_1 + 0xc80) + uVar4;
        }
        if (param_2 != 0x200) {
LAB_000ace28:
          if (DebugLevel < 0) {
            return 0xffffffff;
          }
          printk("%s: OmacType(%d)\n","GetOmacIdx",param_2);
          return 0xffffffff;
        }
        uVar3 = (uint)*(byte *)(param_1 + 0xc7c);
        if (uVar3 < *(byte *)(param_1 + 0xc7b)) {
          uVar2 = uVar3;
          do {
            if ((1 << uVar2 & *puVar5) == 0) {
              *puVar5 = 1 << uVar2 | *puVar5;
              return uVar3;
            }
            uVar3 = uVar3 + 1;
            uVar2 = uVar3 & 0xff;
          } while (uVar3 < *(byte *)(param_1 + 0xc7b));
        }
        goto LAB_000acce0;
      }
      if (param_2 == 0x2000) goto LAB_000acd98;
      if ((param_2 != 0x4000) && (param_2 != 0x1000)) goto LAB_000ace28;
    }
  }
  if (*(byte *)(param_1 + 0xc7c) != 0) {
    uVar3 = 0;
    do {
      uVar4 = uVar3 + 1;
      uVar2 = 1 << (uVar3 & 0xff);
      if ((uVar3 != 0 || param_2 != 2) && ((uVar2 & *puVar5) == 0)) {
        *puVar5 = *puVar5 | uVar2;
        return uVar3;
      }
      uVar3 = uVar4;
    } while (uVar4 != *(byte *)(param_1 + 0xc7c));
  }
LAB_000acce0:
  if (DebugLevel < 0) {
    return 0xffffffff;
  }
  printk("%s: OmacIndex is not available\n","GetFirstAvailableOmacIdx");
  return 0xffffffff;
}

