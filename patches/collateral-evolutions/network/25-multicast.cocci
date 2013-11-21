@@
identifier ha;
expression netdev;
iterator name netdev_for_each_mc_addr;
@@
 netdev_for_each_mc_addr(ha, netdev) {
 <...
-ha->addr
+mc_addr(ha)
 ...>
 }
