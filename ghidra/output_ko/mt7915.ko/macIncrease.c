// module: mt7915.ko
// function: macIncrease @ 0xf03d4
// size: 144 bytes
//

void macIncrease(int param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  byte bVar4;
  undefined2 local_1e;
  undefined2 local_1c;
  undefined2 local_1a;
  
  puVar3 = &local_1e;
  local_1e = 0;
  local_1c = 0;
  local_1a = 0;
  iVar1 = param_1;
  do {
    iVar2 = iVar1 + 3;
    AtoH(iVar1,puVar3,1);
    puVar3 = (undefined2 *)((int)puVar3 + 1);
    iVar1 = iVar2;
  } while (iVar2 != param_1 + 0x12);
  bVar4 = local_1a._1_1_ + 1;
  local_1a = CONCAT11(bVar4,(byte)local_1a);
  sprintf(param_2,"%02x:%02x:%02x:%02x:%02x:%02x",(uint)(byte)local_1e,(uint)local_1e._1_1_,
          (uint)(byte)local_1c,(uint)local_1c._1_1_,(uint)(byte)local_1a,(uint)bVar4);
  return;
}

