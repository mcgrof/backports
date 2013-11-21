@@
expression dev;
expression ops;
@@
-dev->netdev_ops = ops;
+netdev_attach_ops(dev, ops);
