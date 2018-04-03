# Implementations for Four UVa Questions

## FleaCircus
### Data Structure:
- Use adjacent list to implement a tree representing which two leaves or forks are connected. (vector<vector<int>>)
### Algorithm:
- Use DFS to search the tree to find the unique path from source to destination.
- Use a vector to store the path.
- Use a vector to record whether the leaf/fork has been visited or not.
- If the unique path contains odd number of leaves, the two fleas will meet at the middle of the path.
- If the unique path contains even number of leaves, the two fleas will jump forever at the middle two leaves of the path.

## PokerHands
Use 2 different algorithms to solve this problem.
### Algorithm1:
- Use 64-bit integer to store a hand of cards. First 10 bits are used to store the type of hands, and remaining bits are for the exact hand. One bit represents whether the hand contains the specific card, or is a specific type.
- Implement 9 functions to detect whether a hand is a specified type. Then return a value for each function to compare two hands of the same type.
- Pass all debuging cases in uva, fail the online judge because the input contains two same cards in one hand. The 64-bit data structure fails to store this kind of hand. 
### Algorithm2:
- Sort a hand according to card value.
- Detect whether a hand is flush or straight. If both, return type 9.
- Count how many times a value appears from '2' to 'A'.
- If 4 same values appear, return type 8. Other types are similarly processed.
- If within the same type, several cards' values need to be compared. Compressed them with radix 13.

## CheckTheCheck
### Data Structure:
- Use matrix board[8][8] to store the info of each chess.
- Use four integers to record the King info.

### Algorithm:
- Use loop to check every board[i][j]. For diffent types of chess, check whether it is the King. If it is, then use checkNoJump function to check whether this chess and the king have the some other chess between them. If yes, then King will not be checked. Otherwise, the King is checked and jumps out of the loop.

### Enhancement:
 - Use the King to check whether 8 directions have other chesses which not jump. It saves time.

## ErdosNumber
### Data Structure: 
- Use map<string,set<string>> to realize linked list described in hint.ppt(which can also be seemed as undirected graph). This stores data for each writer co-working with whom.
- Use map<string,int> to store every one's relationship with Erdos.
- Use queue<string> to realize BFS for undirected graph.

### Algorithm:
- Do loop to initialize the map<string,set<string>>. Loop every paper, if the author is not a key in map, then other co-workers for this paper are pushed into a set. And this author and his set will be inserted to the map. If the author is already the key, then get the set and push other co-workers.
- After initializing the map, start from Erdos to use queue to do BFS and give every author an order number stored at map<string,int>
- Set deletes duplicate authors. Map can easily find the author who will be manipulated.
