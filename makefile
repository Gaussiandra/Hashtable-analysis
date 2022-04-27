CXX_flags = -g -O2 -std=c++14 -Wall -Wextra -Weffc++ -Waggressive-loop-optimizations -Wc++0x-compat -Wc++11-compat -Wc++14-compat -Wcast-align -Wcast-qual -Wchar-subscripts -Wconditionally-supported -Wconversion -Wctor-dtor-privacy -Wempty-body -Wfloat-equal -Wformat-nonliteral -Wformat-security -Wformat-signedness -Wformat=2 -Winline -Wlarger-than=8192 -Wlogical-op -Wnon-virtual-dtor -Wopenmp-simd -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstack-usage=8192 -Wstrict-null-sentinel -Wstrict-overflow=2 -Wsuggest-attribute=noreturn -Wsuggest-final-methods -Wsuggest-final-types -Wsuggest-override -Wswitch-default -Wswitch-enum -Wsync-nand -Wundef -Wunreachable-code -Wunused -Wuseless-cast -Wvariadic-macros -Wno-literal-suffix -Wno-missing-field-initializers -Wno-narrowing -Wno-old-style-cast -Wno-varargs -fcheck-new -fsized-deallocation -fstack-protector -fstrict-overflow -flto-odr-type-merging -fno-omit-frame-pointer -fPIE -fsanitize=address -fsanitize=alignment -fsanitize=bool -fsanitize=bounds -fsanitize=enum -fsanitize=float-cast-overflow -fsanitize=float-divide-by-zero -fsanitize=integer-divide-by-zero -fsanitize=leak -fsanitize=nonnull-attribute -fsanitize=null -fsanitize=object-size -fsanitize=return -fsanitize=returns-nonnull-attribute -fsanitize=shift -fsanitize=signed-integer-overflow -fsanitize=undefined -fsanitize=unreachable -fsanitize=vla-bound -fsanitize=vptr -lm -pie
CXX_no_flags = -g -O2

dump_spectrum: spectrum_dumper.out
	./spectrum_dumper.out

spectrum_dumper.out: spectrum_dumper.cpp vector.cpp hashtable.cpp string_list.cpp utils.cpp vector.hpp hashtable.hpp string_list.hpp utils.hpp
	g++ spectrum_dumper.cpp vector.cpp hashtable.cpp string_list.cpp utils.cpp $(CXX_flags) -o spectrum_dumper.out 

plot_spectrum: plotter.py
	python3 plotter.py

benchmark_wo_flags: benchmark_wo_flags.out
	./benchmark_wo_flags.out

benchmark_wo_flags.out: stresser.cpp vector.cpp hashtable.cpp string_list.cpp utils.cpp vector.hpp hashtable.hpp string_list.hpp utils.hpp
	g++ stresser.cpp vector.cpp hashtable.cpp string_list.cpp utils.cpp $(CXX_no_flags) -o benchmark_wo_flags.out

benchmark: benchmark.out
	./benchmark.out

benchmark.out: stresser.cpp vector.cpp hashtable.cpp string_list.cpp utils.cpp vector.hpp hashtable.hpp string_list.hpp utils.hpp
	g++ stresser.cpp vector.cpp hashtable.cpp string_list.cpp utils.cpp $(CXX_flags) -o benchmark.out 