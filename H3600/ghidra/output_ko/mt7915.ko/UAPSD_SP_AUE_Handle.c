// module: mt7915.ko
// function: UAPSD_SP_AUE_Handle @ 0x1de12c
// size: 868 bytes
//

/* WARNING: Removing unreachable block (ram,0x001de330) */
/* WARNING: Removing unreachable block (ram,0x001de1a4) */
/* WARNING: Removing unreachable block (ram,0x001de244) */

void UAPSD_SP_AUE_Handle(int *param_1,int param_2)

{
  ushort uVar1;
  bool bVar2;
  int iVar3;
  byte bVar4;
  short sVar5;
  int iVar6;
  short *psVar7;
  
  if (param_2 == 0) {
    return;
  }
  if (*(char *)(param_2 + 0xaf8) == '\0') {
    if (2 < DebugLevel) {
      printk("uapsd> aux: Station actives! Close SP!\n");
    }
    *(undefined1 *)(param_2 + 0xb62) = 0;
    *(undefined1 *)(param_2 + 0xb63) = 0;
    *(undefined1 *)((int)param_1 + 0x58000d) = 0;
    return;
  }
  uVar1 = *(ushort *)(param_2 + 0xe0);
  if (*(char *)(param_2 + 0xaf8) != '\x01') {
    return;
  }
  _raw_spin_lock_bh(param_1 + 0xa5e24);
  if (*(char *)(param_2 + 0xb68) == '\0') {
    psVar7 = (short *)(param_2 + 0xb60);
    if (2 < DebugLevel) {
      printk("uapsd> aux: Tx Num = %d\n",*psVar7);
    }
    iVar3 = DebugLevel;
    if ((*(char *)(param_2 + 0xb63) == '\0') && (*(undefined1 *)(param_2 + 0xb69) = 0, 2 < iVar3)) {
      printk("uapsd> legacy PS packet is sent!\n");
    }
    *(undefined4 *)(param_2 + 0xb64) = jiffies;
    sVar5 = *psVar7;
    if (sVar5 == 0) {
      if ((char)param_1[0xa5e25] == '\x01') {
        if (2 < DebugLevel) {
          printk("uapsd> aux: SP is suspend, keep SP if exists!\n");
        }
        *(undefined1 *)(param_2 + 0xb62) = 1;
      }
      iVar3 = DebugLevel;
      if ((*(char *)(param_2 + 0xb63) == '\0') || ((char)param_1[0xa5e25] != '\0'))
      goto LAB_001de2fc;
      *(undefined1 *)(param_2 + 0xb62) = 0;
      *(undefined1 *)(param_2 + 0xb63) = 0;
      *(undefined1 *)((int)param_1 + 0x58000d) = 0;
    }
    else {
      if (sVar5 != 1) {
        bVar2 = false;
LAB_001de22c:
        *psVar7 = sVar5 + -1;
        _raw_spin_unlock_bh(param_1 + 0xa5e24);
        if (bVar2) {
          iVar6 = *param_1;
          iVar3 = hc_get_hif_type(param_1[0x29e5e8]);
          if ((iVar3 == 1) || (iVar3 = hc_get_hif_type(param_1[0x29e5e8]), iVar3 == 0)) {
            iVar3 = _test_and_set_bit(0,iVar6 + 0x18);
            if (iVar3 == 0) {
              __tasklet_hi_schedule(iVar6 + 0x14);
              return;
            }
          }
        }
        return;
      }
      iVar3 = *(int *)(param_2 + 0xb5c);
      if (iVar3 == 0) {
        bVar2 = false;
        goto LAB_001de22c;
      }
      if (2 < DebugLevel) {
        printk("uapsd> aux: send EOSP frame...\n");
        iVar3 = *(int *)(param_2 + 0xb5c);
      }
      bVar4 = *(byte *)(iVar3 + 0x32) & 0x7f;
      if (3 < bVar4) {
        bVar4 = 0;
      }
      iVar3 = ge_enq_req(param_1,iVar3,bVar4,param_1 + (uint)uVar1 * 0x188 + 0xbda8,0);
      if (iVar3 != 0) {
        *(undefined4 *)(param_2 + 0xb5c) = 0;
        bVar2 = true;
        sVar5 = *psVar7;
        goto LAB_001de22c;
      }
      RTMPFreeNdisPacket(param_1,*(undefined4 *)(param_2 + 0xb5c));
      if ((char)param_1[0xa5e25] == '\x01') {
        if (2 < DebugLevel) {
          printk("uapsd> aux: SP is suspend, keep SP if exists!\n");
        }
        *(undefined1 *)(param_2 + 0xb62) = 1;
      }
      iVar3 = DebugLevel;
      if ((*(char *)(param_2 + 0xb63) == '\0') || ((char)param_1[0xa5e25] != '\0'))
      goto LAB_001de2fc;
      *(undefined1 *)(param_2 + 0xb62) = 0;
      *(undefined1 *)(param_2 + 0xb63) = 0;
      *(undefined1 *)((int)param_1 + 0x58000d) = 0;
    }
    if (2 < iVar3) {
      printk("uapsd> aux: close a SP.\n\n\n");
    }
  }
LAB_001de2fc:
  _raw_spin_unlock_bh();
  return;
}

