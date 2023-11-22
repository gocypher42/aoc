filepath=$(pwd)
target="$(basename "$filepath")"

if [ -f dayXX.cpp ] && [ "$target" != "dayXX" ]; then
	rm "$target.cpp"
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
