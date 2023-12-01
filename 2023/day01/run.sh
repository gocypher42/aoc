filepath=$(pwd)
target="$(basename "$filepath")"

if [ -f dayXX.cpp ] && [ "$target" != "dayXX" ]; then
	if [ -f "$target.cpp" ]; then
		rm "$target.cpp"
	fi
	mv dayXX.cpp "$target.cpp"
fi

if !(cmake -B build);
then
	rm -rf build
	cmake -B build
fi

cmake --build build

echo
./build/bin/$target
