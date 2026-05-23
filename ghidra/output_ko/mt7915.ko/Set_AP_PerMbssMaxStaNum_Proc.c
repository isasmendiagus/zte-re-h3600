// module: mt7915.ko
// function: Set_AP_PerMbssMaxStaNum_Proc @ 0x3ef88
// size: 16 bytes
//

void Set_AP_PerMbssMaxStaNum_Proc(int *param_1,undefined4 param_2)

{
  ApCfg_Set_PerMbssMaxStaNum_Proc(param_1,*(undefined4 *)(*param_1 + 0x3c),param_2);
  return;
}

