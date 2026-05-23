// module: mt7915.ko
// function: WPAInsertRSNIE @ 0x11cdb0
// size: 348 bytes
//

void WPAInsertRSNIE(int param_1,int *param_2,int param_3,int param_4,undefined4 param_5,byte param_6
                   )

{
  int iVar1;
  char cVar2;
  undefined4 uVar3;
  char local_28;
  char local_27;
  ushort local_26;
  int local_24 [2];
  
  local_24[0] = 0;
  local_26 = 0;
  local_27 = '\0';
  if ((param_6 == 0) || ((param_6 & 0xf) != 0)) {
    if (DebugLevel < 3) {
      cVar2 = '\0';
    }
    else {
      printk("%s : no PMKID-List included(%d).\n","WPAInsertRSNIE",param_6);
      cVar2 = '\0';
    }
  }
  else {
    local_26 = (ushort)(param_6 >> 4);
    cVar2 = param_6 + 2;
  }
  if (param_4 != 0) {
    local_28 = -0x23;
    local_27 = (char)param_4;
    iVar1 = memcmp((void *)(param_3 + 2),&OUI_WPA2_CIPHER,3);
    if (iVar1 == 0) {
      local_27 = cVar2 + (char)param_4;
      local_28 = '0';
    }
    uVar3 = 0xffffffff;
    MakeOutgoingFrame(param_1,local_24,1,&local_28,1,&local_27,param_4,param_3,0xffffffff);
    *param_2 = *param_2 + local_24[0];
    if (local_28 == '0' && cVar2 != '\0') {
      MakeOutgoingFrame(param_1 + local_24[0],local_24,2,&local_26,param_6,param_5,0xffffffff,
                        param_3,uVar3);
      *param_2 = *param_2 + local_24[0];
    }
  }
  return;
}

