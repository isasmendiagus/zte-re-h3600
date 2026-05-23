// module: mt7915.ko
// function: net_ad_read_bulk_rf_reg @ 0x25d70c
// size: 184 bytes
//

int net_ad_read_bulk_rf_reg(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 local_24 [2];
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar2 == 0) {
    iVar2 = 0x606;
  }
  else {
    if ((short)param_2[1] != 0) {
      uVar5 = 0;
      do {
        iVar1 = uVar5 * 4;
        iVar4 = param_2[2];
        iVar6 = iVar1 + *param_2;
        uVar5 = uVar5 + 1;
        iVar3 = MtCmdRFRegAccessRead(iVar2,param_2[3],iVar6,local_24);
        if (iVar3 != 0) {
          printk("wf_sel=%d, cr_addr=0x%08x, ",param_2[3],iVar6);
          printk("cr_val=0x%08x fail\n",local_24[0]);
          return iVar3;
        }
        sys_ad_move_mem((void *)(iVar4 + iVar1),local_24,4);
      } while (uVar5 < *(ushort *)(param_2 + 1));
    }
    iVar2 = 0;
  }
  return iVar2;
}

