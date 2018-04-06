/*
 *  ============================
 *  Daniweb.com | Developed by Narue
 *  https://www.daniweb.com/programming/software-development/threads/146112/printing-a-binary-tree
 *  ============================
 */

void padding ( char ch, int n ){
  for (int i = 0; i < n; i++ )
    putchar ( ch );
}
void printStructure ( struct avl_node *root, int level ){

  if ( root == NULL ) {
    padding ( '\t', level+1 );
    puts ( "~" );
  }
  else {
    printStructure ( root->right, level + 1 );
    padding ( '\t', level+1 );

    int height = root->r_height > root->l_height ? root->r_height : root->l_height;
    printf ( "(\x1b[1m%d\x1b[0m|h:%d)\n", root->data, height );
    printStructure ( root->left, level + 1 );
  }
}
