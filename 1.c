#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    char name[4];
    float mo[11];
    float dong[11];
    float hieu[11];
    int ngay;
    float tb;
    int ngaytang;
    struct Node *left;
    struct Node *right;
} Node;

// add node

Node *addNode(Node *root, char name[], float mo, float dong)
{
    if (root == NULL)
    {
        root = (Node *)malloc(sizeof(Node));
        strcpy(root->name, name);
        root->mo[0] = mo;
        root->dong[0] = dong;
        root->ngay = 1;
        root->hieu[0]=dong-mo;
        root->tb = (dong-mo) / 10;
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        if (strcmp(root->name, name) == 0)
        {
            root->mo[root->ngay] = mo;
            root->dong[root->ngay] = dong;
            root->tb += (dong-mo) / 10;
            root->hieu[root->ngay]=dong-mo;
            root->ngay++;
        }
        else
        {
            if (strcmp(root->name, name) > 0)
            {
                root->left = addNode(root->left, name, mo, dong);
            }
            else
            {
                root->right = addNode(root->right, name, mo, dong);
            }
        }
    }
    return root;
}

Node* readFile(struct Node *r)
{
    int n;
    FILE *f = fopen("data.txt", "r");
    fscanf(f, "%d", &n);
    while (!feof(f))
    {
        char name[4];
        float mo, dong;
        fscanf(f, "%s\t%f\t%f", name, &mo, &dong);
        r = addNode(r, name, mo, dong);
    }
    fclose(f);
    return r;
}
void printBST(struct Node *r)
{
    if (r != NULL)
    {
        printBST(r->left);
        printf("%s\t%.3f\n", r->name, r->tb);
        printBST(r->right);
    }
}

struct Node *findNode(struct Node *root , char name[]){
    if (root == NULL)
        return root; 
    int c = strcmp(root->name, name);
    if (c == 0) return root;
    else if (c < 0)
        return findNode(root->right, name);
    else if (c > 0)
        return findNode(root->left, name);
}



void Func2(struct Node *r){
    printf("Nhap ten ma co phieu can tim: ");
    char name[100];
    fflush(stdin);
    scanf("%[^\n]%*c",name);
    struct Node *p = findNode(r, name);
    if (p != NULL){
        printf("%s:\n",p->name);
        int i;
        float max = p->dong[0], min = p->dong[0];
        for (i = 0; i < 10; i++){
        	if (p->dong[i] > max){
        		max = p->dong[i];
			}
            if (p->dong[i] < min){
                min = p->dong[i];
            }
        }
        printf("Gia dong cua cao nhat: %.3f\n", max);
        printf("Gia dong cua thap nhat: %.3f\n", min);
    }
    else {
        printf("Khong tim thay\n");
        return;
    }
    fflush(stdin);
}

int checkFunc3(Node *r)
{
    if (r == NULL)
    {
        return 0;
    }
    else
    {
        if (r->hieu[0] > 0 && r->hieu[1] > 0)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
}

void Func3(struct Node *r)
{
    if (r != NULL)
    {
        Func3(r->left);
        if (checkFunc3(r))
        {
            printf("%s\t%.3f\n", r->name, r->tb);
        }
        Func3(r->right);
    }
}

void freeTree(Node* r)
{
    if (r==NULL) return;
    freeTree(r->left);
    freeTree(r->right);
    free(r);
}

int tangmax = 0;
void findtangmax(Node *r)
{
	if (r == NULL) return;
	findtangmax(r->left);
	if (r->ngaytang > tangmax) tangmax = r->ngaytang;
	findtangmax(r->right);
}
void Func4(Node *r)
{
	//demtang(root);
	if (r == NULL) return;
	Func4(r->left);
	if (r->ngaytang == tangmax) printf("%s co so ngay tang lon nhat\n", r->name);
	Func4(r->right);
}

int main()
{
    struct Node* root=NULL;
    int choose;
    do
    {
        printf("============MENU============\n");
        printf("1. Doc file\n");
        printf("2. Tim kiem theo ma chung khoan\n");
        printf("3. Tim kiem nhung ma co xu huong tang\n");
        printf("4. Tim ma co so ngay tang lon nhat\n");
        printf("5. Thoat chuong trinh\n");
        printf("Ban chon chuc nang: ");
        scanf("%d",&choose);
        switch (choose)
        {
        case 1:
            root=readFile(root);
            printBST(root);
            fflush(stdin);
            break;
        case 2:
            Func2(root);
            break;
        case 3:
            Func3(root);
            break;
        case 4:
            findtangmax(root);
            Func4(root);
            break;
        case 5:
            printf("Nguyen Doan Anh Thai - 20205021\n");
            printf("============THANKS==========\n");
            freeTree(root);
            break;
        default:
            printf("Vui long chon 1 trong cac chuc nang!\n");
            break;
        }
    } while (choose!=5);
    
}