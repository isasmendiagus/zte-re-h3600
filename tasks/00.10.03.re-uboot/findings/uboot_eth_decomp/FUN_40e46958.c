/* ===== FUN FUN_40e46958 @ 40e46958 =====
 * callers: 40e21ebc:FUN_40e21ebc, 40e2ffa4:FUN_40e2ffa4, 40e37fcc:FUN_40e37fcc, 40e38248:FUN_40e38248, 40e3b6f8:FUN_40e3b6f8, 40e3bfa4:FUN_40e3bfa4, 40e3ddd8:FUN_40e3ddd8, 40e408a4:FUN_40e408a4
 * callees: 40e220e8:FUN_40e220e8, 40e2a154:FUN_40e2a154, 40e2a200:FUN_40e2a200, 40e45a90:FUN_40e45a90
 */


void FUN_40e46958(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uStack_c;
  undefined4 uStack_8;
  undefined4 uStack_4;
  
  puVar1 = &uStack_c;
  uStack_c = param_2;
  uStack_8 = param_3;
  uStack_4 = param_4;
  FUN_40e2a200(param_1);
  FUN_40e2a154(10);
  FUN_40e45a90(DAT_40e46998/*=0x000186a0*/);
  FUN_40e220e8(0,0,0,0,param_1,puVar1,param_3);
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}
