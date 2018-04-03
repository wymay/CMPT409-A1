FleaCircus
- Data Structure:
Use adjacent list to implement a tree representing which two leaves or forks are connected. (vector<vector<int>>)
- Algorithm:
Use DFS to search the tree to find the unique path from source to destination.
Use a vector to store the path.
Use a vector to record whether the leaf/fork has been visited or not.
If the unique path contains odd number of leaves, the two fleas will meet at the middle of the path.
If the unique path contains even number of leaves, the two fleas will jump forever at the middle two leaves of the path.

PokerHands
we use 2 different algorithm to solve this problem.
1. we use 64 bit integer to store a hand of cards. first 10 bits are used to store the type of hands, and remaining bits are for the exact hand. One bit represent whether the hand contains the specific card, or is a specific type.
2. we implement 9 functions to detect whether a hand is a specified type. Also, we return a value for each function to compare two hands of the same type.
we pass all debug cases in uva, but we can't pass the online judge because the input contains two same cards in one hand. The 64bit data structure fails to store this kind of hand. We believe our program is correct. We implement the second algorithm to pass online judge, and we put the first program in the bottom of the submited cpp file.
The second algorithm is the following:
1. we sort a hand according to card value
2. we detect whether a hand is flush or straight. if both, we return type 9
3. we count how many time a value appear from '2' to 'A' 
4. if 4 same value appears, we return type 8 with the value. other types are similarly processed
5. if within the same type, several cards value needs to be compared, we compressed them with radix 13

CheckTheCheck
- Data Structure:
	Using matrix board[8][8] to store the every chess info. And also using four ints to record the King info.

- Algorithm:
	For loop to check every board[i][j]. And for diffent types of chess, check whether if it is check the King. If it is then using checkNoJump function to check weather this chess and the king have some other chess between them. If yes, then King will not be checked. If no, then King is checked and jump out of the loop.

- Inhancement:
	After writing this method, I find out that if I just using king to check whether 8 directions have other chess which not jumped is checking itself. It may save some times.

ErdosNumber
- Data Structure: 
	1. Using map< string, set<string> > to realize linked list described in hint.ppt(which can also seem as undirected graph). This stores data for each writer co-work with whom.
	2. Using map< string, int > to store every one is which order relation with Erdos.
	3. Using queue< string > to realize BFS the undirected graph.

- Algorithm:
	1. Do loop to initialize the map< string, set<string> >. Loop every paper, if the auther is not a key in map and other co-workers for this paper push into a set. And this auther and set will be insert to map. If the auther is already the key, then get the set and push other co-workers. (set will delete duplicated authers for us)
	2. After initialize the map. Started from Erdos to use queue to do BFS and give every auther a order number stored at map< string, int >
	3. set will help us delete duplicate authers which we don't need. map will help us to easily find the auther which we want to manipulate it.
