// module: mt7915.ko
// function: HdevCfgShow @ 0xae62c
// size: 728 bytes
//

void HdevCfgShow(int param_1)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  ushort uVar5;
  int iVar6;
  undefined4 *puVar7;
  uint uVar8;
  undefined1 *puVar9;
  undefined4 *local_54;
  undefined4 local_48;
  uint local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  if (0 < DebugLevel) {
    printk("band_num: %d\n",*(undefined1 *)(param_1 + 0x32d8));
  }
  RcRadioShow(param_1 + 0x1360);
  if (*(char *)(param_1 + 0x32d8) != '\0') {
    uVar8 = 0;
    local_54 = &_LC13;
    do {
      puVar9 = *(undefined1 **)(param_1 + uVar8 * 0x1c + 4);
      uVar1 = puVar9[4];
      uVar5 = *(ushort *)(puVar9 + 2);
      uVar2 = puVar9[7];
      uVar3 = puVar9[6];
      uVar4 = puVar9[8];
      local_40 = 0;
      local_3c = 0;
      local_38 = 0;
      local_34 = 0;
      local_30 = 0;
      local_2c = 0;
      if ((uVar5 & 0x4e) == 0) {
        puVar7 = local_54;
        if ((uVar5 & 0x100) == 0) {
          puVar7 = &_LC14;
        }
        local_48 = *puVar7;
        local_44 = puVar7[1] & 0xff;
      }
      else {
        local_48 = 0x47342e32;
        local_44 = 0x7a48;
      }
      if (0 < DebugLevel) {
        printk("==========%s band==========\n",&local_48);
      }
      iVar6 = wmode_2_str(uVar5);
      if (iVar6 != 0) {
        if (0 < DebugLevel) {
          printk("wmode\t: %s\n",iVar6);
        }
        os_free_mem(iVar6);
      }
      if (0 < DebugLevel) {
        printk("ch\t: %d\n",uVar1);
      }
      if ((uVar5 & 0x18) == 0) {
LAB_000ae778:
        if ((uVar5 & 0x20) == 0) goto LAB_000ae780;
        if (0 < DebugLevel) {
          printk("cen ch2\t: %d\n",puVar9[5]);
          goto LAB_000ae780;
        }
      }
      else {
        bw_2_str(uVar2,&local_48);
        if (0 < DebugLevel) {
          printk("bw\t: %s\n",&local_48);
        }
        extcha_2_str(uVar4,&local_48);
        if ((0 < DebugLevel) && (printk("extcha\t: %s\n",&local_48), 0 < DebugLevel)) {
          printk("cen_ch\t: %d\n",uVar3);
          goto LAB_000ae778;
        }
        if ((uVar5 & 0x20) != 0) goto LAB_000ae6ac;
LAB_000ae780:
        if (((0 < DebugLevel) && (printk("band_id\t: %d\n",*puVar9), 0 < DebugLevel)) &&
           (printk("obj_num\t: %d\n",*(undefined1 *)(param_1 + uVar8 * 0x1c + 0x14)), 0 < DebugLevel
           )) {
          printk("state\t: %d\n",puVar9[1]);
        }
      }
LAB_000ae6ac:
      uVar8 = uVar8 + 1 & 0xff;
    } while (uVar8 < *(byte *)(param_1 + 0x32d8));
  }
  return;
}

