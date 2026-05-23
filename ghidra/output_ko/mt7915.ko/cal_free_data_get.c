// module: mt7915.ko
// function: cal_free_data_get @ 0x17ce00
// size: 708 bytes
//

void cal_free_data_get(int param_1)

{
  int iVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  ushort *puVar5;
  undefined1 local_22 [2];
  
  if (2 < DebugLevel) {
    printk(&_LC312,"cal_free_data_get");
  }
  rtmp_ee_efuse_read16(param_1,0x50,local_22);
  iVar1 = DebugLevel;
  *(char *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x50) = local_22[0];
  if (3 < iVar1) {
    printk("\t\t%s Replace: 0x%x=0x%x\n","cal_free_data_get_from_addr",0x50,
           *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x50));
  }
  iVar3 = *(byte *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x50) - 1;
  iVar1 = iVar3 * 0x7a;
  cVar2 = (&DAT_0029b96c)[iVar1];
  if (cVar2 != '\0') {
    puVar5 = (ushort *)(&DAT_0029b96c + iVar1);
    do {
      puVar5 = puVar5 + 1;
      uVar4 = (uint)*puVar5;
      if ((*puVar5 & 1) == 0) {
        rtmp_ee_efuse_read16(param_1,uVar4,local_22);
        *(char *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar4) = local_22[0];
      }
      else {
        rtmp_ee_efuse_read16(param_1,uVar4 - 1,local_22);
        *(char *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar4) = local_22[1];
      }
      if (3 < DebugLevel) {
        printk("\t\t%s Replace: 0x%x=0x%x\n","cal_free_data_get_from_addr",uVar4,
               *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar4));
      }
    } while (puVar5 != (ushort *)(&DAT_0029b96c + ((byte)(cVar2 - 1) + 1 + iVar3 * 0x3d) * 2));
  }
  rtmp_ee_efuse_read16(param_1,0x9a0,local_22);
  iVar1 = DebugLevel;
  *(char *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x9a0) = local_22[0];
  if (3 < iVar1) {
    printk("\t\t%s Replace: 0x%x=0x%x\n","cal_free_data_get_from_addr",0x9a0,
           *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x9a0));
  }
  iVar3 = *(byte *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x9a0) - 1;
  iVar1 = iVar3 * 0x7a;
  cVar2 = (&DAT_0029b9e8)[iVar1];
  if (cVar2 != '\0') {
    puVar5 = (ushort *)(&DAT_0029b9e8 + iVar1);
    do {
      puVar5 = puVar5 + 1;
      uVar4 = (uint)*puVar5;
      if ((*puVar5 & 1) == 0) {
        rtmp_ee_efuse_read16(param_1,uVar4,local_22);
        *(char *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar4) = local_22[0];
      }
      else {
        rtmp_ee_efuse_read16(param_1,uVar4 - 1,local_22);
        *(char *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar4) = local_22[1];
      }
      if (3 < DebugLevel) {
        printk("\t\t%s Replace: 0x%x=0x%x\n","cal_free_data_get_from_addr",uVar4,
               *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + uVar4));
      }
      iVar1 = DebugLevel;
      if (uVar4 == 0x9a1) {
        *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x77) =
             *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x9a1);
        if (3 < iVar1) {
          printk("\t\t%s Replace: 0x77=0x%x\n","cal_free_data_get",
                 *(undefined1 *)(*(int *)("Set_IRR_TTGOnOff" + param_1 + 4) + 0x9a1));
        }
      }
    } while (puVar5 != (ushort *)(&DAT_0029b9e8 + ((byte)(cVar2 - 1) + 1 + iVar3 * 0x3d) * 2));
  }
  if (0 < DebugLevel) {
    printk(&_LC43);
  }
  return;
}

