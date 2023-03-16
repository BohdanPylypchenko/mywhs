# mywhs

### mywhs - my where is

Small library + command-line utility built on top of it to search (BFS algorithm) files on filesystem.

Library provides both single-threaded and multi-threaded search implementation.

### Supported command line arguments:

-f | --filename : file name to search for. If not specified - file named "mywhs_demo" will be searched.

-r | --start-directory : path to directory to start search in. If not specified - search will be started
from filesystem root ("/").

-m | --multi-threaded : if flag is passed, multi-threaded implementation will run. If flag is NOT passed - 
single-threaded implementation will run.

### Build instructions

1. Clone repository
2. cd in directory
3. create build directory
4. cd build
5. cmake ../
6. make
7. run mywhs_demo application
