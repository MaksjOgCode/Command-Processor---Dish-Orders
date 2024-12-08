# Command Processor
----------------
## Error Codes:
----------------
### CPMENU CATEGORY:
**[CODE CPMENU-00]**

*If the file is not open, the std::unexpected error is returned with a message that the file failed to open.*

**[CODE CPMENU-01]**

*In this error, exceptions of the std::ios_base::failure type are intercepted, and the std::unexpected error is returned with an I/O error message.*

**[CODE CPMENU-02]**

*A file with that name already exists. When creating a new file in the ".cpmenu" format, you need to specify a unique file name.*

**[CODE CPMENU-11]**

*Only the cpmenu format is supported: [OR] The file has no name: [OR] The file path is empty*

**[CODE CPMENU-12]**

*Error opening the [.cpmenu] file - try to recreate the object*

**[CODE CPMENU-13]**

*You cannot close a file that has not been opened*

**[CODE CPMENU-14]**

*You cannot read the file that has not been opened*

----------------

[ENG]
Documentation in development



[RU]
Документация в разработке
