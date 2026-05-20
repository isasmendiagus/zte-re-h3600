// module: mt7915.ko
// function: net_ad_write_bulk_rf_reg @ 0x25d7c4
// size: 180 bytes
//

int net_ad_write_bulk_rf_reg(int param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 local_1c;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    iVar1 = 0x606;
  }
  else {
    if ((short)param_2[1] != 0) {
      uVar3 = 0;
      do {
        iVar4 = uVar3 * 4 + *param_2;
        sys_ad_move_mem(&local_1c,(void *)(param_2[2] + uVar3 * 4),4);
        uVar3 = uVar3 + 1;
        iVar2 = MtCmdRFRegAccessWrite(iVar1,param_2[3],iVar4,local_1c);
        if (iVar2 != 0) {
          printk("wf_sel=%d, cr_addr=0x%08x, ",param_2[3],iVar4);
          printk("cr_val=0x%08x fail\n",local_1c);
          return iVar2;
        }
      } while (uVar3 < *(ushort *)(param_2 + 1));
    }
    iVar1 = 0;
  }
  return iVar1;
}

