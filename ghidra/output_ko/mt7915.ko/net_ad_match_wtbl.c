// module: mt7915.ko
// function: net_ad_match_wtbl @ 0x25c240
// size: 56 bytes
//

undefined4 net_ad_match_wtbl(int param_1,uint param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    printk("(%s)Invalid virtual wtbl!\n","net_ad_match_wtbl",param_3,param_4,param_4);
    return 0x607;
  }
  if (*(ushort *)(param_1 + 0xe0) == param_2) {
    uVar1 = 0;
  }
  else {
    uVar1 = 0x600;
  }
  return uVar1;
}

