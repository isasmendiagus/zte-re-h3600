// module: mt7915.ko
// function: net_ad_post_tx @ 0x25c9f4
// size: 336 bytes
//

undefined4 net_ad_post_tx(int param_1,uint *param_2,uint param_3,int param_4)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  
  iVar3 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar3 == 0) {
    uVar4 = 0x606;
  }
  else if (param_3 < 2) {
    uVar5 = *param_2;
    uVar6 = param_2[0x30e];
    if ((uVar5 & 2) == 0) {
      uVar4 = 0;
    }
    else {
      if (param_4 != 0) {
        *(int *)(iVar3 + 0xa39e6c) = *(int *)(iVar3 + 0xa39e6c) + 1;
      }
      uVar2 = (uint)(param_4 != 0);
      cVar1 = (char)param_2[0x81];
      if (cVar1 == '\x01') {
        net_ad_thread_proceed_tx(param_1,param_3);
        uVar4 = 0;
      }
      else if (cVar1 == '\0') {
        if (uVar2 < uVar6) {
          uVar4 = net_ad_enq_pkt(param_1,*(undefined2 *)((int)param_2 + 0x2e),param_2[0x9f],
                                 param_2[0xaf],param_2[0xbf]);
        }
        else if (uVar2 == uVar6) {
          if ((uVar5 & 0x40) != 0) {
            complete(param_2 + 4);
          }
          uVar4 = 0;
          *(undefined1 *)(param_2 + 8) = 0;
        }
        else {
          printk("%s: do not match any condition, ","net_ad_post_tx");
          printk("op_mode:0x%x, tx_cnt:%u, txdone_cnt:%u\n",uVar5,uVar6,uVar2);
          uVar4 = 0;
        }
      }
      else {
        printk("%s: wrong tx strategy=%d, ret=0x%08x\n","net_ad_post_tx",cVar1,0x60a);
        uVar4 = 0x60a;
      }
    }
  }
  else {
    printk("%s: wrong band_idx %u, ret=0x%08x\n","net_ad_post_tx",param_3,0x608);
    uVar4 = 0x608;
  }
  return uVar4;
}

