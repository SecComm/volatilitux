Volatilitux is pretty much the equivalent of Volatility for Linux systems.

Volatilitux supports the following architectures for physical memory dumps:
  * ARM
  * x86
  * x86 with PAE enabled

It supports the following commands:
  * pslist: print the list of all process
  * memmap: print the memory map of a process
  * memdmp: dump the addressable memory of a process
  * filelist: print the list of all open files for a given process
  * filedmp: dump an open file

It can easily be extended with new architectures, commands and classes.

Volatilitux automatically detects kernel structure offsets within the memory dump, and can export its current configuration into a XML file.
If it is unable to successfuly detect offsets, you can use the provided Loadable Kernel Module to generate a configuration file.

Volatilitux has been tested with the following machines:
  * Android 2.1
  * Fedora 5 and 8
  * Debian 5
  * CentOS 5
  * Ubuntu 10.10 with and without PAE (some commands may not give proper output, see README file for more details)

Please see this blog post for more details: http://www.segmentationfault.fr/projets/volatilitux-physical-memory-analysis-linux-systems/