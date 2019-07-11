# DirectoryWalker
## What does it do 
DirectoryWalker can iterate over directories and files straightly or recursively (2 types for now) also it allows to change some files' properties on fly (for now Name only). So far it can send information using different methods (file,stdout,Unix domain socket for now).

## How to build

### Requirements
CMake must be installed to build it >=3.10
gcc/g++ >=8

### Building
Go to the root directory and run : 
```bash
./build.sh
```
For now DirectoryWalker bin file is located at ./DirectoryWalker/DirectoryWalker.
So you can easily run it just calling : 
 ```bash
./DirectoryWalker/DirectoryWalker
```

## How to use :) (will be removed when i add help to bin)
Straight iteration
 ```bash
./DirectoryWalker
```
Iterate straightly specified folder
```bash
./DirectoryWalker ./
```
Iterate specified folder
* r - recursively
* s - straightly
```bash
./DirectoryWalker ./ [r|s]
```
Iterate specified folder and write output :
* f - to file (./DirectoryWalker.txt)
* u - to unix domain socket (/tmp/directorywalker.socket)
* s - standart output
```bash
./DirectoryWalker ./ [r|s] [f|s|u]
```
Iterate specified folder, write output to specified destination and change file name : 
* Name.Replace - replaces first argument with second in a file name
* Name.Append - just inserts specified test at the end of a file name
```bash
./DirectoryWalker ./ [r|s] [f|s|u] [Name.Replace|Name.Append] args...
```
Iterate recursively over current directory, redirect all info to file.
Append **.old** to the file name and replace all **tmp** entries with **t_**
```bash
./DirectoryWalker ./ r f Name.Append .old Name.Replace tmp t_
```
#### The real project purpose - practicing design patterns

List of used patterns in this project opens my implementation of the iterator pattern applied to directories. For now there are only 2 examples (straight and depth). This pattern is obviously taken to traverse through files. So it obviously gives an opportunity to "iterate" over the directory.The next one is Strategy pattern. In this project it used with a Factory method and kind of an Adaptor pattern. Strategy allows consumer to replace an implementation in runtime. So, in this context it chooses between writing data to UDS( unix domain socket), file or just to standard output. Adapter and Factory method help to create specific object which will be passed further. Adapter converts command line arguments into the appropriate enum type of Writable interface. Then factory method consumes passed enum and decides which concrete type of object will be created.

