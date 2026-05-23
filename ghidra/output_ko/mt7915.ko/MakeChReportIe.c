// module: mt7915.ko
// function: MakeChReportIe @ 0xb4334
// size: 124 bytes
//

void MakeChReportIe(int param_1,int param_2,int *param_3,int param_4)

{
  undefined2 uVar1;
  undefined4 uVar2;
  int local_24 [2];
  
  uVar1 = *(undefined2 *)(param_2 + 0x18);
  local_24[0] = *param_3;
  param_4 = param_4 + local_24[0];
  uVar2 = get_regulatory_class(param_1,*(undefined1 *)(param_2 + 0x1a),uVar1,param_2);
  InsertChannelRepIE(param_1,param_4,local_24,param_1 + 0x794c31,uVar2,0,uVar1,
                     *(undefined1 *)(param_2 + 0xe));
  *param_3 = local_24[0];
  return;
}

