========================================================================
    APPLICATION : EzLog Project Overview
========================================================================

EzLog demonstrates how to easily create a fastjob tool. This particular tool 
allows textual messages to be time-stamped and added to / listed from either
the `pwd`, or to an .ezlog file in the parent's tree or in the default 
program (".EXE") folder.

EXAMPLES
========

For example, when given the following folder / file combination:

/bin
     File: EzLog.EXE
     File: .ezlog
/usr
/usr/code
/usr/code/MyProjectA
/usr/code/MyProjectB/BLA
/usr/code/MyProjectB/FOO/BAR

-If the present working folder is BAR, then typing:

   EzLog = My new message

-Would put the message into /bin/.ezlog, whereas if you had
an .ezlog somewhere in the parental tree, say at:

/usr/code
     File: .ezlog

-Then the same command would be appended the message to that log file, 
instead. Simple, eh?

... But if you wanted to create a NEW .ezlog, say in our example for 
perpetual re-use in the BAR Folder, then typing:

   EzLog . My new message

-Would create AND append your message to /usr/code/MyProjectB/FOO/BAR/.ezlog

Finally, note that you can use the dollar operator ($) to log to the log file 
located in the EzLog.EXE home directory each and every time. This option allows 
you to access the default logging file for your installation reguardless of what 
you have in the default directory OR its parental tree.

CONCLUSION
==========

This 'noj is very useful when you are generating comments on an entire 
TREE of files, folders, and / or directories... Or just want to keep tabs on
what you have done in every single folder in a given tree or installation.


Once installed on your command path, type EzLog for help. Or see EzLog::Usage() 
for more information.


CAVEATS
=======

Logging to the root directory (D:\) on WIN32 is only supported via the 
dot (.) operator.

Explicit file naming is not supported from the command line at this time.

  -
 ---
-----
NOTES
-----
 ---
  -

NOTE THAT LOG FILE USAGE IS OPTOMISTIC - NO LOG FILE CONTENTION LOGIC IS USED 
AT THIS TIME! 



