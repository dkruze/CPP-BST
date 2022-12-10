binaryTree: binaryTree.o
	g++ binaryTree.cpp -o binaryTree

binaryTree: binaryTree.cpp
	g++ -c binaryTree.cpp

clean: 
	rm *.o
	rm binaryTree

run:
	./a.out