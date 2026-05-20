// module: mt7915.ko
// function: MtAsicUpdateBASessionOffloadByFw @ 0x198afc
// size: 328 bytes
//

undefined4
MtAsicUpdateBASessionOffloadByFw
          (undefined4 param_1,uint param_2,uint param_3,int param_4,undefined4 param_5,
          undefined4 param_6)

{
  undefined4 uVar1;
  undefined4 local_44;
  undefined4 local_40;
  uint local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  byte bStack_a;
  char local_6;
  
  local_44 = 0;
  bStack_a = (byte)(param_2 >> 0x10);
  local_40 = 0;
  local_3c = 0;
  local_38 = 0;
  local_34 = 0;
  local_30 = 0;
  local_2c = 0;
  if (bStack_a < 8) {
    local_40 = (uint)CONCAT11((char)param_4,bStack_a);
    local_44 = 0x1c0008;
    local_6 = (char)(param_3 >> 0x10);
    if (param_4 != 2) {
      if (local_6 != '\0') {
        local_3c = (uint)CONCAT12(1,param_6._2_2_);
        local_38 = param_3 & 0xffff;
      }
      uVar1 = CmdExtWtblUpdate(param_1,param_2 & 0xffff,2,&local_44,0x1c);
      return uVar1;
    }
    if (local_6 != '\0') {
      local_30 = param_3 & 0xff000000;
      os_move_mem((void *)((int)&local_38 + 2),&param_5,6);
      local_30._0_3_ = CONCAT12(1,(ushort)bStack_a);
      uVar1 = CmdExtWtblUpdate(param_1,param_2 & 0xffff,2,&local_44,0x1c);
      return uVar1;
    }
  }
  else if (-1 < DebugLevel) {
    printk("%s: unknown tid(%d)\n","MtAsicUpdateBASessionOffloadByFw",bStack_a);
  }
  return 1;
}

