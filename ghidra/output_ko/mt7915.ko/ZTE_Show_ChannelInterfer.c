// module: mt7915.ko
// function: ZTE_Show_ChannelInterfer @ 0x1578ac
// size: 48 bytes
//

undefined4 ZTE_Show_ChannelInterfer(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    return 0;
  }
  uVar1 = ZTE_Get_ChannelInterfer();
  printk("ChannelInterfer:%d\n",uVar1);
  return 1;
}

