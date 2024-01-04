To build:
- Edit the CONFIG file:
 - SOFTWARE_INC and SOFTWARE_LIB should point to the directories where the include files and, respectively, the libraries of GMP and NTL are installed
 - update the CFLAGS to whatever works best for the type of machine you are building this on.  I find it best to copy the ones that GMP selects automatically when building it.
- make appl, to build the libarary and the applications in appl
- doxygen ANTLdoc-config, to build the documentation in doc