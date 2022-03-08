# Clear win32 Clip Board

Empty the clipboard history using c++ and win32 api

- Gets PID for the clipboard service and kills it. 


Once executed, ClipboardClear immediately empties the clipboard using [Clipboard.Clear()](https://docs.microsoft.com/en-us/dotnet/api/system.windows.forms.clipboard.clear?view=netframework-4.8) and then closes. This software has no GUI.
