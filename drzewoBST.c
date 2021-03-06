#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
unsigned int ns[] = {1000 ,2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 11000};

// each tree node contains an integer key and pointers to left and right children nodes
struct node {
    int key;
    struct node *left;
    struct node *right;
};

// tree'mrs.agnieszka s beginning is called the root
struct node *root = NULL;

struct node **tree_search(struct node **candidate, int value){
    if(((**candidate).key < value)&&((**candidate).right != NULL)){
            return tree_search(&(**candidate).right, value);

    }
    if(((**candidate).key > value)&&((**candidate).left != NULL)){
            return tree_search(&(**candidate).left, value);
    }
   // if ((**candidate).key == value){
        return candidate;
    //}

}

void display_tree(struct node* nod)
{
if(nod!=NULL)
{
if(nod->left==NULL & nod->right==NULL) printf("[%d;;]",nod->key);
if(nod->left==NULL & nod->right!=NULL) printf("[%d;;%d]",nod->key,nod->right->key);
if(nod->left!=NULL & nod->right==NULL) printf("[%d;%d;]",nod->key,nod->left->key);
if(nod->left!=NULL & nod->right!=NULL) printf("[%d;%d;%d]",nod->key,nod->left->key,nod->right->key);

display_tree(nod->left);
display_tree(nod->right);
}

}
struct node* tree_insert(int value) {
  struct node *new_component;
  new_component = (struct node*) malloc(sizeof(struct node));
        (*new_component).key = value;
        (*new_component).left = NULL;
        (*new_component).right = NULL;

    if (root == NULL){

        root = new_component;
    }
    else{

    struct node *struct_operational = root;


        while(1){
            if(((*struct_operational).key >= value)&&((*struct_operational).left) != NULL){
                struct_operational = (*struct_operational).left;


            }
            else if(((*struct_operational).key < value)&&((*struct_operational).right) != NULL){
                struct_operational = (*struct_operational).right;

            }
            else if((*struct_operational).key >= value){
                (*struct_operational).left = new_component;
                return new_component;
                }
            else{
                (*struct_operational).right = new_component;
                return new_component;
            }
            }

}
}



struct node **tree_maximum(struct node **candidate) {
        if((**candidate).right != NULL){
           return tree_maximum(&(**candidate).right);
        }

    return candidate;
}


void tree_delete(int value) {

    struct node **nodeptr = tree_search(&root, value);
    struct node **nodeptr2 = tree_search(&root, value);

if((**nodeptr).key == value){
    if(((**nodeptr).left == NULL) && ((**nodeptr).right == NULL)){
        *nodeptr = NULL;
        free(*nodeptr);
    }
    else if(((**nodeptr).left == NULL) && (**nodeptr).right != NULL){
        struct node *component = (**nodeptr).right;
        free(*nodeptr2);
        *nodeptr = component;


     }
    else if(((**nodeptr).left != NULL) && (**nodeptr).right == NULL){

        struct node *component = (**nodeptr).left;
        free(*nodeptr2);
        *nodeptr = component;
}
    else if(((**nodeptr).left != NULL) && (**nodeptr).right != NULL){
        struct node **maxnodeptr = tree_maximum(&(**nodeptr).left);

       (**nodeptr).key = (**maxnodeptr).key;


       if((**maxnodeptr).left != NULL){

        struct node *component = (**maxnodeptr).left;
        struct node *maxnodeptr2 = *maxnodeptr;
        free(maxnodeptr2);
        *maxnodeptr = component;
        }
        else{
        struct node *maxnodeptr2 = *maxnodeptr;

        free(maxnodeptr2);
        *maxnodeptr = NULL;

        }


    }
    }
}
int count(struct node *element, unsigned int *t){



    struct node *element_left = element;
    struct node *element_right = element;




    if((((*element_left).left != NULL))||((*element_right).right != NULL)){
        if((*element_left).left != NULL){

            element_left = (*element_left).left;
            *t = *t + 1;


            count(element_left, t);

        }
        if((*element_right).right != NULL){
            element_right = (*element_right).right;
            *t = *t + 1;

            count(element_right, t);

        }

    }


}




unsigned int tree_size(struct node *element) {

    unsigned int size = 1;



    if(element == NULL){

        return 0;
    }


    count(element, &size);


    return size;
}

/*
 * Fill an array with increasing values.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void fill_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }
}

/*
 * Reorder array elements in a random way.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void shuffle(int *t, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

/*
 * Check if tree is a valid BST.
 *
 * Parameters:
 *      struct node *element:   pointer to node to be checked
 *
 * Returns:
 *      bool:                   true if subtree rooted in "element" is a BST
 */
bool is_bst(struct node *element) {
    // empty tree is a valid BST
    if (element == NULL) {
        return true;
    }
    // leaf node is valid
    if (element->left == NULL && element->right == NULL) {
        return true;
    }
    // only right subnode? check it recursively
    if (element->left == NULL && element->right != NULL) {
        return (element->key < element->right->key) && is_bst(element->right);
    }
    // only left subnode? check it recursively
    if (element->left != NULL && element->right == NULL) {
        return (element->key > element->left->key) && is_bst(element->left);
    }
    // both subnodes present? check both recursively
    return (element->key > element->left->key)
        && (element->key < element->right->key)
        && is_bst(element->left)
        && is_bst(element->right);
}

void insert_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        tree_insert(t[i]);
    }
}

void insert_random(int *t, int n) {
    shuffle(t, n);
    for (int i = 0; i < n; i++) {
        //printf("   %d   ",t[i]);
 //       sleep(1);
        tree_insert(t[i]);
    };;
//exit(0);
}


void heapify(int A[], int n, int i)
{
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;



    if (l < n && A[l] > A[largest])
        largest = l;

    if (r < n && A[r] > A[largest])
        largest = r;

    if (largest != i)
    {

        int w = A[i];
        A[i] = A[largest];
        A[largest] = w;


        heapify(A, n, largest);
    }
}


void heapSort(int A[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(A, n, i);

    for (int i=n-1; i>=0; i--)
    {

        int w = A[0];
        A[0] = A[i];
        A[i] = w;

        heapify(A, i, 0);
    }
}




void tree_insert_biject(int *t, int p, int r){
    if (p == r){
        tree_insert(t[p]);
    }
    else if (r-p == 1){
        tree_insert(t[p]);
        tree_insert(t[r]);
    }
    else{
        int q = p + (r - p)/2;
        tree_insert(t[q]);
        tree_insert_biject(t, p, q-1);
        tree_insert_biject(t, q+1, r);
    }
}


void insert_binary(int *t, int n) {

    heapSort(t, n);
    tree_insert_biject(t, 0, n-1);


}

char *insert_names[] = { "Increasing", "Random", "Binary" };
void (*insert_functions[])(int*, int) = { insert_increasing, insert_random, insert_binary };

#define REPEATS 100


int main(int argc, char **argv) {
srand(time(NULL));
    for (unsigned int i = 0; i < sizeof(insert_functions) / sizeof(*insert_functions); i++) {
        void (*insert)(int*, int) = insert_functions[i];

        for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++) {
            unsigned int n = ns[j];

            // crate an array of increasing integers: 0, 1, 2, ...
            int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);

            // insert data using one of methods
            clock_t insertion_time = clock();
          //  for(int i=0; i<REPEATS; i++){
            insert(t, n);
           // }
            insertion_time = clock() - insertion_time;
//exit(0);
int a = tree_size(root);
           for (unsigned int l = 0, g = a; l < a; l++, g--) {


                assert(tree_size(root) == g);   // tree size must be equal to the expected value
             //   display_tree(root);
             //   printf("\n");
                tree_delete(t[l]);
             //   printf("TS:%d; m:%d; l:%d; n:%d;del:%d\n",tree_size(root),m-1,l,n,t[l]);
             // printf("\n");
            //  display_tree(root);
            //  printf("\n");
            //    assert(is_bst(root));
                     // after deletion, tree must still be valid BST
            }
            insert(t, n);

            assert(tree_size(root) == n);       // after all insertions, tree size must be `n`
            assert(is_bst(root));               // after all insertions, tree must be valid BST

            // reorder array elements before searching
            shuffle(t, n);

            // search for every element in the order present in array `t`
            clock_t search_time = clock();
            for(int i=0; i<REPEATS; i++){
            for (unsigned int k = 0; k < n; k++) {
                struct node **pnode = tree_search(&root, t[k]);
                struct node *iter = *pnode;
                assert(iter != NULL);           // found element cannot be NULL
                assert(iter->key == t[k]);      // found element must contain the expected value
            }}
            search_time = clock() - search_time;

            // reorder array elements before deletion
            shuffle(t, n);

            // delete every element in the order present in array `t`
            for (unsigned int l = 0, m = n; l < n; l++, m--) {

                assert(tree_size(root) == m);   // tree size must be equal to the expected value
             //   display_tree(root);
             //   printf("\n");
                tree_delete(t[l]);
             //   printf("TS:%d; m:%d; l:%d; n:%d;del:%d\n",tree_size(root),m-1,l,n,t[l]);
             // printf("\n");
            //  display_tree(root);
            //  printf("\n");
                assert(is_bst(root));
                     // after deletion, tree must still be valid BST
            }
            assert(tree_size(root) == 0);       // after all deletions, tree has size zero

            free(root);
            free(t);

            printf("%d\t%s\t%f\t%f\n",
                    n,
                    insert_names[i],
                    (double)insertion_time / CLOCKS_PER_SEC/REPEATS,
                    (double)search_time / CLOCKS_PER_SEC/REPEATS);

        }
    }
    return 0;
}
