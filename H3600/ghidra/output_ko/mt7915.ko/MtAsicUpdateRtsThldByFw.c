// module: mt7915.ko
// function: MtAsicUpdateRtsThldByFw @ 0x199540
// size: 148 bytes
//

void MtAsicUpdateRtsThldByFw(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined1 local_24;
  undefined1 local_23;
  undefined4 local_20;
  undefined4 local_1c;
  
  local_23 = HcGetBandByWdev(param_2);
  if ((((*(uint *)("Get_RBIST_IQ_Data_Proc" + param_1 + 0xc) & 0xffff) != 0x7615) ||
      (0xf < (byte)"Get_RBIST_IQ_Data_Proc"[param_1 + 0x10])) ||
     (*(char *)(param_1 + 0x79504d) == '\0')) {
    os_zero_mem(&local_24,0xc);
    local_24 = 1;
    local_20 = param_4;
    local_1c = param_3;
    MtCmdUpdateProtect(param_1,&local_24);
  }
  return;
}

