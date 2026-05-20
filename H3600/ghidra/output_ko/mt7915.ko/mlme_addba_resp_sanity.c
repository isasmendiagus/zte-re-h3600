// module: mt7915.ko
// function: mlme_addba_resp_sanity @ 0x1107e4
// size: 208 bytes
//

undefined4 mlme_addba_resp_sanity(undefined4 param_1,ushort *param_2,int param_3)

{
  ushort uVar1;
  uint uVar2;
  
  if (param_3 == 0x10) {
    uVar1 = *param_2;
    uVar2 = HcGetMaxStaNum();
    if (uVar1 < uVar2) {
      if ((*(byte *)((int)param_2 + 0xb) & 0xf0) == 0) {
        return 1;
      }
      if (-1 < DebugLevel) {
        printk("%s: The peer TID is incorrect\n","mlme_addba_resp_sanity");
        return 0;
      }
    }
    else if (-1 < DebugLevel) {
      printk("%s: The peer Mac is not associated yet\n","mlme_addba_resp_sanity");
      return 0;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: message lenght not correct\n","mlme_addba_resp_sanity");
  }
  return 0;
}

