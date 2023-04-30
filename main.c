//sleman ghithan
//1202009

#include <stdio.h>
#include <intrin.h>
#include <string.h>
#include <stdbool.h>


struct Course{//Coursses structure
    char CourseName [50] ;
    int CreditHours;
    char CourseCode [30];
    char Department [50];
    char Topics [150];
    struct Course* Left;
    struct Course* Right;
    int Height;
};
struct Course* deleteByLetterTree;//global tree ,needed in deleting by first letter
//functions creation
struct Course* insert (struct Course* , char [50],int,char[30],char [50],char [150]);
struct Course* fileReader(struct Course*);
struct Course* insertNewCourse(struct Course*);
void printPreOrder(struct Course* t);
void printInOrder(struct Course* );
struct Course* findCourseAndUpdate(struct Course* );
struct Course* deleteNode(struct Course* , char  [30]);
void listTopics(struct Course* );
struct Course* deleteByLetter(struct Course* );
void printOrder(struct Course* );
void printDep(struct Course* );
struct Course* deleteDep(struct Course* );
struct Course* deleteCourse(struct Course* );
void PrintOnFileCall(struct Course*);
int main() {
    struct Course* mainTree;//the main tree(list) of coursses
    int choice=0;

    while (choice!=11) {//while the user don't enter 11 show the menu
        printf("1. Read the file courses.txt file and create the tree.\n"
               "2. Insert a new course from the user with all its associated data.\n"
               "3. Find a course and support updating of its information. \n"
               "4. List courses in lexicographic order with their associated information (credit hours, IDs, and topics). \n"
               "5. List all topics associated with a given course. \n"
               "6. List all courses in lexicographic order that belong to the same department.\n"
               "7. Delete a course.\n"
               "8. Delete all courses that start with a specific letter. \n"
               "9. Delete all courses belong to a given department.\n"
               "10. Save all words in file offered_courses.txt\n"
               "11.Exit program\n");
        scanf("%d",&choice);
        if(choice==11){
            printf("thanks for using my app\n"
                   "made by sleman ghithan \n");
            return 0;
        }

        switch (choice) {
            case 1:mainTree= fileReader(mainTree);break;
            case 2:mainTree= insertNewCourse(mainTree);break;
            case 3:mainTree= findCourseAndUpdate(mainTree);break;
            case 4:printOrder(mainTree);break;
            case 5:listTopics(mainTree);break;
            case 6:printDep(mainTree);break;
            case 7:mainTree=deleteCourse( mainTree);break;
            case 8:mainTree=deleteByLetter(mainTree );break;
            case 9:mainTree=deleteDep(mainTree);break;
            case 10: PrintOnFileCall( mainTree);break;
            case 11:printf("thanks for using my app\n");return 0;

        }
    }
    return 0;
}
int Max( int a, int b )
{//find maximum  between two numbers
    return a > b ? a : b;
}
struct Course* Find( char CourseCodeN [30], struct Course* mainTree )
{//search for an Course by its CODE
    if( mainTree == NULL )//if the list is null return null
        return NULL;
    if(strcmp(CourseCodeN,mainTree->CourseCode)==-1 )//if root code is more than entered code go search in left tree
        return Find( CourseCodeN, mainTree->Left );
    else if( strcmp(CourseCodeN,mainTree->CourseCode)==1 )//if root code is less than entered code go search in right tree
        return Find( CourseCodeN, mainTree->Right );
    else
        return mainTree;//return the node when find it
}
struct Course* FindMin( struct Course* T )
{//this function to find minimum node code by recursion
    if( T == NULL )
        return NULL;
    else if( T->Left == NULL )//when reach last left node return it
        return T;
    else//go left
        return FindMin( T->Left );
}
struct Course* FindMax( struct Course* T )
{//this function to find maximum node code without recursion
    if( T != NULL )
        while( T->Right != NULL )//until last right node
            T = T->Right;

    return T;//return it
}
int Height( struct Course* P )
{//this will return the height of node
    if( P == NULL )
        return -1;
    else
        return P->Height;
}
struct Course *right_rotate(struct Course *node)
{//rotate right of tree
    // Get left child node
    struct Course *left_node = node->Left;
    // Get left node right subtree
    struct Course *right_subtree = left_node->Right;
    // update the left and right subtree
    left_node->Right = node;
    node->Left = right_subtree;
    // Change the height of modified node
    node->Height = Max(
            Height(node->Left), Height(node->Right)) + 1;
    left_node->Height = Max(
            Height(left_node->Left), Height(left_node->Right)) + 1;
    return left_node;
}
struct Course *left_rotate(struct Course *node)
{
    // Get right child node
    struct Course *right_node = node->Right;
    //Get right node left subtree
    struct Course *left_subtree = right_node->Left;
    //update the left and right subtree
    right_node->Left = node;
    node->Right = left_subtree;
    //Change the height of modified node
    node->Height = Max(
            Height(node->Left), Height(node->Right)) + 1;
    right_node->Height = Max(
            Height(right_node->Left), Height(right_node->Right)) + 1;
    return right_node;
}
struct Course* SingleRotateWithLeft( struct Course* K2 )
{
    struct Course*  K1;

    K1 = K2->Left;//set k1 equal left of k2
    K2->Left = K1->Right;//set k2 left  equal right of k1
    K1->Right = K2;//set k1 right equal to k2

    //change the height as needed
    K2->Height = Max( Height( K2->Left ), Height( K2->Right ) ) + 1;
    K1->Height = Max( Height( K1->Left ), K2->Height ) + 1;

    return K1;  /* New root */
}
struct Course* SingleRotateWithRight( struct Course* K1 )
{
    struct Course* K2;

    K2 = K1->Right;//set k2 equal right of k1
    K1->Right = K2->Left;//set k1 right equal to k2 left
    K2->Left = K1;//set k2 left equal to k1

    //change the height as needed
    K1->Height = Max( Height( K1->Left ), Height( K1->Right ) ) + 1;
    K2->Height = Max( Height( K2->Right ), K1->Height ) + 1;

    return K2;  /* New root */
}
struct Course* DoubleRotateWithLeft( struct Course* K3 )
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithRight( K3->Left );

    /* Rotate between K3 and K2 */
    return SingleRotateWithLeft( K3 );
}
struct Course* DoubleRotateWithRight( struct Course* K1 )
{
    /* Rotate between K3 and K2 */
    K1->Right = SingleRotateWithLeft( K1->Right );

    /* Rotate between K1 and K2 */
    return SingleRotateWithRight( K1 );
}
struct Course* insert (struct Course* mainTree , char  CourseNameN [50],int CreditHoursN,char CourseCodeN [30],char DepartmentN [50],char  TopicsN [150]){
    if(mainTree==NULL){//build the node
        mainTree=(struct Course*) malloc(sizeof (struct Course));
        strcpy(mainTree->CourseName,CourseNameN);
        mainTree->CreditHours=CreditHoursN;
        strcpy(mainTree->CourseCode,CourseCodeN);
        strcpy(mainTree->Department,DepartmentN);
        strcpy(mainTree->Topics,TopicsN);
        mainTree->Height=0;
        mainTree->Left=NULL;
        mainTree->Right=NULL;
    }

    else if(strcmp(CourseCodeN,mainTree->CourseCode)<0){//if code entered is less go left
        mainTree->Left= insert(mainTree->Left,CourseNameN,CreditHoursN,CourseCodeN,DepartmentN,TopicsN);
        if( Height( mainTree->Left ) - Height( mainTree->Right ) == 2 ){//check height
            if(strcmp(CourseCodeN,mainTree->Left->CourseCode)<0) {//check height
                mainTree = SingleRotateWithLeft(mainTree);
            }
            else{//do rotation
                mainTree = DoubleRotateWithLeft(mainTree);
            }
        }
    }
    else if( strcmp(CourseCodeN,mainTree->CourseCode)>0 )
    {//if code entered is more go right
        mainTree->Right = insert( mainTree->Right,CourseNameN,CreditHoursN,CourseCodeN,DepartmentN,TopicsN );
        if( Height( mainTree->Right ) - Height( mainTree->Left ) == 2 ) {//check height
            if (strcmp(CourseCodeN,mainTree->Right->CourseCode)>0) {//check height
                mainTree = SingleRotateWithRight(mainTree);
            }
            else {//check height
                mainTree= DoubleRotateWithRight(mainTree);
            }
        }
    }

    //change the height
    mainTree->Height = Max( Height( mainTree->Left ), Height( mainTree->Right ) ) + 1;
    return mainTree;
}
void printPreOrder(struct Course* t){// print:root,left,root
    if(t!= NULL){
        printf("%s\n",t->CourseCode);
        printPreOrder(t->Left);
        printPreOrder(t->Right);
    }

}
void printInOrder(struct Course* t){// print:left,root,right
    if(t!= NULL){
        printInOrder(t->Left);
        printf("%s\t",t->CourseCode);
        printInOrder(t->Right);
    }
}
struct Course* fileReader(struct Course* mainTree){//read file and load data in the tree
    FILE *fileReader;//file pointer
    fileReader= fopen("courses.txt","r");//open file in read mode
    if(fileReader==NULL){
        printf("error while reading file\n");
        return mainTree;
    }
    else{
        char courseRead [250];
        int count=0;
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        while( fgets(courseRead,sizeof (courseRead),fileReader)!=NULL){//read line by line
            count++;
            char CourseNameN [50] ;
            int CreditHoursN;
            char CourseCodeN [30];
            char DepartmentN [50];
            char TopicsN [150];
            //trim
            char *token= strtok(courseRead,":");
            //copy data
            strcpy(CourseNameN,token);
            token= strtok(NULL,"#");
            CreditHoursN= atoi(token);
            token= strtok(NULL,"#");
            strcpy(CourseCodeN,token);
            token= strtok(NULL,"/");
            strcpy(DepartmentN,token);
            token= strtok(NULL,"\n");
            strcpy(TopicsN,token);
            //print
            printf("adding course number: %d\n",count);
            printf("Course info:\n\n");
            printf("course name: %s\n",CourseNameN);
            printf("course Credit Hours: %d\n",CreditHoursN);
            printf("course Code: %s\n",CourseCodeN);
            printf("Department: %s\n",DepartmentN);
            printf("topics: %s\n",TopicsN);
            printf("------------------------------------------------------------------------------------------------------------------------\n");
            mainTree= insert(mainTree,CourseNameN,CreditHoursN,CourseCodeN,DepartmentN,TopicsN);//insert into tree

        }

    }
    return mainTree;
}
struct Course* insertNewCourse(struct Course* mainTree){
    char CourseNameN [50];
    int CreditHoursN;
    char CourseCodeN [30];
    char DepartmentN [50];
    char  TopicsN [150];
    printf("------------------------------------------------------------------------------------------------------------------------");
    fflush(stdin);
    printf("enter Course name\n");
    scanf("%[a-z,A-Z,0-9,' ']c",CourseNameN);
    fflush(stdin);
    printf("enter credit hours\n");
    scanf("%d",&CreditHoursN);
    fflush(stdin);
    printf("enter the course code\n");
    scanf("%[a-z,A-Z,0-9,' ']c",CourseCodeN);
    fflush(stdin);
    printf("enter the department\n");
    scanf("%[a-z,A-Z,0-9,' ']c",DepartmentN);
    fflush(stdin);
    printf("enter the topics and put (,) between\n");
    scanf("%[a-z,A-Z,0-9,' ']c",TopicsN);
    mainTree= insert(mainTree,CourseNameN,CreditHoursN,CourseCodeN,DepartmentN,TopicsN);
    printf("course added successfully\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    return  mainTree;



}
struct Course* findCourseAndUpdate(struct Course* mainTree){
    char CourseCodeN [30];
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    fflush(stdin);
    printf("enter the course code to find it\n");
    scanf("%[a-z,A-Z,0-9,' ']c",CourseCodeN);
    char CourseNameN [50];
    int CreditHoursN;
    char DepartmentN [50];
    char  TopicsN [150];
    fflush(stdin);
    printf("enter new Course name\n");
    scanf("%[a-z,A-Z,0-9,' ']c",CourseNameN);
    fflush(stdin);
    printf("enter new credit hours\n");
    scanf("%d",&CreditHoursN);
    fflush(stdin);
    printf("enter new the department\n");
    scanf("%[a-z,A-Z,0-9,' ']c",DepartmentN);
    fflush(stdin);
    printf("enter the new topics and put (,) between\n");
    scanf("%[a-z,A-Z,0-9,' ']c",TopicsN);
    if( Find(CourseCodeN,mainTree)==NULL){//if the course not founded return
        printf("course not found\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        return mainTree;
    }
    struct Course* CourseFinded= Find(CourseCodeN,mainTree);//find it
    //copy its data
    strcpy(CourseFinded->CourseName,CourseNameN);
    CourseFinded->CreditHours=CreditHoursN;
    strcpy(CourseFinded->Department,DepartmentN);
    strcpy(CourseFinded->Topics,TopicsN);
    printf("course updated sucsessfully\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    return mainTree;


}
int get_balance_factor(struct Course *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return Height(node->Left) - Height(node->Right);//check the balance for a node
}
struct Course* deleteNode(struct Course* root,char CourseCodeN [30])
{//this  function will delete a node by its code

    if (root == NULL)

        return root;



//Find the node to be deleted

    //go left
    if (strcmp(CourseCodeN,root->CourseCode)==-1)

        root->Left = deleteNode(root->Left, CourseCodeN);



        //go right
    else if(strcmp(CourseCodeN,root->CourseCode)==1)

        root->Right = deleteNode(root->Right, CourseCodeN);



    else

    {// AVL_Node with only one child or no child

        //if no child
        if( (root->Left == NULL) || (root->Right == NULL) )
        {
            struct Course* temp = root->Left ? root->Left : root->Right;
            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else // One child case
                *root = *temp; // Copy the contents of the non-empty child
            free(temp);

        }
        else
        {
            // tree with two children: Get the inorder
            struct Course* temp = FindMin(root->Right);
            //cody data
            strcpy(root->CourseName,temp->CourseName);
            root->CreditHours=temp->CreditHours;
            strcpy(root->CourseCode,temp->CourseCode);
            strcpy(root->Department,temp->Department);
            strcpy(root->Topics,temp->Topics);
            //call delete
            root->Right = deleteNode(root->Right,temp->CourseCode);
        }
    }

// If the tree had only one node then return
    if (root == NULL)
        return root;
    //change height
    root->Height = 1 + Max(Height(root->Left),Height(root->Right));
    //check balance
    int balance = get_balance_factor(root);

    //rotate belong to balance
    if (balance > 1 &&
        get_balance_factor(root->Left) >= 0)
        return right_rotate(root);
    if (balance > 1 &&
        get_balance_factor(root->Left) < 0)
    {
        root->Left = left_rotate(root->Left);
        return right_rotate(root);
    }
    if (balance < -1 &&
        get_balance_factor(root->Right) <= 0)
        return left_rotate(root);
    if (balance < -1 &&
        get_balance_factor(root->Right) > 0)
    {
        root->Right = right_rotate(root->Right);
        return left_rotate(root);
    }
    return root;

}
struct Course* deleteCourse(struct Course* mainTree){//delete course calling
    char CourseCodeN [30];
    printf("------------------------------------------------------------------------------------------------------------------------");
    fflush(stdin);
    printf("enter the course code\n");
    scanf("%[a-z,A-Z,0-9,' ']c",CourseCodeN);
    if(Find(CourseCodeN,mainTree)==NULL){//if not found return
        printf("course not found\n");
        printf("------------------------------------------------------------------------------------------------------------------------\n");

        return mainTree;
    }
    struct Course* newTree=deleteNode(mainTree,CourseCodeN);//delete
    if(Find(CourseCodeN,newTree)!=NULL){//if still found then delete failed
        printf("delete failed\n");
    }
    if(Find(CourseCodeN,newTree)==NULL){//done
        printf("delete done successfully\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------------\n");

    return newTree;
}
void listTopics(struct Course* mainTree){//list a topics of a Course by its code
    char CourseCodeN [30];
    fflush(stdin);
    printf("------------------------------------------------------------------------------------------------------------------------");
    printf("enter the Course code to list it  topics\n");
    scanf("%[a-z,A-Z,0-9,' ']c",CourseCodeN);
    if(Find(CourseCodeN,mainTree)==NULL){//if not found
        printf("Course not found \n");
        return;mainTree;
    }
    struct Course* courseFinded=Find(CourseCodeN,mainTree);//search
    char TopicsN [150];
    strcpy(TopicsN,courseFinded->Topics);
    char *token= strtok(TopicsN,",");//trim
    int counter=1;
    printf("topics of %s\n",courseFinded->CourseName);
    while (token!=NULL){//print
        printf("%s",token);
        printf("        ");
        token= strtok(NULL,",");
        counter++;
        if(counter==5){
            printf("\n");
            counter=1;
        }

    }
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");

}
void printOrder(struct Course* t){

    if(t!= NULL){//print all courses data as left root right
        printOrder(t->Left);
        printf("name: %s\n",t->CourseName);
        printf("hours: %d\n",t->CreditHours);
        printf("code: %s\n",t->CourseCode);
        printf("Department: %s\n",t->Department);
        printf("topics: %s\n",t->Topics);
        printf("------------------------------------------------------------------------------------------------------------------------\n");
        printOrder(t->Right);
    }
}
bool isTRUE=false;//used to check if done
void callTreeDep(struct Course* t,char DepartmentN [50]){
    if(t!=NULL){//search for Department and print its courses
        callTreeDep(t->Left,DepartmentN);
        if(strcmp(DepartmentN,t->Department)==0){
            printf("%s\t",t->CourseCode);
            isTRUE=true;

        }
        callTreeDep(t->Right,DepartmentN);
    }

}
void printDep(struct Course* t){
    char DepartmentN [50];
    printf("------------------------------------------------------------------------------------------------------------------------");
    fflush(stdin);
    printf("enter the department name\n");
    scanf("%[a-z,A-Z,0-9,' ']c",DepartmentN);
    callTreeDep(t,DepartmentN);//call
    if(isTRUE==false){//if not found
        printf("error or not found \n");
    }
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");

}
struct Course* deleteTreeDep(struct Course* t,char DepartmentN [50]){//this will delete all courses of a department
    struct Course* temp;
    while(t!=NULL){//delete all
        if(strcmp(t->Department,DepartmentN)!=0){
            temp= insert(temp,t->CourseName,t->CreditHours,t->CourseCode,t->Department,t->Topics);
            //insert needed
        }
        else{
            printf("Course %s deleted\n",t->CourseCode);
        }
        t= deleteNode(t,t->CourseCode);//delete all
    }
    if(temp==NULL){
        printf("error or Department has no courses\n");
    }
    printf("------------------------------------------------------------------------------------------------------------------------");
    return temp;
}
struct Course* deleteDep(struct Course* t){
    char DepartmentN [50];
    printf("------------------------------------------------------------------------------------------------------------------------");
    fflush(stdin);
    printf("enter the department name\n");
    scanf("%[a-z,A-Z,0-9,' ']c",DepartmentN);
    return deleteTreeDep(t,DepartmentN);//call

}
struct Course* findByLetter(struct Course* mainTree,char letter){//this will delete all nodes its code starts be a letter
    struct Course* temp=mainTree;
    if(temp!=NULL){
        if(letter>temp->CourseCode[0]){
            findByLetter(temp->Right,letter);//right
        }
        if(letter<temp->CourseCode[0]){
            findByLetter(temp->Left,letter);//left
        }
        if(letter==temp->CourseCode[0]){
            findByLetter(temp->Left,letter);//left
            //insert into new tree
            deleteByLetterTree= insert(deleteByLetterTree,temp->CourseName,temp->CreditHours,temp->CourseCode,temp->Department,temp->Topics);
            findByLetter(temp->Right,letter);//right

        }
    }

    return temp;
}
struct Course* deleteByLetter(struct Course* mainTree){
    char letter;
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    fflush(stdin);
    printf("enter the letter\n");
    scanf("%c",&letter);
    struct Course* tempT=findByLetter(mainTree,letter);
    while(deleteByLetterTree!=NULL){//delete from global and main tree
        printf("course %s deleted\n",deleteByLetterTree->CourseCode);
        mainTree= deleteNode(mainTree,deleteByLetterTree->CourseCode);
        deleteByLetterTree= deleteNode(deleteByLetterTree,deleteByLetterTree->CourseCode);
    }
    printf("\n------------------------------------------------------------------------------------------------------------------------\n");
    return mainTree;
}
void PrintOnFile(FILE* FileWriter,struct Course* mainTree){
    if(mainTree!=NULL) {//for all nodes
        PrintOnFile(FileWriter, mainTree->Left);//left
        //print on file
        fprintf(FileWriter,"%s:%d#%s#%s/%s\n",mainTree->CourseName,mainTree->CreditHours,mainTree->CourseCode,mainTree->Department,mainTree->Topics);
        PrintOnFile(FileWriter, mainTree->Right);//right
    }
}
void PrintOnFileCall(struct Course* mainTree){
    FILE *FileWriter;//file pointer
    FileWriter= fopen("offered_courses.txt","w");//open file in write mode
    PrintOnFile(FileWriter, mainTree);//call
    fclose(FileWriter);


}