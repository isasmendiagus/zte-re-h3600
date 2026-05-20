// module: mt7915.ko
// function: wdev_init @ 0x14dbe4
// size: 140 bytes
//

undefined4
wdev_init(undefined4 param_1,undefined4 *param_2,int param_3,undefined4 param_4,undefined1 param_5,
         undefined4 param_6,undefined4 param_7)

{
  int iVar1;
  
  *(undefined1 *)((int)param_2 + 0xe) = param_5;
  param_2[5] = param_3;
  *param_2 = param_4;
  param_2[1] = param_6;
  param_2[2] = param_7;
  *(undefined2 *)(param_2 + 4) = 0xffff;
  param_2[0x2c6] = 0;
  *(undefined1 *)(param_2 + 0x2c7) = 0;
  param_2[0x223] = 1;
  iVar1 = wdev_idx_reg();
  init_vie_ctrl(param_2);
  if (iVar1 < 0) {
    return 0;
  }
  if (param_3 != 0x100) {
    hc_obj_init(param_2,iVar1);
    return 1;
  }
  return 1;
}

