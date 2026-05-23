// module: tm.ko
// function: tm_oam_unmatch_mode_get @ 0x46fec
// size: 152 bytes
//

undefined4 tm_oam_unmatch_mode_get(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 local_c;
  
  iVar1 = greg_get_oam_mode(&local_c);
  if (iVar1 == 0) {
    switch(local_c) {
    case 0:
      *param_1 = 0;
      return 0;
    case 1:
      *param_1 = 1;
      return 0;
    case 2:
      *param_1 = 2;
      return 0;
    case 3:
      uVar2 = 0;
      *param_1 = 3;
      break;
    default:
      uVar2 = 0;
    }
  }
  else {
    printk("tm_oam_unmatch_mode_get fail\n");
    uVar2 = 0xffffffff;
  }
  return uVar2;
}

