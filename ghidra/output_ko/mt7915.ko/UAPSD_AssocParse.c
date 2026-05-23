// module: mt7915.ko
// function: UAPSD_AssocParse @ 0x1dddb0
// size: 452 bytes
//

void UAPSD_AssocParse(undefined4 param_1,int param_2,byte *param_3,int param_4)

{
  byte *pbVar1;
  undefined1 *puVar2;
  undefined1 *puVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  byte local_14;
  byte local_13 [3];
  
  iVar7 = DebugLevel;
  if (param_4 != 1 || param_2 == 0) {
    return;
  }
  uVar4 = (uint)*param_3;
  uVar6 = (uVar4 << 0x1d) >> 0x1f;
  local_14 = (byte)((uVar4 << 0x1d) >> 0x1f);
  local_13[0] = (byte)((uVar4 << 0x1c) >> 0x1f);
  local_13[1] = (byte)((uVar4 << 0x1e) >> 0x1f);
  local_13[2] = (byte)((uVar4 << 0x1f) >> 0x1f);
  *(byte *)(param_2 + 0xb15) = (byte)((uVar4 << 0x19) >> 0x1e);
  if (2 < iVar7) {
    uVar4 = (uint)*param_3;
    printk("apsd> UAPSD %d %d %d %d!\n",(uVar4 << 0x1c) >> 0x1f,(uVar4 << 0x1d) >> 0x1f,
           (uVar4 << 0x1e) >> 0x1f,uVar4 & 1);
    iVar7 = DebugLevel;
    if (2 < DebugLevel) {
      printk("apsd> MaxSPLength = %d\n",*(undefined1 *)(param_2 + 0xb15));
      iVar7 = DebugLevel;
    }
  }
  puVar2 = (undefined1 *)(param_2 + 0xb10);
  puVar3 = (undefined1 *)(param_2 + 0xb0c);
  pbVar1 = &local_14;
  iVar5 = 0;
  while( true ) {
    iVar5 = iVar5 + 1;
    puVar3 = puVar3 + 1;
    *puVar3 = (char)uVar6;
    puVar2 = puVar2 + 1;
    *puVar2 = (char)uVar6;
    if (iVar5 == 4) break;
    pbVar1 = pbVar1 + 1;
    uVar6 = (uint)*pbVar1;
  }
  uVar4 = *(uint *)(param_2 + 0xb0c) & 0xffffff00;
  if (uVar4 == 0) {
    if (*(char *)(param_2 + 0xb10) == '\0') {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) & 0xfffff7ff;
    }
    else {
      *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x800;
    }
  }
  else {
    *(uint *)(param_2 + 0xb4) = *(uint *)(param_2 + 0xb4) | 0x800;
    if ((uVar4 == 0x1010100) && (*(char *)(param_2 + 0xb10) == '\x01')) {
      if (2 < iVar7) {
        printk("apsd> all AC are UAPSD\n");
        iVar7 = DebugLevel;
      }
      *(undefined1 *)(param_2 + 0xb16) = 1;
      goto LAB_001dde78;
    }
  }
  if (2 < iVar7) {
    printk("apsd> at least one AC is not UAPSD %d %d %d %d\n",*(undefined1 *)(param_2 + 0xb0e),
           *(undefined1 *)(param_2 + 0xb0d),*(undefined1 *)(param_2 + 0xb0f),
           *(undefined1 *)(param_2 + 0xb10));
    iVar7 = DebugLevel;
  }
  *(undefined1 *)(param_2 + 0xb16) = 0;
LAB_001dde78:
  *(undefined1 *)(param_2 + 0xafa) = 0;
  if (2 < iVar7) {
    printk("apsd> MaxSPLength = %d\n",*(undefined1 *)(param_2 + 0xb15));
    return;
  }
  return;
}

