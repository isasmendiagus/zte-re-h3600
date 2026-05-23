// module: tm.ko
// function: claDebugDelFastRule @ 0x78480
// size: 324 bytes
//

int claDebugDelFastRule(char *param_1)

{
  int iVar1;
  undefined1 local_100 [4];
  undefined1 local_fc [4];
  undefined1 local_f8 [4];
  int local_f4;
  int local_f0;
  int local_ec;
  uint local_e8;
  int local_e4;
  int local_e0;
  int local_dc;
  uint local_d8;
  undefined1 auStack_d4 [20];
  undefined1 auStack_c0 [4];
  uint local_bc [4];
  uint local_ac;
  
  memset(&local_f4,0,0x10);
  memset(&local_e4,0,0x10);
  memset(local_100,0,0xc);
  __memzero(auStack_d4,0x14);
  __memzero(auStack_c0,0xa0);
  sscanf(param_1,"%d %d %d %d %d %d %d %d %d %d %d",local_100,local_fc,local_f8,&local_f4,&local_f0,
         &local_ec,&local_e8,&local_e4,&local_e0,&local_dc,&local_d8);
  local_bc[0] = local_f0 << 0x10 | local_f4 << 0x18 | local_e8 | local_ec << 8;
  local_ac = local_e0 << 0x10 | local_e4 << 0x18 | local_d8 | local_dc << 8;
  iVar1 = zte_api_fast_l3_session_del(local_bc,auStack_d4);
  if (iVar1 != 0) {
    printk("[tmtst]delfastrule fail, error code %d!\n",iVar1);
  }
  return iVar1;
}

