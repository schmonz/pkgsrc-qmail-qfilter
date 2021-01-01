$NetBSD: patch-qmail-qfilter.c,v 1.3 2021/01/01 15:07:59 schmonz Exp $

Apply patch (submitted upstream) to set QMAILPPID for filters to
know grandparent PID.

With this change, my homegrown badrcptto-alike filter can log
rejections in the same format as Paul Jarc's realrcptto, thereby
allowing me to correlate each rejection with a qmail-smtpd session.

Also remove unneeded bglibs dependency.

--- qmail-qfilter.c.orig	2005-08-12 23:40:51.000000000 +0000
+++ qmail-qfilter.c
@@ -15,7 +15,6 @@
  * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
  */
 
-#include <sysdeps.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
@@ -332,6 +331,8 @@ int main(int argc, char* argv[])
   if ((qqargv[0] = getenv("QQF_QMAILQUEUE")) == 0)
     qqargv[0] = QMAIL_QUEUE;
 
+  mysetenvu("QMAILPPID", getppid());
+
   copy_fd(0, 0, &msg_len);
   copy_fd(1, ENVIN, &env_len);
   parse_envelope();
