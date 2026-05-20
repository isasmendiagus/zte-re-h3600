// module: mt7915.ko
// function: net_ad_enq_pkt @ 0x25c8f4
// size: 252 bytes
//

undefined4 net_ad_enq_pkt(int param_1,uint param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 uVar4;
  undefined1 uVar5;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x606;
  }
  else if (param_4 == 0) {
    printk("%s: invalid wdev(%p)!\n","net_ad_enq_pkt",0);
    uVar2 = 0x607;
  }
  else if (param_3 == 0) {
    uVar2 = 0x607;
  }
  else {
    if (param_5 == 0) {
      return 0;
    }
    iVar3 = skb_clone(param_5,0x20);
    if (iVar3 == 0) {
      printk("%s: clone packet fail\n","net_ad_enq_pkt");
      uVar2 = 0x600;
    }
    else {
      uVar4 = 8;
      *(undefined2 *)(iVar3 + 0x42) = *(undefined2 *)(param_3 + 0xe0);
      uVar5 = *(undefined1 *)(param_4 + 0xc);
      *(undefined1 *)(iVar3 + 0x36) = 8;
      if (param_2 != 0) {
        uVar4 = 1;
      }
      else {
        *(undefined1 *)(iVar3 + 0x4d) = 0;
      }
      *(undefined1 *)(iVar3 + 0x2d) = uVar5;
      if (param_2 != 0) {
        uVar5 = 0;
        *(undefined1 *)(iVar3 + 0x4d) = uVar4;
      }
      else {
        uVar5 = 2;
      }
      *(undefined1 *)(iVar3 + 0x4f) = uVar5;
      iVar1 = send_mlme_pkt(iVar1,iVar3,param_4,param_2 & 0xff,0);
      if (iVar1 == 0) {
        return 0;
      }
      uVar2 = 0x600;
    }
  }
  return uVar2;
}

