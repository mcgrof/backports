--- a/net/mac80211/key.c
+++ b/net/mac80211/key.c
@@ -24,6 +24,9 @@
 #include "aes_ccm.h"
 #include "aes_cmac.h"
 
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29))
+#include <asm/unaligned.h>
+#endif
 
 /**
  * DOC: Key handling basics
