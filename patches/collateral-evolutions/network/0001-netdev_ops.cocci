@@
struct net_device *dev;
struct net_device_ops ops;
@@
-dev->netdev_ops = &ops;
+netdev_attach_ops(dev, &ops);
