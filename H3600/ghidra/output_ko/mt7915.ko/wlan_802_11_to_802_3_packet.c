// module: mt7915.ko
// function: wlan_802_11_to_802_3_packet @ 0x2448a8
// size: 220 bytes
//

void wlan_802_11_to_802_3_packet
               (undefined4 param_1,int param_2,int param_3,undefined4 param_4,int param_5,
               int param_6,int param_7,void *param_8)

{
  void *__dest;
  undefined4 uVar1;
  
  if (param_8 == (void *)0x0) {
    printk(&_LC33,0x2c3);
    dump_stack();
  }
  *(int *)(param_5 + 0xcc) = param_6;
  *(undefined4 *)(param_5 + 0x18) = param_1;
  *(int *)(param_5 + 100) = param_7;
  *(int *)(param_5 + 0xc0) = param_6 + param_7;
  if (param_2 == 1) {
    if (param_3 == 0) {
      uVar1 = 0xe;
    }
    else {
      uVar1 = 0x12;
    }
    skb_push(param_5,uVar1);
    VLAN_8023_Header_Copy(param_3,param_4,param_8,0xe);
    return;
  }
  if (param_2 != 0) {
    return;
  }
  __dest = (void *)skb_push(param_5,0xe);
  memmove(__dest,param_8,0xe);
  return;
}

