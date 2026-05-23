// module: mt7915.ko
// function: RtmpOSFileOpen @ 0x243cd4
// size: 148 bytes
//

uint RtmpOSFileOpen(undefined4 param_1,int param_2,undefined2 param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0xf01;
  if (param_2 == 0xf01) {
    param_2 = 0;
  }
  else {
    uVar2 = 0xf02;
    if (param_2 == 0xf02) {
      param_2 = 1;
    }
    else {
      uVar2 = 0xf03;
      if (param_2 == 0xf03) {
        param_2 = 0x40;
      }
      else {
        uVar2 = 0xf04;
        if (param_2 == 0xf04) {
          param_2 = 0x200;
        }
      }
    }
  }
  uVar1 = filp_open(param_1,param_2,param_3,uVar2,param_4);
  if ((0xfffff000 < uVar1) && (-1 < DebugLevel)) {
    printk("%s(): Error %ld opening %s\n","RtmpOSFileOpen",-uVar1,param_1);
  }
  return uVar1;
}

