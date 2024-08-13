files=$(find . -name '*.h' -or -name '*.hpp' -or -name '*.cpp' -o -name '*.c' -o -name '*.cc' -o -name '*.proto')
for eachfile in $files
do
   clang-format-10 -i -style=file $eachfile
done
