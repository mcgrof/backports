--- a/net/wireless/util.c
+++ b/net/wireless/util.c
@@ -816,7 +816,7 @@
 		return -EOPNOTSUPP;
 
 	/* if it's part of a bridge, reject changing type to station/ibss */
-	if ((dev->priv_flags & IFF_BRIDGE_PORT) &&
+	if (br_port_exists(dev) &&
 	    (ntype == NL80211_IFTYPE_ADHOC ||
 	     ntype == NL80211_IFTYPE_STATION ||
 	     ntype == NL80211_IFTYPE_P2P_CLIENT))
