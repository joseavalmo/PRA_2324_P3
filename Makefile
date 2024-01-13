bin/all: testTableEntry.cpp testHashTable.cpp testBSTree.cpp testBSTreeDict.cpp TableEntry.h HashTable.h BSNode.h BSTree.h BSTreeDict.h
	mkdir -p bin
	g++ -o bin/testTableEntry testTableEntry.cpp
	g++ -o bin/testHashTable testHashTable.cpp
	g++ -c BSNode.h
	g++ -c BSTree.h
	g++ -c BSTreeDict.h
	g++ -o bin/testBSTree testBSTree.cpp
	g++ -o bin/testBSTreeDict testBSTreeDict.cpp
	g++ -o bin/praB praB.cpp

clean:
	rm -r bin
