// module: tm.ko
// function: tm_yellow_drop_cfg @ 0x4d490
// size: 264 bytes
//

undefined4 tm_yellow_drop_cfg(int param_1,int param_2,undefined4 param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  if (param_2 != 1) {
    if (param_1 == 1) {
      spa_set_color_mode(0,0);
      DAT_000c4de9 = '\0';
      cVar1 = tm_color_en;
    }
    else {
      iVar3 = 1;
      do {
        iVar2 = iVar3 + 1;
        spa_set_color_mode(iVar3,0);
        iVar3 = iVar2;
      } while (iVar2 != 9);
      tm_color_en = '\0';
      cVar1 = DAT_000c4de9;
    }
    if (cVar1 == '\0') {
      adm_set_color_enable(0);
      red_set_cfg_enable(0,1);
    }
    return 0;
  }
  if (param_1 == 1) {
    spa_set_color_mode(0,param_3);
    DAT_000c4de9 = '\x01';
  }
  else {
    iVar3 = 1;
    do {
      iVar2 = iVar3 + 1;
      spa_set_color_mode(iVar3,param_3);
      iVar3 = iVar2;
    } while (iVar2 != 9);
    tm_color_en = '\x01';
  }
  adm_set_color_enable(1);
  red_set_cfg_enable(1,1);
  return 0;
}

