// module: wlan_debug_module.ko
// function: _pktcnt_Extract_parameters.constprop.2 @ 0x12494
// size: 132 bytes
//

void _pktcnt_Extract_parameters_constprop_2
               (char *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  size_t sVar1;
  int iVar2;
  
  sVar1 = strnlen(param_1,10);
  if (sVar1 == 0) {
    return;
  }
  if ((*param_1 == '0') && ((param_1[1] & 0xdfU) == 0x58)) {
    iVar2 = sscanf(param_1,"0x%x",param_2);
    if (iVar2 != 0) {
      return;
    }
    sscanf(param_1,"0X%x",param_2,param_4);
    return;
  }
  sscanf(param_1,"%u",param_2,param_4);
  return;
}

