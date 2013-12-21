/*
Backports threaded IRQ support

The 2.6.31 kernel introduced threaded IRQ support, in order to
backport threaded IRSs on older kernels we built our own struct
compat_threaded_irq to queue_work() onto it as the kernel thread
will be running the thread in process context as well.

For now each driver's private data structure is modified to add
the their own struct compat_threaded_irq, and that is used by
the backports module to queue_work() onto it. We can likely avoid
having to backport this feature by requiring to modify the private
driver's data structure by relying on an internal worker thread
within the backports module, this should be revised later.
*/

@ threaded_irq @
identifier ret;
expression irq, irq_handler, irq_thread_handler, flags, name;
type T;
T *private;
@@

+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
ret = request_threaded_irq(irq,
			   irq_handler,
			   irq_thread_handler,
			   flags,
			   name,
			   private);
+#else
+ret = compat_request_threaded_irq(&private->irq_compat,
+				   irq,
+				   irq_handler,
+				   irq_thread_handler,
+				   flags,
+				   name,
+				   private);
+#endif

@ sync_irq depends on threaded_irq @
expression irq;
type threaded_irq.T;
T *threaded_irq.private;
@@

+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
synchronize_irq(irq);
+#else
+compat_synchronize_threaded_irq(&private->irq_compat);
+#endif

@ free depends on threaded_irq @
expression irq, dev;
type threaded_irq.T;
T *threaded_irq.private;
@@

+#if LINUX_VERSION_CODE >= KERNEL_VERSION(2,6,31)
free_irq(irq, dev);
+#else
+compat_free_threaded_irq(&private->irq_compat);
+compat_destroy_threaded_irq(&dev->irq_compat);
+#endif

@ modify_private_header depends on threaded_irq @
type threaded_irq.T;
@@

T {
+#if LINUX_VERSION_CODE < KERNEL_VERSION(2,6,31)
+      struct compat_threaded_irq irq_compat;
+#endif
...
};
