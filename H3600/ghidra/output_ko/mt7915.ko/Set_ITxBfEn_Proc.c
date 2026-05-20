// module: mt7915.ko
// function: Set_ITxBfEn_Proc @ 0xe6d18
// size: 432 bytes
//

undefined4 Set_ITxBfEn_Proc(int param_1,undefined4 param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  ushort uVar6;
  undefined4 uVar7;
  undefined1 local_58;
  byte local_57;
  ushort local_56;
  byte local_54;
  byte local_53;
  undefined1 local_52;
  undefined1 local_51;
  undefined1 local_50;
  ushort local_4e;
  int local_4c;
  int local_48;
  int local_44;
  int local_40;
  undefined1 local_2c;
  undefined1 local_2b;
  
  uVar1 = os_str_tol(param_2,0,10);
  uVar1 = uVar1 & 0xff;
  if (1 < uVar1) {
    return 0;
  }
  uVar6 = 0;
  uVar7 = 0;
  while( true ) {
    uVar5 = (uint)uVar6;
    uVar2 = HcGetMaxStaNum(param_1);
    iVar4 = uVar5 * 0x14c0 + param_1;
    if (uVar2 <= uVar5) break;
    if (*(int *)(iVar4 + 0xa1d20) != 0) {
      iVar4 = *(int *)(iVar4 + 0xa1d28);
      local_54 = (byte)"SetPartProfileParameters"[param_1 + 0x18] >> 4;
      local_53 = (byte)(((uint)(byte)"SetPartProfileParameters"[param_1 + 0x18] << 0x1c) >> 0x1c);
      if (*(char *)(param_1 + 0x79504d) != '\0') {
        iVar3 = HcGetBandByWdev(iVar4);
        if (iVar3 == 0) {
          local_54 = "SetPartProfileParameters"[param_1 + 0x1a];
          local_53 = "SetPartProfileParameters"[param_1 + 0x1b];
        }
        else {
          local_54 = "rtmp_read_vow_parms_from_file"[param_1];
          local_53 = "rtmp_read_vow_parms_from_file"[param_1 + 1];
        }
      }
      local_4c = *(ushort *)("Get_System_CapNode_Info" + param_1 + 0x10) * uVar5 +
                 *(int *)("Get_System_CenFreq_Info" + param_1);
      local_48 = *(ushort *)("Get_System_CapNode_Info" + param_1 + 0x12) * uVar5 +
                 *(int *)("Get_System_CenFreq_Info" + param_1 + 4);
      local_2b = *(undefined1 *)(param_1 + 0x7959a5);
      local_51 = (undefined1)uVar1;
      local_56 = (ushort)*(byte *)(iVar4 + 0x1a);
      local_2c = *(undefined1 *)(param_1 + 0x7959a4);
      local_58 = (undefined1)*(undefined2 *)(iVar4 + 0x18);
      local_52 = 0;
      local_50 = 2;
      uVar2 = (uint)*(ushort *)(uVar5 * 0x14c0 + param_1 + 0xa1ddc) << 0x17;
      local_57 = (byte)(uVar2 >> 0x1e);
      local_4e = uVar6;
      local_44 = param_1 + 0x79563d;
      local_40 = param_1 + 0x795960;
      uVar7 = AsicTxBfEnCondProc(param_1,&local_58,2,uVar2 >> 0x1e,uVar1);
    }
    uVar6 = uVar6 + 1;
  }
  return uVar7;
}

