#include <stdio.h>

#define node struct node_
node {
  int data;
  node *left;
  node *right;
};

node *tree;

void print_menu();
void create_tree(node *);
node *insertElement(node *, int);
void preorderTraversal(node *);
void inorderTraversal(node *);
void postorderTraversal(node *);
node *findSmallestElement(node *);
node *findLargestElement(node *);
node *deleteElement(node *, int);
int totalNodes(node *);
int totalExternalNodes(node *);
int totalInternalNodes(node *);
int height(node *);
/* figure out return type of following function */
node *mirrorImage(node *);
node *deleteTree(node *);

int main() {
  int option, val;
  node *ptr;
  create_tree(tree);
  print_menu();
  do {
    printf(" Enter your option : ");
    scanf("%d", &option);
    switch (option) {
    case 1:
      printf(" Enter the value of the new node : ");
      scanf("%d", &val);
      tree = insertElement(tree, val);
      break;
    case 2:
      printf(" The elements of the tree are : \n\t");
      preorderTraversal(tree);
      printf("\n");
      break;
    case 3:
      printf(" The elements of the tree are : \n\t");
      inorderTraversal(tree);
      printf("\n");
      break;
    case 4:
      printf(" The elements of the tree are : \n\t");
      postorderTraversal(tree);
      printf("\n");
      break;
    case 5:
      ptr = findSmallestElement(tree);
      printf(" Smallest element is :%d\n", ptr->data);
      break;
    case 6:
      ptr = findLargestElement(tree);
      printf(" Largest element is : %d\n", ptr->data);
      break;
    case 7:
      printf(" Enter the element to be deleted : ");
      scanf("%d", &val);
      tree = deleteElement(tree, val);
      break;
    case 8:
      printf(" Total no. of nodes = %d\n", totalNodes(tree));
      break;
    case 9:
      printf(" Total no. of external nodes = %d\n", totalExternalNodes(tree));
      break;
    case 10:
      printf(" Total no. of internal nodes = %d\n", totalInternalNodes(tree));
      break;
    case 11:
      printf(" The height of the tree = %d\n", height(tree));
      break;
    case 12:
      tree = mirrorImage(tree);
      break;
    case 13:
      tree = deleteTree(tree);
      break;
    case 14:
      break;
    default:
      print_menu();
      break;
    }
  } while (option != 14);
  return 0;
}

void print_menu() {
  printf("\n ******MAIN MENU******* \n");
  printf(" 1. Insert Element\n");
  printf(" 2. Preorder Traversal\n");
  printf(" 3. Inorder Traversal\n");
  printf(" 4. Postorder Traversal\n");
  printf(" 5. Find the smallest element\n");
  printf(" 6. Find the largest element\n");
  printf(" 7. Delete an element\n");
  printf(" 8. Count the total number of nodes\n");
  printf(" 9. Count the total number of external nodes\n");
  printf(" 10. Count the total number of internal nodes\n");
  printf(" 11. Determine the height of the tree\n");
  printf(" 12. Find the mirror image of the tree\n");
  printf(" 13. Delete the tree\n");
  printf(" 14. Exit\n\n");
}

void create_tree(tree)
node *tree;
{
  tree = NULL;
}

node *insertElement(tree, val)
node *tree;
int val;
{
  node *ptr, *nodeptr, *parentptr;
  ptr = alloc(6);
  ptr->data = val;
  ptr->left = NULL;
  ptr->right = NULL;

  if (tree == NULL) {
    tree = ptr;
    tree->left = NULL;
    tree->right = NULL;
  } else {
    parentptr = NULL;
    nodeptr = tree;
    while (nodeptr != NULL) {
      parentptr = nodeptr;
      if (val < nodeptr->data)
        nodeptr = nodeptr->left;
      else
        nodeptr = nodeptr->right;
    }
    if (val < parentptr->data)
      parentptr->left = ptr;
    else
      parentptr->right = ptr;
  }

  return tree;
}

void preorderTraversal(tree)
node *tree;
{
  if (tree == NULL)
    return;

  printf("%d\t", tree->data);
  preorderTraversal(tree->left);
  preorderTraversal(tree->right);
}

void inorderTraversal(tree)
node *tree;
{
  if (tree == NULL)
    return;

  inorderTraversal(tree->left);
  printf("%d\t", tree->data);
  inorderTraversal(tree->right);
}

void postorderTraversal(tree)
node *tree;
{
  if (tree == NULL)
    return;

  postorderTraversal(tree->left);
  postorderTraversal(tree->right);
  printf("%d\t", tree->data);
}

node *findSmallestElement(tree)
node *tree;
{
  if ((tree == NULL) || (tree->left == NULL))
    return tree;
  else
    return findSmallestElement(tree->left);
}

node *findLargestElement(tree)
node *tree;
{
  if ((tree == NULL) || (tree->right == NULL))
    return tree;
  else
    return findLargestElement(tree->right);
}

node *deleteElement(tree, val)
node *tree;
int val;
{
  node *cur, *parent, *suc, *psuc, *ptr;
  if (tree->left == NULL) {
    printf(" The tree is empty\n");
    return tree;
  }

  parent = tree;
  cur = tree->left;
  while ((cur != NULL) && (val != cur->data)) {
    parent = cur;
    cur = (val < cur->data) ? cur->left : cur->right;
  }
  if (cur == NULL) {
    printf(" The value to be deleted is not present in the tree\n");
    return tree;
  }

  if (cur->left == NULL)
    ptr = cur->right;
  else if (cur->right == NULL)
    ptr = cur->left;
  else {
    psuc = cur;
    cur = cur->left;
    while (suc->left != NULL) {
      psuc = suc;
      suc = suc->left;
    }
    if (cur == psuc)
      suc->left = cur->right;
    else {
      suc->left = cur->left;
      psuc->left = suc->right;
      suc->right = cur->right;
    }
    ptr = suc;
  }

  if (parent->left == cur)
    parent->left = ptr;
  else
    parent->right = ptr;

  free(cur);
  return tree;
}

int totalNodes(tree)
node *tree;
{
  if (tree == NULL)
    return 0;
  else
    return totalNodes(tree->left) + totalNodes(tree->right) + 1;
}

int totalExternalNodes(tree)
node *tree;
{
  if (tree == NULL)
    return 0;
  else if ((tree->left == NULL) && (tree->right == NULL))
    return 1;
  else
    return (totalExternalNodes(tree->left) + totalExternalNodes(tree->right));
}

int totalInternalNodes(tree)
node *tree;
{
  if ((tree == NULL) || ((tree->left == NULL) && (tree->right == NULL)))
    return 0;
  else
    return (totalInternalNodes(tree->left) + totalInternalNodes(tree->right) +
            1);
}

int height(tree)
node *tree;
{
  if (tree == NULL)
    return 0;

  int leftheight, rightheight;
  leftheight = height(tree->left);
  rightheight = height(tree->right);

  return (leftheight > rightheight) ? leftheight + 1 : rightheight + 1;
}

node *mirrorImage(tree)
node *tree;
{
  if (tree != NULL) {
    node *ptr;
    mirrorImage(tree->left);
    mirrorImage(tree->right);
    ptr = tree->left;
    ptr->left = ptr->right;
    tree->right = ptr;
  }
}

node *deleteTree(tree)
node *tree;
{
  if (tree != NULL) {
    deleteTree(tree->left);
    deleteTree(tree->right);
    free(tree);
  }
}
