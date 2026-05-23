// module: mt7915.ko
// function: MT_ATEDevInfoUpdate @ 0x27d52c
// size: 168 bytes
//

void MT_ATEDevInfoUpdate(int param_1,uint param_2,undefined1 *param_3)

{
  undefined1 uVar1;
  
  uVar1 = *(undefined1 *)(param_1 + 0xa3ae36);
  if (2 < DebugLevel) {
    printk("%s: control_band_idx:%d OwnMacIdx:%d Bssid:%02x:%02x:%02x:%02x:%02x:%02x\n",
           "MT_ATEDevInfoUpdate",uVar1,param_2,*param_3,param_3[1],param_3[2],param_3[3],param_3[4],
           param_3[5]);
  }
  AsicDevInfoUpdate(param_1,param_2 & 0xff,param_3,uVar1,1,1);
  return;
}

