#include <stdio.h>
#include <stdlib.h>



typedef struct node {
	int key;
	struct node *left;
	struct node *right;
} Node;

/* 스택 노드 */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* 큐 노드 */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);  /* 헤드노드(root) 생성 함수 */

void recursiveInorder(Node* ptr);	  /* 순환적 중위 순회 함수 */
void iterativeInorder(Node* ptr);     /* 반복적 중위 순회 함수 */
void levelOrder(Node* ptr);	          /* 레벨순서 순회 함수 */
int insert(Node* head, int key);      /* 노드 삽입 함수 */
int deleteNode(Node* head, int key);  /* 노드 삭제 함수 */
int freeBST(Node* head); /* 트리의 모든 메모리 할당 해제 함수 */
void printStack();  /* 스택 정보 출력 함수 */



int main()
{
	char command;
	int key;
	Node* head = NULL;

	do{
		printf("\n\n");
		printf("-----------------------[배기원][2021041081]---------------------\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z      Print Stack                  = p \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			/* 헤드노드(root) 생성 함수 호출 */
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			/* 트리의 모든 메모리 해제 */
			freeBST(head);
			break;
		case 'i': case 'I':
			/* 입력받은 키에 따라 노드 삽입 */
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			/* 입력받은 키의 노드 삭제 */
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			/* 순환적 중위 순회로 트리 탐색 */
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			/* 반복적 중위 순회로 트리 탐색 */
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			/* 레벨순서 순회로 트리 탐색 */
			levelOrder(head->left);
			break;

		case 'p': case 'P':
			/* 스택 정보 출력 */
			printStack();
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* 트리에 이미 노드가 존재하면 freeBST함수 호출 */
	if(*h != NULL)
		freeBST(*h);

	/* 헤드노드(root) 메모리 할당 */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if(ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}


void iterativeInorder(Node* node)
{
	for(;;)
	{
		for(; node; node = node->left)
			push(node);  //스택 push
		node = pop();  //스택 pop

		if(!node) break;  //스택이 공백이면 break
		printf(" [%d] ", node->key);

		node = node->right;
	}
}


void levelOrder(Node* ptr)
{
	/* 트리가 공백이면 리턴 */
	if(!ptr) return; 

	/* 큐를 사용하여 루트, 왼쪽 자식노드, 오른쪽 자식노드 순으로 순회 */
	enQueue(ptr);

	for(;;)
	{
		ptr = deQueue();
		if(ptr) {
			printf(" [%d] ", ptr->key);

			if(ptr->left)
				enQueue(ptr->left);
			if(ptr->right)
				enQueue(ptr->right);
		}
		else
			break;

	}

}


int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* root주소 전달 */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while(ptr != NULL) {

		/* 같은 키를 가진 노드가 이미 존재한다면, 함수 종료 */
		if(ptr->key == key) return 1;

		parentNode = ptr;

		/* 입력 key값이 현재 노드의 key보다 크면 오른쪽 노드로, 작으면 왼쪽 노드로 삽입 */
		if(ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* 부모노드에 따라 왼쪽자식노드 or 오른쪽자식노드로 삽입 */
	if(parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	/* 헤드노드가 없거나 자식노드가 없다면 오류 문구 출력 */
	if (head == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	if (head->left == NULL) {
		printf("\n Nothing to delete!!\n");
		return -1;
	}

	/* root주소 전달 */
	Node* root = head->left;



	Node* parent = NULL;
	Node* ptr = root;

	while((ptr != NULL)&&(ptr->key != key)) {
		if(ptr->key != key) {

			parent = ptr;	

			if(ptr->key > key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
	}

	/* 해당 키의 노드가 존재하지 않으면 오류문구 출력 */
	if(ptr == NULL)
	{
		printf("No node for key [%d]\n ", key);
		return -1;
	}

	/* 리프노드를 삭제하는 경우 */
	if(ptr->left == NULL && ptr->right == NULL)
	{
		if(parent != NULL) { 
			if(parent->left == ptr)
				parent->left = NULL;
			else
				parent->right = NULL;
		} else {
			head->left = NULL;

		}

		free(ptr);
		return 1;
	}

	/* 삭제할 노드의 자식노드가 하나일 경우 */
	if ((ptr->left == NULL || ptr->right == NULL))
	{
		Node* child;
		if (ptr->left != NULL)
			child = ptr->left;
		else
			child = ptr->right;

		if(parent != NULL)
		{
			if(parent->left == ptr)
				parent->left = child;
			else
				parent->right = child;
		} else {
			root = child;
		}

		free(ptr);
		return 1;
	}

	/* 삭제할 노드의 자식노드가 2개인 경우 */
	Node* candidate;
	parent = ptr;


	candidate = ptr->right;

	/* 왼쪽 서브트리에서 찾기 */
	while(candidate->left != NULL)
	{
		parent = candidate;
		candidate = candidate->left;
	}

	/* 오른쪽 서브트리에서 찾기 */
	if (parent->right == candidate)
		parent->right = candidate->right;
	else
		parent->left = candidate->right;

	ptr->key = candidate->key;

	free(candidate);
	return 1;
}


void freeNode(Node* ptr)
{
	if(ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{
	/* 트리에 헤드노드만 존재한다면 헤드노드 메모리 해제 */
	if(head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	if (top < 0) return NULL;
	return stack[top--];
}

void push(Node* aNode)
{
	stack[++top] = aNode;
}


void printStack()
{
	int i = 0;
	printf("--- stack ---\n");
	while(i <= top)
	{
		printf("stack[%d] = %d\n", i, stack[i]->key);
	}
}


Node* deQueue()
{
	if (front == rear) {
		printf("\n....Now Queue is empty!!\n" );
		return NULL;
	}

	front = (front + 1) % MAX_QUEUE_SIZE;
	return queue[front];

}

void enQueue(Node* aNode)
{
	rear = (rear + 1) % MAX_QUEUE_SIZE;
	if (front == rear) {
		printf("\n....Now Queue is full!!\n");
		return;
	}

	queue[rear] = aNode;
}





