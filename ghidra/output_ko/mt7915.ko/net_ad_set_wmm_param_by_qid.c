// module: mt7915.ko
// function: net_ad_set_wmm_param_by_qid @ 0x25d0a0
// size: 244 bytes
//

int net_ad_set_wmm_param_by_qid(uint param_1,uint param_2,int param_3,int param_4)

{
  undefined2 uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_3 + 4));
  if (iVar2 == 0) {
    iVar3 = 0x606;
  }
  else {
    if (3 < param_1) {
      printk("%s: invalid wmm_idx=%d, ","net_ad_set_wmm_param_by_qid",param_1);
      param_1 = 0xff;
      printk("reset to 0xff!\n");
    }
    if ((param_2 & 0xfb) == 0x10 || param_2 == 1) {
      uVar1 = *(undefined2 *)(param_4 + 0xc20);
      iVar3 = AsicSetWmmParam(iVar2,param_1,param_2,1,*(undefined1 *)(param_4 + 0xc1f));
      if ((iVar3 == 0) && (iVar3 = AsicSetWmmParam(iVar2,param_1,param_2,2,uVar1), iVar3 == 0)) {
        iVar2 = AsicSetWmmParam(iVar2,param_1,param_2,3,uVar1);
        return iVar2;
      }
    }
    else {
      printk("%s: impossible!\n","net_ad_set_wmm_param_by_qid");
      iVar3 = 0x60a;
    }
  }
  return iVar3;
}

