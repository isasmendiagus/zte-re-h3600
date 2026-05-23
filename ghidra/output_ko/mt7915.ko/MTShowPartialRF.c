// module: mt7915.ko
// function: MTShowPartialRF @ 0x1c81ec
// size: 176 bytes
//

undefined4 MTShowPartialRF(int param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  undefined4 local_24;
  
  if ((byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4 != 0) {
    uVar2 = 0;
    uVar1 = param_2;
    do {
      for (; uVar1 <= param_3; uVar1 = uVar1 + 4) {
        MtCmdRFRegAccessRead(param_1,uVar2,uVar1,&local_24);
        if (0 < DebugLevel) {
          printk("%s():%d 0x%04x 0x%08x\n","MTShowPartialRF",uVar2,uVar1,local_24);
        }
      }
      uVar2 = uVar2 + 1;
      uVar1 = param_2;
    } while (uVar2 < (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4);
  }
  return 1;
}

