// module: mt7915.ko
// function: HQA_GetBandMode @ 0x2766bc
// size: 252 bytes
//

undefined4 HQA_GetBandMode(int param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  undefined4 uVar2;
  int local_20;
  int local_1c [2];
  
  cVar1 = *(char *)(param_1 + 0x79504d);
  local_20 = param_3 + 0xc;
  local_1c[0] = 0;
  FUN_00276034(1,4,&local_20,local_1c);
  if (cVar1 == '\0') {
    if (local_1c[0] == 1) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x3000000;
    }
  }
  else if ((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) == 0x7626) {
    if (local_1c[0] == 0) {
      uVar2 = 0x1000000;
    }
    else {
      uVar2 = 0x2000000;
    }
  }
  else if (local_1c[0] == 0) {
    uVar2 = 0x3000000;
  }
  else {
    uVar2 = 0x2000000;
  }
  if (0 < DebugLevel) {
    printk("%s: is_dbdc:%x, band_mode:%x, band_idx:%x\n","HQA_GetBandMode",cVar1);
  }
  *(undefined4 *)(param_3 + 0xe) = uVar2;
  FUN_0026cdd0(param_3,param_2,6,0);
  return 0;
}

