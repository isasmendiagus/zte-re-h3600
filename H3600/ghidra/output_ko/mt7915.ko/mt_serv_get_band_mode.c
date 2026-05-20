// module: mt7915.ko
// function: mt_serv_get_band_mode @ 0x251fbc
// size: 180 bytes
//

undefined4 mt_serv_get_band_mode(int *param_1)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  
  cVar1 = (char)param_1[0x133];
  if ((char)param_1[0x7d1] == '\0') {
    iVar4 = *param_1;
    if (*(char *)(iVar4 + 0x34) == '\0') {
      uVar3 = 0;
      uVar2 = 0;
      if (cVar1 == '\x01') goto LAB_00252068;
      goto LAB_00251ff4;
    }
    if (cVar1 == '\0') {
      uVar5 = 1;
    }
    else {
      uVar5 = 2;
    }
    uVar3 = 0;
  }
  else {
    uVar3 = (**(code **)(param_1[0x7c4] + 200))(*param_1,param_1 + 0x131);
    if ((cVar1 != '\0') && (param_1[0x131] != 2)) {
LAB_00252068:
      uVar5 = 0;
      goto LAB_00252004;
    }
    iVar4 = *param_1;
    uVar2 = uVar3;
LAB_00251ff4:
    uVar3 = uVar2;
    uVar5 = 3;
  }
  if (*(char *)(iVar4 + 0x72) != '\0') {
    uVar5 = uVar5 | 4;
  }
LAB_00252004:
  printk("%s: band_type=%u\n","mt_serv_get_band_mode",uVar5);
  param_1[0x132] = uVar5;
  return uVar3;
}

