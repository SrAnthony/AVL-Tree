/*
 *  ============================
 *  Anthony Nadaletti
 *  https://github.com/SrAnthony/AVL-Tree
 *  ============================
 */
typedef struct avl_node {
    // bf = Balance Factor
    // position = where the node is localized
		// 0 - right, 1 - left, 3 - is root
		int data, l_height, r_height, bf, position;
		struct avl_node *right;
		struct avl_node *left;
		struct avl_node *root;
}avl_node;
