// module: mt7915.ko
// function: net_ad_set_device_info @ 0x25d2f0
// size: 268 bytes
//

undefined4
net_ad_set_device_info(int param_1,int param_2,void *param_3,undefined4 param_4,char param_5)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_29 [5];
  
  local_29[0] = 0;
  uVar2 = *(undefined4 *)
           (param_2 + (uint)*(byte *)(param_2 + (uint)*(byte *)(param_2 + 0xc55) + 0x205) * 4 + 0x24
           );
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  uVar2 = net_ad_get_omac_idx(param_1,uVar2,local_29);
  if (param_5 == '\0') {
    AsicDevInfoUpdate(iVar1,local_29[0],iVar1 + 0x794b5b,param_4,1,1);
  }
  else {
    sys_ad_move_mem((void *)(param_2 + 0xc25),param_3,6);
    AsicDevInfoUpdate(iVar1,local_29[0],param_3,param_4,1,1);
  }
  printk("%s : ownmac ID : %d, ownmac addr = %.2x:%.2x:%.2x:%.2x:%.2x:%.2x\n",
         "net_ad_set_device_info",local_29[0],*(undefined1 *)(param_2 + 0xc25),
         *(undefined1 *)(param_2 + 0xc26),*(undefined1 *)(param_2 + 0xc27),
         *(undefined1 *)(param_2 + 0xc28),*(undefined1 *)(param_2 + 0xc29),
         *(undefined1 *)(param_2 + 0xc2a));
  return uVar2;
}

