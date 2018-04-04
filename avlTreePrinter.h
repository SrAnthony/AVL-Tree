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
    printf ( "(%d|h:%d)\n", root->data, height );
    printStructure ( root->left, level + 1 );
  }
}
