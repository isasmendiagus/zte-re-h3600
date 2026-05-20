// module: mt7915.ko
// function: mt_op_set_ru_aid @ 0x2592c4
// size: 156 bytes
//

undefined4 mt_op_set_ru_aid(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_5c;
  undefined1 local_5b;
  undefined1 local_59;
  undefined4 local_58;
  undefined2 local_54;
  
  iVar1 = RtmpOsGetNetDevPriv(*(undefined4 *)(param_1 + 4));
  if (iVar1 == 0) {
    uVar2 = 0x503;
  }
  else {
    sys_ad_zero_mem(&local_5c,0x4c);
    local_59 = 0xf;
    local_5c = 1;
    local_5b = 0x1e;
    local_54 = (undefined2)param_3;
    local_58 = param_2;
    printk("%s: Set to decode MU accodring to AID:%d\n","mt_op_set_ru_aid",param_3);
    printk("\t\t(%d means disable)\n",0xf800);
    iVar1 = MtCmdATETest(iVar1,&local_5c);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 0x501;
    }
  }
  return uVar2;
}

