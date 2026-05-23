// module: mt7915.ko
// function: mt_mac_cr_range_mapping @ 0x1df07c
// size: 336 bytes
//

int mt_mac_cr_range_mapping(int param_1,uint *param_2)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  undefined1 *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  
  uVar6 = *param_2;
  if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7915) {
    if (DebugLevel < 1) {
      return 0;
    }
    printk("%s(): NotSupported Chip for this function!, CHIP_ID=%x\n","mt_mac_cr_range_mapping",
           *(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc));
    return 0;
  }
  iVar2 = 0;
  puVar4 = mt7915_mac_cr_range;
  while ((uVar7 = *(uint *)(mt7915_mac_cr_range + iVar2 * 4), uVar6 < uVar7 ||
         (uVar7 + *(int *)(puVar4 + 8) <= uVar6))) {
    piVar1 = (int *)(puVar4 + 0x14);
    iVar2 = iVar2 + 3;
    puVar4 = puVar4 + 0xc;
    if (*piVar1 == 0) {
      uVar3 = *(uint *)(param_1 + 0x286280);
      iVar2 = 0;
      if ((uVar3 & 0xfffffffb) != 1) {
LAB_001df13c:
        if (uVar3 == 4) {
LAB_001df148:
          iVar5 = iVar2;
          if (uVar6 < 0x100000) {
            iVar5 = 0;
          }
          if (iVar5 != 0) {
            if (DebugLevel < 1) {
              return 0;
            }
            printk("CR Addr[0x%x] out of range\n",uVar6);
            return 0;
          }
        }
      }
      *param_2 = uVar6;
      return iVar2;
    }
  }
  uVar3 = *(uint *)(param_1 + 0x286280);
  uVar6 = (uVar6 - uVar7) + *(int *)(mt7915_mac_cr_range + (iVar2 + 1) * 4);
  if ((uVar3 & 0xfffffffb) != 1) {
    iVar2 = 1;
    goto LAB_001df13c;
  }
  iVar2 = 1;
  goto LAB_001df148;
}

