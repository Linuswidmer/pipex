valgrind ./pipex empty "grep h" "wc -w" outfile && cat outfile
valgrind ./pipex does_not_exist "grep h" "wc -w" outfile && cat outfile
valgrind ./pipex infile "grep h" "wc -w" does_not_exist && cat does_not_exist
valgrind ./pipex infile "grep h" "wc -w" outfile && cat outfile
valgrind ./pipex infile "bla" "wc -w" outfile && cat outfile
valgrind ./pipex infile "grep h" "bla" outfile && cat outfile
valgrind ./pipex infile "grep h" "wc -w" outfile and more args && cat outfile
valgrind ./pipex "" "" "" ""
valgrind ./pipex infile "grep h -v" "wc -w" outfile && cat outfile
valgrind ./pipex infile "grep h -bla" "wc -w" outfile && cat outfile
valgrind ./pipex a "grep a" "wc -w" outfile && cat outfile
valgrind ./pipex

rm does_not_exist
