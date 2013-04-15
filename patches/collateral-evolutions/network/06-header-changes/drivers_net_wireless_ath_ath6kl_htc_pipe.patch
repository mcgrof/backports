--- a/drivers/net/wireless/ath/ath6kl/htc_pipe.c
+++ b/drivers/net/wireless/ath/ath6kl/htc_pipe.c
@@ -18,6 +18,10 @@
 #include "debug.h"
 #include "hif-ops.h"
 
+#if (LINUX_VERSION_CODE < KERNEL_VERSION(2,6,29))
+#include <asm/unaligned.h>
+#endif
+
 #define HTC_PACKET_CONTAINER_ALLOCATION 32
 #define HTC_CONTROL_BUFFER_SIZE (HTC_MAX_CTRL_MSG_LEN + HTC_HDR_LENGTH)
 
