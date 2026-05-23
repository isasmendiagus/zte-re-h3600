// module: mt7915.ko
// function: MtPwrLimitSimilarCheck @ 0x15139c
// size: 488 bytes
//

undefined1
MtPwrLimitSimilarCheck
          (int param_1,int param_2,int param_3,undefined1 *param_4,byte param_5,byte param_6)

{
  byte bVar1;
  int iVar2;
  byte *pbVar3;
  char *pcVar4;
  uint uVar5;
  uint uVar6;
  char local_2a [2];
  byte *local_28;
  int local_24;
  
  local_28 = (byte *)0x0;
  local_24 = 0;
  uVar5 = (uint)param_6;
  iVar2 = hc_get_chip_cap(*(undefined4 *)(param_1 + 0xa797a0));
  local_2a[0] = *(char *)(iVar2 + 0x1fa);
  local_2a[1] = *(undefined1 *)(iVar2 + 0x1fe);
  if (param_2 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: null pointer for pointer to power limit table start channel for check !!\n",
             "MtPwrLimitSimilarCheck");
      return 1;
    }
  }
  else if (param_3 == 0) {
    if (-1 < DebugLevel) {
      printk("%s: null pointer for pointer to power limit table current channel for check !!\n",
             "MtPwrLimitSimilarCheck");
      return 1;
    }
  }
  else {
    MtPwrGetPwrLimitInstance(param_1,uVar5,1,&local_28);
    if ((local_28 != (byte *)0x0) &&
       (MtPwrGetPwrLimitInstance(param_1,uVar5,4,&local_24), local_24 != 0)) {
      *param_4 = 1;
      if (local_2a[uVar5] == '\0') {
        return 0;
      }
      pcVar4 = (char *)(local_24 + -1);
      uVar6 = 0;
      pbVar3 = local_28 + (byte)(local_2a[uVar5] - 1) + 1;
      do {
        pcVar4 = pcVar4 + 1;
        bVar1 = *local_28;
        if ((((int)*pcVar4 & param_5 + 1) != 0) && (0 < (char)bVar1)) {
          if (*(char *)(param_2 + uVar6) != *(char *)(param_3 + uVar6)) {
LAB_00151508:
            *param_4 = 0;
            return 0;
          }
          uVar5 = 0;
          while( true ) {
            uVar5 = uVar5 + 1 & 0xff;
            if ((int)(char)bVar1 <= (int)uVar5) break;
            if (*(char *)(param_2 + uVar6 + uVar5) != *(char *)(param_3 + uVar6 + uVar5))
            goto LAB_00151508;
          }
        }
        local_28 = local_28 + 1;
        uVar6 = uVar6 + bVar1 & 0xff;
        if (local_28 == pbVar3) {
          return 0;
        }
      } while( true );
    }
    if (-1 < DebugLevel) {
      printk("%s: null pointer for parameter related to power limit table proc similar check !!\n",
             "MtPwrLimitSimilarCheck");
    }
  }
  return 1;
}

