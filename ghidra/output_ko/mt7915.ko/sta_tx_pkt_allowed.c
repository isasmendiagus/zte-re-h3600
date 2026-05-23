// module: mt7915.ko
// function: sta_tx_pkt_allowed @ 0x53060
// size: 540 bytes
//

bool sta_tx_pkt_allowed(int param_1,int param_2,int param_3)

{
  ushort uVar1;
  undefined1 uVar2;
  int iVar3;
  int iVar4;
  undefined2 uVar5;
  uint uVar6;
  byte *pbVar7;
  uint uVar8;
  bool bVar9;
  
  iVar3 = GetStaCfgByWdev();
  pbVar7 = *(byte **)(param_3 + 0xcc);
  uVar8 = *(uint *)(param_3 + 100);
  if ((pbVar7 == (byte *)0x0 || 0xd < uVar8) && (pbVar7 != (byte *)0x0 && uVar8 != 0xe)) {
    if (iVar3 == 0) {
      printk(&_LC1,0x2c);
      dump_stack();
      return false;
    }
    if ((*(byte *)(iVar3 + 0x4060) < 2) && ("hif_set_WPDMA"[param_1 + 0xc] != '\x01')) {
      if (*(byte *)(iVar3 + 0x4060) == 0) {
        if ((*(uint *)(param_1 + 0x795124) & 2) != 0) {
          if ((*pbVar7 & 1) == 0) {
            iVar3 = MacTableLookup2(param_1,pbVar7,param_2);
            bVar9 = iVar3 != 0;
            if (bVar9) {
              uVar5 = *(undefined2 *)(iVar3 + 0xe0);
            }
            else {
              uVar5 = 0xffff;
            }
          }
          else {
            bVar9 = true;
            *(undefined2 *)(param_3 + 0x42) = *(undefined2 *)(param_2 + 0x10);
            uVar5 = *(undefined2 *)(param_2 + 0x10);
          }
          *(undefined2 *)(param_3 + 0x42) = uVar5;
          return bVar9;
        }
      }
      else if ((*(uint *)(iVar3 + 0x212464) & 1) != 0) {
        iVar4 = GetAssociatedAPByWdev(param_1,param_2);
        if (iVar4 == 0) {
          return false;
        }
        uVar1 = *(ushort *)(iVar4 + 0xe0);
        uVar6 = (uint)uVar1;
        uVar2 = get_frag_num(param_1,param_2,param_3);
        *(undefined1 *)(param_3 + 0x2b) = uVar2;
        uVar8 = hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
        if (0x11f < uVar6 || uVar8 <= uVar6) {
          return false;
        }
        iVar4 = RTMPCheckEtherType(param_1,param_3,param_1 + uVar6 * 0x620 + 0x2f6a0,param_2);
        if (iVar4 == 0) {
          return false;
        }
        if (((((*(int *)(param_2 + 0x12e4) != 0) && (*(char *)(param_2 + 0x3cc8) != '\0')) ||
             (*(char *)(param_2 + 0x888) == '\x02')) || (1 < *(uint *)(iVar3 + 0x2127b4))) &&
           ((*(byte *)(param_3 + 0x30) & 2) == 0)) {
          return false;
        }
        *(ushort *)(param_3 + 0x42) = uVar1;
        return true;
      }
      uVar2 = get_frag_num(param_1,param_2,param_3);
      *(undefined1 *)(param_3 + 0x2b) = uVar2;
      hc_get_chip_wtbl_max_num(*(undefined4 *)(param_1 + 0xa797a0));
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s():pkt error(%p, %d)\n","sta_tx_pkt_allowed",pbVar7,uVar8);
    return false;
  }
  return false;
}

