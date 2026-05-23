// module: mt7915.ko
// function: MtCmdThermoCal @ 0x1b0d60
// size: 472 bytes
//

undefined4
MtCmdThermoCal(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,byte param_5,
              byte param_6,char param_7,char param_8)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined1 local_3c;
  undefined1 local_3b;
  undefined1 local_3a;
  undefined1 local_39;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined2 local_34;
  undefined1 local_32;
  undefined2 local_30;
  undefined1 local_2e;
  undefined2 local_2c;
  undefined1 local_2a;
  
  uVar3 = (uint)param_6;
  uVar2 = (uint)param_5;
  iVar4 = (int)param_7;
  iVar5 = (int)param_8;
  os_zero_mem(&local_3c,0x14);
  if ((2 < DebugLevel) &&
     (uVar7 = param_4,
     printk("%s: IsEnable = %d, SourceMode = %d, RFDiffTemp = %d\n","MtCmdThermoCal",param_2,param_3
            ,param_4), 2 < DebugLevel)) {
    printk("%s: sizeof(Thermo) = %lu\n","MtCmdThermoCal",0x14,DebugLevel,uVar7);
  }
  iVar1 = AndesAllocCmdMsg(param_1,0x14);
  if (iVar1 == 0) {
    uVar7 = 3;
  }
  else {
    AndesInitCmdMsg(iVar1,0x12ed0000,0x8000f,0,0,EventExtCmdResult,uVar2,uVar3,iVar4,iVar5);
    iVar6 = *(int *)("Set_IRR_TTGOnOff" + param_1 + 4);
    local_2e = *(undefined1 *)(iVar6 + 0x54);
    local_3a = (undefined1)param_4;
    local_39 = (undefined1)uVar2;
    local_3b = (undefined1)param_3;
    local_32 = *(undefined1 *)(iVar6 + 0x53);
    local_38 = (undefined1)uVar3;
    local_2a = *(undefined1 *)(iVar6 + 0x55);
    local_30 = 0x54;
    local_37 = (undefined1)iVar4;
    local_2c = 0x55;
    local_36 = (undefined1)iVar5;
    local_3c = (undefined1)param_2;
    local_34 = 0x53;
    AndesAppendCmdMsg(iVar1,&local_3c,0x14);
    uVar7 = chip_cmd_tx(param_1,iVar1);
  }
  if (3 < DebugLevel) {
    printk("%s:(ret = %d)\n","MtCmdThermoCal",uVar7);
  }
  return uVar7;
}

