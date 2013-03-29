--- a/drivers/net/wireless/iwlwifi/iwl-debug.c
+++ b/drivers/net/wireless/iwlwifi/iwl-debug.c
@@ -76,13 +76,16 @@
 	struct va_format vaf = {				\
 		.fmt = fmt,					\
 	};							\
-	va_list args;						\
+	va_list args1, args2;					\
 								\
-	va_start(args, fmt);					\
-	vaf.va = &args;						\
+	va_start(args1, fmt);					\
+	va_copy(args2, args1);					\
+	vaf.va = &args2;					\
 	dev_ ##fn(dev, "%pV", &vaf);				\
+	va_end(args2);						\
+	vaf.va = &args1;					\
 	trace_iwlwifi_ ##fn(&vaf);				\
-	va_end(args);						\
+	va_end(args1);						\
 }
 
 __iwl_fn(warn)
@@ -101,13 +104,18 @@
 	va_list args;
 
 	va_start(args, fmt);
-	vaf.va = &args;
 	if (!trace_only) {
+		va_list args2;
+
+		va_copy(args2, args);
+		vaf.va = &args2;
 		if (rfkill_prefix)
 			dev_err(dev, "(RFKILL) %pV", &vaf);
 		else
 			dev_err(dev, "%pV", &vaf);
+		va_end(args2);
 	}
+	vaf.va = &args;
 	trace_iwlwifi_err(&vaf);
 	va_end(args);
 }
@@ -124,13 +132,19 @@
 	va_list args;
 
 	va_start(args, fmt);
-	vaf.va = &args;
 #ifdef CONFIG_IWLWIFI_DEBUG
 	if (iwl_have_debug_level(level) &&
-	    (!limit || net_ratelimit()))
+	    (!limit || net_ratelimit())) {
+		va_list args2;
+
+		va_copy(args2, args);
+		vaf.va = &args2;
 		dev_dbg(dev, "%c %s %pV", in_interrupt() ? 'I' : 'U',
 			function, &vaf);
+		va_end(args2);
+	}
 #endif
+	vaf.va = &args;
 	trace_iwlwifi_dbg(level, in_interrupt(), function, &vaf);
 	va_end(args);
 }
