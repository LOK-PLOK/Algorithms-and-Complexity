# BINARY SEARCH TREES

- is a `Binary Tree` where the value of any node is greater than the left subtrees and less than the right subtree.

    ### Properties of Binary Search Tree
    - All nodes of the left subtree are `less` than the root node and nodes of the right subtree are `greater` than the root node.
    - The In-order traversal of binary search trees gives the values in ascending order.
    - All the subtrees of BST hold the same properties.

#### Advantages
- **Operations**:
- **Search** -  Best: `O(Log N)`: Worst: `O(N)`
- **Insert** -  Best: `O(Log N)`: Worst: `O(N)`
- **Delete** -  Best: `O(Log N)`: Worst: `O(N)`
---
1. **Efficient Operations (when balanced)**:
    - `Search`, `insert`, and `delete` operations can be done in `O(log n)` time on average.

2. **Dynamic Size**:
    - Unlike `arrays`, `BSTs` can grow or shrink dynamically without the need to reallocate memory.

3. **In-Order Traversal Gives Sorted Data**:
    - Traversing the tree in-order yields the elements in sorted order, which is useful for printing or range queries.

4. **Easy Implementation**:
    - `BSTs` are relatively easy to implement compared to more complex structures like `AVL` or `Red-Black Trees`.

5. **Binary Tree Structure**:
    - They can be used as the base structure for more advanced trees like `AVL`, `Red-Black`, `Splay Trees`, etc.

#### Disadvantages
1. **Poor Worst-Case Performance (O(n))**:
- If the tree becomes `unbalanced/Skewed` (e.g., inserting sorted data), operations degrade to linear time like a `linked list`.

2. **No Automatic Balancing**:
    - BSTs do not automatically balance themselves, which can lead to inefficiency over time unless manually balanced or restructured.

3. **Performance Dependent on Input Order**:
    - The structure and performance of a BST heavily depend on the order of insertion.

4. **Recursive Operations Can Be Costly**:
    - Recursive traversal or operations can lead to `stack overflow` for very deep trees.

5. **Inefficient for Duplicate Handling**:
    - BSTs do not naturally support duplicate values unless specifically handled with custom logic.

